#include <catch2/catch_all.hpp>
#include "../../src/headers/entities/Minion.h"
#include "../../src/headers/tasks/AttackTask.h"

TEST_CASE("AttackTask Initialization", "[AttackTask]") {
    auto attackerMinion = Minion("Attacker", "CardKey1", 3, 25, MinionType::beast, 2, false, Rarity::common);
    auto defenderMinion = Minion("Defender", "CardKey2", 2, 20, MinionType::beast, 3, true, Rarity::common);

    attackerMinion.setZone(Zone::play);
    defenderMinion.setZone(Zone::play);

    SECTION("Initialization") {
        AttackTask attackTask(&attackerMinion, &defenderMinion);

        REQUIRE(attackTask.attacker == &attackerMinion);
        REQUIRE(attackTask.defender == &defenderMinion);
    }
}

TEST_CASE("AttackTask Execution", "[AttackTask]") {
    auto attackerMinion = Minion("Attacker", "CardKey1", 3, 25, MinionType::beast, 2, false, Rarity::common);
    auto defenderMinion = Minion("Defender", "CardKey2", 2, 20, MinionType::beast, 3, true, Rarity::common);
    int attackerAttack = attackerMinion.getAttack();
    int defenderAttack = defenderMinion.getAttack();

    attackerMinion.setZone(Zone::play);
    defenderMinion.setZone(Zone::play);

    SECTION("Execute AttackTask") {
        AttackTask attackTask(&attackerMinion, &defenderMinion);
        attackTask.execute();

        REQUIRE(attackerMinion.getRemainingAttacks() == 0);
        REQUIRE(defenderMinion.getHealthPoints() == 20 - attackerAttack);
        REQUIRE(attackerMinion.getHealthPoints() == 25 - defenderAttack);
    }
}
