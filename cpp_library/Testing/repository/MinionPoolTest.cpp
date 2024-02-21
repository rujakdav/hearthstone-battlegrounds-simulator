#include <catch2/catch_all.hpp>
#include "../../src/headers/repository/MinionPool.h"



TEST_CASE("MinionPool Get Available Keys for Tier", "[MinionPool]") {
    MinionPool minionPool;

    SECTION("Get Available Minion Keys for Tier") {
        std::vector<std::string> availableKeys = minionPool.getAvailableKeysForTier(2);
        REQUIRE(availableKeys.size() == 3);
    }
}

TEST_CASE("MinionPool Get Random Minion Keys for Tier", "[MinionPool]") {
    MinionPool minionPool;

    SECTION("Get Random Minion Keys for Tier") {
        std::vector<std::string> randomKeys = minionPool.getRandomMinionKeysForTier(5, 2);
        REQUIRE(randomKeys.size() == 5);
        // Add more checks based on your repository keys and counts
    }
}
