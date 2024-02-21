#include <catch2/catch_test_macros.hpp>
#include "../../src/headers/entities/Player.h"

TEST_CASE("Player Initialization", "[Player]") {
    Player player("Player1", "CardKey1");

    SECTION("Check Initial Values") {
        REQUIRE(player.getName() == "Player1");
        REQUIRE(player.getId() != "");
        REQUIRE(player.getTavernTier() == 1);
        REQUIRE(player.getCurrentGold() == 3);
        REQUIRE(player.getStartOfTurnGold() == 10);
        REQUIRE(player.getLevelUpCost() == 5);
        REQUIRE(player.getRefreshCost() == 1);
        REQUIRE(player.getBuyCost() == 3);
        REQUIRE(player.getMaxMinionsOnBoard() == 7);
        REQUIRE(player.getMaxMinionsInHand() == 10);
    }

    SECTION("Check Player Board and Hand Initialization") {
        REQUIRE(player.getBoard().empty());
        REQUIRE(player.getHand().empty());
    }
}

TEST_CASE("Player Leveling Up", "[Player]") {
    Player player("Player1", "CardKey1");

    SECTION("Level Up to Tier 2") {
        player.levelUp();
        REQUIRE(player.getTavernTier() == 2);
        REQUIRE(player.getLevelUpCost() == 5);
    }

    SECTION("Level Up to Maximum Tier") {
        for (int i = 0; i < 5; ++i) {
            player.levelUp();
        }
        REQUIRE(player.getTavernTier() == 6);
        REQUIRE(player.getLevelUpCost() == 5);
    }
}

TEST_CASE("Player Gold Management", "[Player]") {
    Player player("Player1", "CardKey1");

    SECTION("Add Gold") {
        player.addGold(5);
        REQUIRE(player.getCurrentGold() == 8);
    }

    SECTION("Spend Gold") {
        player.spendGold(2);
        REQUIRE(player.getCurrentGold() == 1);
    }

    SECTION("Check Affordability") {
        REQUIRE(player.canAfford(2));
        REQUIRE_FALSE(player.canAfford(10));
    }
}

TEST_CASE("Player Board Operations", "[Player]") {
    Player player("Player1", "CardKey1");

    SECTION("Add Minion to Board") {
        Minion minion = Minion("MinionName", "CardKey", 2, 3, MinionType::beast, 3, true, Rarity::common);

        player.addMinionToBoard(minion);

        REQUIRE(player.getBoard().size() == 1);
        REQUIRE(player.getBoard()[0]->getId() == minion.getId());
    }

    SECTION("Remove Minion from Board") {
        Minion minion = Minion("MinionName", "CardKey", 2, 3, MinionType::beast, 3, true, Rarity::common);
        player.addMinionToBoard(minion);

        REQUIRE(player.getBoard().size() == 1);

        player.removeMinionFromBoardById(minion.getId());

        REQUIRE(player.getBoard().empty());
    }
}


