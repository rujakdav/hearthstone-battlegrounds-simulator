#pragma once


#include <memory>
#include <vector>
#include "messaging/ActionsCenter.h"

/**
 * @brief The GameManager class
 * This class is used to represent the game manager
 */
class GameManager {

private:
    const int minPlayers = 2; /**< The minimum number of players */
    const int maxPlayers = 8; /**< The maximum number of players */
    std::vector<Player *> alivePlayers; /**< The alive players */
    std::vector<Player *> deadPlayers; /**< The dead players */
    Player *lastDeadPlayer = nullptr; /**< The last dead player */
    MinionPool minionPool; /**< The minion pool */
    int currentTurn = 1; /**< The current turn */
public:
    GameManager();

    /**
     * @brief Adds a player to alive players
     * @param player
     */
    void addPlayer(Player *player);

    /**
     * @brief Add a player to alive players
     * @param player
     * @return The player id
     */
    std::string addPlayer(const std::string &playerKey);

    /**
     * @brief Moves a player with playerId to dead players
     * @param playerId
     */
    void movePlayerToDead(const std::string &playerId);

    /**
     * @brief Starts the game
     */
    void startGame();

    /**
     * @brief Starts the combat phase of game with players with playerIds
     * @param playerIds
     */
    void startCombatPhase(const std::string &playerId1, const std::string &playerId2);

    /**
     * @brief Starts the recruit phase of game with players with playerIds
     * @param playerIds
     */
    void startRecruitPhase(const std::string &playerId);

    /**
     * @brief Executes a single combat between players with playerIds and minions with minionIds
     * @param playerId1
     * @param minionIds1
     * @param playerId2
     * @param minionIds2
     * @param isPrint
     */
    void executeSingleCombat(const std::string &playerId1, const std::vector<std::string> &minionIds1,
                             const std::string &playerId2, const std::vector<std::string> &minionIds2,
                             bool isPrint = true);


    ~GameManager();


};



