#include <catch2/catch_test_macros.hpp>
#include "../../src/headers/messaging/ActionsCenter.h"
#include "../../src/headers/controllers/phases/CombatPhaseController.h"
#include "builders/MinionBuilder.h"


TEST_CASE("CombatPhaseController findAttacker method", "[CombatPhaseController]") {

    auto player1 = Player("Player1", "P1");
    auto player2 = Player("Player2", "P2");
    CombatPhaseController combatController(&player1, &player2);
    int attackerIndex;

    player1.addMinionToBoard(MinionBuilder::getMinion("1Imp"));
    attackerIndex = combatController.findAttacker(&player1);
    REQUIRE(attackerIndex == 0);

    player1.addMinionToBoard(MinionBuilder::getMinion("1Imp"));
    attackerIndex = combatController.findAttacker(&player1);
    REQUIRE(attackerIndex <= 1);

    player1.addMinionToBoard(MinionBuilder::getMinion("1Imp"));
    attackerIndex = combatController.findAttacker(&player1);
    REQUIRE(attackerIndex <= 2);

}


TEST_CASE("CombatPhaseController findDefender method", "[CombatPhaseController]") {

    auto player1 = Player("Player1", "P1");
    auto player2 = Player("Player2", "P2");
    CombatPhaseController combatController(&player1, &player2);

    int defenderIndex;


    player1.addMinionToBoard(MinionBuilder::getMinion("1Imp"));
    defenderIndex = combatController.findDefender(&player1);
    REQUIRE(defenderIndex == 0);

    player1.addMinionToBoard(MinionBuilder::getMinion("1Imp"));
    player1.getBoard()[1]->addTaunt();
    defenderIndex = combatController.findDefender(&player1);
    REQUIRE(defenderIndex == 1);

    player1.addMinionToBoard(MinionBuilder::getMinion("1Imp"));
    player1.getBoard()[2]->addTaunt();
    defenderIndex = combatController.findDefender(&player1);
    REQUIRE((defenderIndex == 1 || defenderIndex == 2));

}

TEST_CASE("CombatPhaseController getPlayerById method", "[CombatPhaseController]") {
    auto player1 = Player("Player1", "P1");
    auto player2 = Player("Player2", "P2");
    CombatPhaseController combatController(&player1, &player2);

    Player *resultPlayer1 = combatController.getPlayerById(player1.getId());
    Player *resultPlayer2 = combatController.getPlayerById(player2.getId());

    REQUIRE(resultPlayer1 == &player1);
    REQUIRE(resultPlayer2 == &player2);
}

TEST_CASE("CombatPhaseController getFriendlyPlayer method", "[CombatPhaseController]") {
    auto player1 = Player("Player1", "P1");
    auto player2 = Player("Player2", "P2");
    CombatPhaseController combatController(&player1, &player2);

    player1.addMinionToBoard(MinionBuilder::getMinion("1Imp"));

    Player *friendlyPlayer = combatController.getFriendlyPlayer(player1.getBoard()[0]);

    REQUIRE(friendlyPlayer == &player1);
}

TEST_CASE("CombatPhaseController getEnemyPlayer method", "[CombatPhaseController]") {
    auto player1 = Player("Player1", "P1");
    auto player2 = Player("Player2", "P2");
    CombatPhaseController combatController(&player1, &player2);

    player1.addMinionToBoard(MinionBuilder::getMinion("1Imp"));

    Player *enemyPlayer = combatController.getEnemyPlayer(player1.getBoard()[0]);

    REQUIRE(enemyPlayer == &player2);
}
