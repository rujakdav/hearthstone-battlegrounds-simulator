#include <catch2/catch_all.hpp>
#include "../../src/headers/entities/Minion.h"
#include "../../src/headers/tasks/HealTask.h"

TEST_CASE("HealTask Initialization with Single Target", "[HealTask]") {
    Minion targetMinion = Minion("Target", "CardKey1", 3, 20, MinionType::beast, 2, false, Rarity::common);
    targetMinion.setZone(Zone::play);

    SECTION("Initialization with Single Target") {
        REQUIRE_NOTHROW(HealTask(&targetMinion, 5));
        REQUIRE_THROWS(HealTask(&targetMinion, -5));
    }
}

TEST_CASE("HealTask Initialization with Multiple Targets", "[HealTask]") {
    Minion targetMinion1 = Minion("Target1", "CardKey1", 3, 20, MinionType::beast, 2, false, Rarity::common);
    Minion targetMinion2 = Minion("Target2", "CardKey2", 4, 15, MinionType::beast, 3, true, Rarity::common);

    targetMinion1.setZone(Zone::play);
    targetMinion2.setZone(Zone::play);

    SECTION("Initialization with Multiple Targets") {
        std::vector<IDestructible *> targets = {&targetMinion1, &targetMinion2};
        REQUIRE_NOTHROW(HealTask(targets, 7));
        REQUIRE_THROWS_AS(HealTask(targets, -7), std::invalid_argument);
    }
}

TEST_CASE("HealTask Execution", "[HealTask]") {
    Minion targetMinion = Minion("Target", "CardKey1", 3, 20, MinionType::beast, 2, false, Rarity::common);
    targetMinion.setZone(Zone::play);

    SECTION("Execute HealTask with Single Target and Full Health") {
        HealTask healTask(&targetMinion, 5);
        REQUIRE_NOTHROW(healTask.execute());
        REQUIRE(targetMinion.getHealthPoints() == targetMinion.getMaxHealthPoints());
    }

    SECTION("Execute HealTask with Single Target") {
        HealTask healTask(&targetMinion, 5);
        auto damage = Damage(10);
        targetMinion.takeDamage(damage);
        REQUIRE_NOTHROW(healTask.execute());
        REQUIRE(targetMinion.getHealthPoints() ==
                targetMinion.getMaxHealthPoints() - damage.getAmount() + healTask.getAmount());
    }

    SECTION("Execute HealTask with Multiple Targets and Full Health") {
        Minion targetMinion2 = Minion("Target2", "CardKey2", 4, 15, MinionType::beast, 3, true, Rarity::common);
        targetMinion2.setZone(Zone::play);

        std::vector<IDestructible *> targets = {&targetMinion, &targetMinion2};
        HealTask healTask(targets, 7);
        REQUIRE_NOTHROW(healTask.execute());
        REQUIRE(targetMinion.getHealthPoints() ==
                targetMinion.getMaxHealthPoints()); // Assuming basic heal logic without special effects
        REQUIRE(targetMinion2.getHealthPoints() ==
                targetMinion2.getMaxHealthPoints()); // Assuming basic heal logic without special effects
    }

    SECTION("Execute HealTask with Multiple Targets") {
        Minion targetMinion2 = Minion("Target2", "CardKey2", 4, 15, MinionType::beast, 3, true, Rarity::common);
        targetMinion2.setZone(Zone::play);

        std::vector<IDestructible *> targets = {&targetMinion, &targetMinion2};
        HealTask healTask(targets, 7);
        auto damage = Damage(10);
        targetMinion.takeDamage(damage);
        targetMinion2.takeDamage(damage);
        REQUIRE_NOTHROW(healTask.execute());
        REQUIRE(targetMinion.getHealthPoints() ==
                targetMinion.getMaxHealthPoints() - damage.getAmount() + healTask.getAmount());
        REQUIRE(targetMinion2.getHealthPoints() ==
                targetMinion2.getMaxHealthPoints() - damage.getAmount() + healTask.getAmount());
    }
}
