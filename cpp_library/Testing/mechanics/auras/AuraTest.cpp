#include "catch2/catch_test_macros.hpp"
#include "mechanics/enchantments/Enchantment.h"
#include "mechanics/auras/Aura.h"
#include "mechanics/effects/DamageEffect.h"


TEST_CASE("Aura Constructor with Enchantment, [Aura]") {

    Enchantment testEnchantment("TestEnchantment", 2, 2);


    Aura aura("TestAura", testEnchantment);


    REQUIRE(aura.getName() == "TestAura");


    REQUIRE(aura.getEnchantment()->getName() == "TestEnchantment");


    REQUIRE(aura.getOwnerId().empty());
}

TEST_CASE("Aura Constructor with IEffect, [Aura]") {
    auto targets = EffectTargetCriteria(EffectTargets::enemyMinions, true, 1);
    std::unique_ptr<IEffect> testEffect = std::make_unique<DamageEffect>(
            "After a friendly minion loses Divine Shield, deal 2 damage to a random enemy minion",
            TriggerType::afterDivineShieldLoss,
            SourceCriteria(TriggerSource::friendlyMinions),
            DamageEffectData(targets, 2));


    Aura aura("TestAura", std::move(testEffect));


    REQUIRE(aura.getName() == "TestAura");


    REQUIRE(aura.getOwnerId().empty());
}

TEST_CASE("Aura Copy Constructor, [Aura]") {

    Enchantment testEnchantment("TestEnchantment", 2, 2);


    Aura originalAura("TestAura", testEnchantment);


    originalAura.setOwnerId("12345");

    Aura copiedAura(originalAura);

    REQUIRE(copiedAura.getName() == "TestAura");

    REQUIRE(copiedAura.getEnchantment()->getName() == "TestEnchantment");

    REQUIRE(copiedAura.getOwnerId() == "12345");
}

TEST_CASE("Set Owner ID for Aura, [Aura]") {
    Enchantment testEnchantment("TestEnchantment", 2, 2);

    Aura aura("TestAura", testEnchantment);

    aura.setOwnerId("98765");

    REQUIRE(aura.getOwnerId() == "98765");

    REQUIRE(aura.getEnchantment()->getOwnerId() == "98765");
}
