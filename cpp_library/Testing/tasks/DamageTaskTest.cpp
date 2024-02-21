#include <catch2/catch_all.hpp>
#include "../../src/headers/entities/Minion.h"
#include "../../src/headers/tasks/DamageTask.h"

TEST_CASE("DamageTask Initialization", "[DamageTask]") {
    Minion dummyMinion = Minion("MinionName", "CardKey", 2, 25, MinionType::beast, 3, true, Rarity::common);
    dummyMinion.setZone(Zone::play);


    Damage dummyDamage(5);

    SECTION("Initialization with Multiple Targets") {
        std::vector<IDestructible *> targets = {&dummyMinion, &dummyMinion, &dummyMinion};
        DamageTask damageTask(targets, dummyDamage);

        REQUIRE(damageTask.getTargets().size() == 3);
        REQUIRE(&damageTask.getDamage() == &dummyDamage);
    }

    SECTION("Initialization with Single Target") {
        DamageTask damageTask(&dummyMinion, dummyDamage);

        REQUIRE(damageTask.getTargets().size() == 1);
        REQUIRE(&damageTask.getDamage() == &dummyDamage);
    }
}

TEST_CASE("DamageTask Execution", "[DamageTask]") {

    Minion dummyMinion1 = Minion("MinionName1", "CardKey1", 2, 25, MinionType::beast, 3, true, Rarity::common);
    Minion dummyMinion2 = Minion("MinionName2", "CardKey2", 2, 20, MinionType::beast, 3, true, Rarity::common);

    dummyMinion1.setZone(Zone::play);

    Damage dummyDamage(5);

    SECTION("Execute DamageTask with Multiple Targets") {
        std::vector<IDestructible *> targets = {&dummyMinion1, &dummyMinion2};
        DamageTask damageTask(targets, dummyDamage);

        damageTask.execute();


        REQUIRE(dummyMinion1.getHealthPoints() == 20);
        REQUIRE(dummyMinion2.getHealthPoints() == 20);
    }

    SECTION("Execute DamageTask with Single Target") {
        DamageTask damageTask(&dummyMinion1, dummyDamage);

        damageTask.execute();

        REQUIRE(dummyMinion1.getHealthPoints() == 20);
    }
}

