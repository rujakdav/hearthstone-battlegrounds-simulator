#include "../../src/headers/entities/Minion.h"
#include "../../src/headers/enums/minion/minionType.h"
#include "../../src/headers/enums/card/rarity.h"
#include "enums/mechanics/effects/EffectTargets.h"
#include "mechanics/common/criterias/targets/EffectTargetCriteria.h"
#include "mechanics/common/data/DamageEffectData.h"
#include "mechanics/effects/DamageEffect.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Minion Constructor and Getter Methods, [Minion]") {
    Minion minion = Minion("MinionName", "CardKey", 2, 3, MinionType::beast, 3, true, Rarity::common);

    SECTION("getType") {
        REQUIRE(minion.getType() == MinionType::beast);
    }

    SECTION("getTavernTier") {
        REQUIRE(minion.getTavernTier() == 3);
    }

    SECTION("getSellCost") {
        REQUIRE(minion.getSellCost() == 3);
    }

    SECTION("isPoisonous") {
        REQUIRE_FALSE(minion.isPoisonous());
    }

    SECTION("hasTaunt") {
        REQUIRE_FALSE(minion.hasTaunt());
    }

    SECTION("getBattlecries") {
        REQUIRE(minion.getBattlecries().empty());
    }

    SECTION("getAuras") {
        REQUIRE(minion.getAuras().empty());
    }

    SECTION("getEnchantments") {
        REQUIRE(minion.getEnchantments().empty());
    }

    SECTION("getEffects") {
        REQUIRE(minion.getEffects().empty());
    }
}

TEST_CASE("Minion Setter Methods and Actions, [Minion]") {
    Minion minion("MinionName", "CardKey", 2, 3, MinionType::beast, 3, true, Rarity::common);

    SECTION("setSellCost") {
        minion.setSellCost(5);
        REQUIRE(minion.getSellCost() == 5);
    }

    SECTION("setPoisonous") {
        minion.setPoisonous(true);
        REQUIRE(minion.isPoisonous());
    }


    SECTION("addEnchantment") {
        std::unique_ptr<Enchantment> enchantment = std::make_unique<Enchantment>("EnchantmentName", 2, 2);
        minion.addEnchantment(std::move(enchantment));
        REQUIRE_FALSE(minion.getEnchantments().empty());
    }

    SECTION("addEffect") {
        auto targets = EffectTargetCriteria(EffectTargets::enemyMinions, true, 1);
        auto damageEffect = DamageEffect(
                "After a friendly minion loses Divine Shield, deal 2 damage to a random enemy minion",
                TriggerType::afterDivineShieldLoss,
                SourceCriteria(TriggerSource::friendlyMinions),
                DamageEffectData(targets, 2));
        minion.addEffect(std::make_unique<DamageEffect>(damageEffect));
        REQUIRE_FALSE(minion.getEffects().empty());
    }


    SECTION("addTaunt") {
        minion.addTaunt();
        REQUIRE(minion.hasTaunt());
    }
}

TEST_CASE("Minion Actions, [Minion]") {
    Minion minion("MinionName", "CardKey", 2, 3, MinionType::beast, 3, true, Rarity::common);

    SECTION("takeDamage") {
        Damage damage(2, false);

        minion.setZone(Zone::play);
        minion.takeDamage(damage);

        REQUIRE(minion.getHealthPoints() == 1);
    }

    SECTION("heal") {
        auto damage = Damage(2, false);
        minion.takeDamage(damage);
        minion.heal(3);
        REQUIRE(minion.getHealthPoints() == 3);
    }

    SECTION("removeEnchantmentAtIndex") {
        std::unique_ptr<Enchantment> enchantment = std::make_unique<Enchantment>("EnchantmentName", 2, 2);
        auto enchantmentHealthIncrease = enchantment->getHealthIncrease();
        auto enchantmentAttackIncrease = enchantment->getAttackIncrease();
        minion.addEnchantment(std::move(enchantment));


        int originalMaxHealth = minion.getMaxHealthPoints();
        int originalHealth = minion.getHealthPoints();

        minion.removeEnchantmentAtIndex(0);

        REQUIRE(minion.getMaxHealthPoints() == originalMaxHealth - enchantmentHealthIncrease);
        REQUIRE(minion.getHealthPoints() == originalHealth - enchantmentHealthIncrease);
    }
}
