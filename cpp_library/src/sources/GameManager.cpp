

#include <algorithm>
#include <ctime>
#include <random>
#include "../headers/GameManager.h"
#include "controllers/phases/CombatPhaseController.h"
#include "controllers/phases/RecruitPhaseController.h"
#include "builders/MinionBuilder.h"
#include "builders/PlayerBuilder.h"

void GameManager::addPlayer(Player *player) {
    if (alivePlayers.size() >= maxPlayers)
        throw std::runtime_error("Maximum number of players reached");
    alivePlayers.emplace_back(player);

}

GameManager::GameManager() {
    minionPool = MinionPool();

}

void GameManager::startCombatPhase(const std::string &playerId1, const std::string &playerId2) {
    if (alivePlayers.size() < 2)
        throw std::runtime_error("Not enough players to start the combat phase");

    if (playerId1 == playerId2)
        throw std::runtime_error("Players must be different to start the combat phase");

    // Find players with the specified IDs
    auto player1Iterator = std::find_if(alivePlayers.begin(), alivePlayers.end(), [playerId1](const auto &player) {
        return player->getId() == playerId1;
    });

    auto player2Iterator = std::find_if(alivePlayers.begin(), alivePlayers.end(), [playerId2](const auto &player) {
        return player->getId() == playerId2;
    });

    // Check if both players were found
    if (player1Iterator != alivePlayers.end() && player2Iterator != alivePlayers.end()) {
        // Players found, proceed to initialize and execute the combatPhase
        auto combatPhase = CombatPhaseController((*player1Iterator), (*player2Iterator));

        auto player1OriginalBoard = (*player1Iterator)->getBoard();
        auto player2OriginalBoard = (*player2Iterator)->getBoard();


        combatPhase.init();

        combatPhase.executeCombat();

        //update original players board
        (*player1Iterator)->setBoard(player1OriginalBoard);
        (*player2Iterator)->setBoard(player2OriginalBoard);


    } else {
        // If one or both players were not found, throw an error
        throw std::runtime_error("One or both players not found to start the combat phase");
    }
}

void GameManager::startRecruitPhase(const std::string &playerId) {
    auto playerIterator = std::find_if(alivePlayers.begin(), alivePlayers.end(), [playerId](const auto &player) {
        return player->getId() == playerId;
    });

    auto recruitPhase = RecruitPhaseController(*playerIterator, &minionPool, currentTurn);
    recruitPhase.init();
    recruitPhase.beginTurn();


}


void GameManager::startGame() {
    // Check if there are enough players to start the game
    if (alivePlayers.size() < minPlayers)
        throw std::runtime_error("Not enough players to start the game");

    // Ensure the number of players is even
    if (alivePlayers.size() % 2 != 0)
        throw std::runtime_error("Uneven number of players");

    while (true) {

        //first every player has recruit phase
        for (auto &player: alivePlayers) {
            if (currentTurn != 1) { player->increaseStartOfTurnGold(); }
            startRecruitPhase(player->getId());
        }

        // Seed for random number generation
        std::srand(std::time(nullptr));

        // Create a copy of alivePlayers and shuffle it randomly
        std::vector<Player *> shuffledPlayers;

        //if there is even number of players, we just shuffle them
        //if there is odd number of players, we add lastDeadPlayer to the vector and shuffle it
        if (alivePlayers.size() % 2 == 0) {
            shuffledPlayers = alivePlayers;
        } else {
            shuffledPlayers = alivePlayers;
            shuffledPlayers.emplace_back(lastDeadPlayer);
        }

        std::shuffle(shuffledPlayers.begin(), shuffledPlayers.end(), std::mt19937(std::random_device()()));

        // Create a local vector of player pairs
        std::vector<std::tuple<Player *, Player *>> playerPairs;

        // Iterate through pairs of players and add to the local vector
        auto it = shuffledPlayers.begin();
        while (it != shuffledPlayers.end()) {
            // Ensure we have at least two players in each pair
            if (it + 1 != shuffledPlayers.end()) {
                playerPairs.emplace_back(*it, *(it + 1));
            }
            it += 2;
        }

        // Iterate through the local vector and start the combat phase for each pair
        for (const auto &[player1, player2]: playerPairs) {
            startCombatPhase(player1->getId(), player2->getId());
        }

        //now we check if any player is dead, if so we remove them from alivePlayers and add them to deadPlayers
        for (auto &player: alivePlayers) {
            if (player->getHealthPoints() <= 0) {
                deadPlayers.emplace_back(player);
                lastDeadPlayer = deadPlayers.back();
                alivePlayers.erase(std::remove(alivePlayers.begin(), alivePlayers.end(), player), alivePlayers.end());
            }
        }

        //if there is only one player left, we have a winner
        if (alivePlayers.size() == 1) {
            std::cout << "The winner of game is: " << alivePlayers[0]->getName() << std::endl;
            return;
        }
        currentTurn++;
    }


}

GameManager::~GameManager() {
    for (auto &player: alivePlayers) {
        delete player;
    }
    for (auto &player: deadPlayers) {
        delete player;
    }

}

std::string GameManager::addPlayer(const std::string &playerKey) {
    auto player = PlayerBuilder::getPlayer(playerKey);
    addPlayer(player);
    return player->getId();

}

void GameManager::movePlayerToDead(const std::string &playerId) {
    auto playerIterator = std::find_if(alivePlayers.begin(), alivePlayers.end(), [playerId](const auto &player) {
        return player->getId() == playerId;
    });

    if (playerIterator != alivePlayers.end()) {
        deadPlayers.emplace_back(*playerIterator);
        alivePlayers.erase(playerIterator);
    } else {
        throw std::runtime_error("Player not found to move to deadPlayers");
    }
}

void GameManager::executeSingleCombat(const std::string &playerId1, const std::vector<std::string> &minionIds1,
                                      const std::string &playerId2, const std::vector<std::string> &minionIds2,bool isPrint) {
    if (minionIds1.size() > 7 || minionIds2.size() > 7) {
        throw std::runtime_error("Too many minions to execute single combat");
    }
    auto player1 = PlayerBuilder::getPlayer(playerId1);
    auto player2 = PlayerBuilder::getPlayer(playerId2);
    for (auto &minionId: minionIds1) {
        player1->addMinionToBoard(MinionBuilder::getMinion(minionId));
    }
    for (auto &minionId: minionIds2) {
        player2->addMinionToBoard(MinionBuilder::getMinion(minionId));
    }

    auto combatPhase = CombatPhaseController(player1, player2);



    if(!isPrint) combatPhase.setPrintMode(PrintMode::noPrint);

    combatPhase.init();

    combatPhase.executeCombat();
    delete player1;
    delete player2;

}

