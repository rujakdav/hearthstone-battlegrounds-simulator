

#include "builders/MinionBuilder.h"
#include "enums/mechanics/effects/EffectTargets.h"
#include "mechanics/effects/SummonEffect.h"
#include "mechanics/effects/DamageEffect.h"
#include "mechanics/common/data/EnchantmentEffectData.h"
#include "mechanics/effects/EnchantmentEffect.h"
#include "mechanics/common/criterias/filters/MinionFilter.h"
#include "mechanics/common/data/HealEffectData.h"
#include "mechanics/effects/HealEffect.h"

Minion MinionBuilder::getMinion(const std::string &cardKey) {

    if (cardKey == "1Imp") {
        auto minion = Minion("Imp", cardKey, 1, 4, MinionType::demon, 1, false, Rarity::common);
        return minion;
    } else if (cardKey == "1ATron") {
        auto minion = Minion("Annoy-o-Tron", cardKey, 1, 2, MinionType::mech, 1, true, Rarity::common);
        minion.addTaunt();
        minion.addDivineShield();
        return minion;
    } else if (cardKey == "1Impris") {
        auto minion = Minion("Imprisoner", cardKey, 2, 2, MinionType::demon, 1, true, Rarity::common);
        minion.addTaunt();
        auto targets = EffectTargetCriteria(EffectTargets::friendlyPlayer);
        auto effect = SummonEffect("End of Turn: Summon a 1/1 Imp.",
                                   TriggerType::endOfTurn,
                                   SourceCriteria(TriggerSource::self),
                                   SummonEffectData(targets, MinionBuilder::getMinion("1Imp")));
        minion.addEffect(std::make_unique<SummonEffect>(effect));
        return minion;

    } else if (cardKey == "1Mis") {
        auto minion = Minion("Mistake", cardKey, 1, 3, MinionType::all, 1, true, Rarity::common);
        return minion;
    } else if (cardKey == "2Gambler") {
        auto minion = Minion("Freedealing Gambler", cardKey, 3, 3, MinionType::pirate, 2, true, Rarity::common);
        minion.setSellCost(3);
        return minion;
    } else if (cardKey == "2Rock") {
        auto minion = Minion("Molten Rock", cardKey, 3, 4, MinionType::elemental, 2, true, Rarity::common);
        auto targets = EffectTargetCriteria(EffectTargets::self);
        auto effect = EnchantmentEffect("After you take damage, gain +1 health",
                                        TriggerType::afterTakeDamage,
                                        SourceCriteria(TriggerSource::self),
                                        EnchantmentEffectData(targets, 0, 1, "Rock's Blessing"));
        minion.addEffect(std::make_unique<EnchantmentEffect>(effect));
        return minion;
    } else if (cardKey == "2Ripcap") {
        auto minion = Minion("Ripsnarl Captain", cardKey, 2, 4, MinionType::pirate, 2, true, Rarity::common);
        auto filter = MinionFilter(
                [](const Minion &filterMinion) { return filterMinion.getType() == MinionType::pirate; });
        auto targets = EffectTargetCriteria(EffectTargets::friendlyMinions, std::make_unique<MinionFilter>(filter),
                                            true, 1);
        auto effect = EnchantmentEffect("Whenever this attacks, give random friendly pirate +2/+0",
                                        TriggerType::onAttack,
                                        SourceCriteria(TriggerSource::self),
                                        EnchantmentEffectData(targets, 2, 0, "Pirate's Blessing"));
        minion.addEffect(std::make_unique<EnchantmentEffect>(effect));
        return minion;

    } else if (cardKey == "3Crackling") {
        auto minion = Minion("Crackling Cyclone", cardKey, 4, 1, MinionType::elemental, 3, true, Rarity::common);
        minion.setRemainingAttacks(2);
        minion.addDivineShield();
        return minion;
    } else if (cardKey == "3Ogre") {
        auto minion = Minion("BoulderFistOgre", cardKey, 6, 7, MinionType::general, 3, true, Rarity::common);
        return minion;
    } else if (cardKey == "3Paladin") {
        // Paladin of Light, 2/6, divine shield, after friendly minion loses divine shield, deal 2 daamge to random enemy
        auto minion = Minion("Paladin of Light", cardKey, 2, 6, MinionType::general, 3, true, Rarity::common);
        minion.addDivineShield();
        auto targets = EffectTargetCriteria(EffectTargets::enemyMinions, true, 1);
        auto effect = DamageEffect(
                "After a friendly minion loses Divine Shield, deal 2 damage to a random enemy minion",
                TriggerType::afterDivineShieldLoss,
                SourceCriteria(TriggerSource::friendlyMinions),
                DamageEffectData(targets, 2));
        minion.addEffect(std::make_unique<DamageEffect>(effect));
        return minion;
    } else if (cardKey == "4Mushroom") {

        auto minion = Minion("Toxic Mushroom", cardKey, 1, 1, MinionType::general, 4, true, Rarity::common);
        minion.setPoisonous(true);
        return minion;
    } else if (cardKey == "4Canon") {
        //Pirate Canon, 3/3, start of combat deal 2 damage to all enemy minions
        auto minion = Minion("Pirate Canon", cardKey, 3, 3, MinionType::pirate, 4, true, Rarity::common);
        auto targets = EffectTargetCriteria(EffectTargets::enemyMinions);
        auto effect = DamageEffect("At the start of combat, deal 2 damage to all enemy minions",
                                   TriggerType::startOfCombat,
                                   SourceCriteria(TriggerSource::none),
                                   DamageEffectData(targets, 2));
        minion.addEffect(std::make_unique<DamageEffect>(effect));
        return minion;
    } else if (cardKey == "4Cleric") {
        auto minion = Minion("Cleric", cardKey, 1, 9, MinionType::general, 4, true, Rarity::common);
        auto targets = EffectTargetCriteria(EffectTargets::friendlyMinions);
        auto effect = HealEffect("Whenever a friendly minion loses divine shield, heal all friendly minions 1",
                                 TriggerType::afterDivineShieldLoss,
                                 SourceCriteria(TriggerSource::friendlyMinions),
                                 HealEffectData(targets, 1));
        minion.addEffect(std::make_unique<HealEffect>(effect));
        return minion;
    } else if (cardKey == "5Defender") {
        auto minion = Minion("Defender of Strahov", cardKey, 1, 8, MinionType::general, 5, true, Rarity::common);
        minion.addTaunt();
        auto targets = EffectTargetCriteria(EffectTargets::friendlyMinions, true, 2);
        auto effect = EnchantmentEffect("At the start of combat, give +6/+6 to two random friendly minions",
                                        TriggerType::startOfCombat,
                                        SourceCriteria(TriggerSource::self),
                                        EnchantmentEffectData(targets, 6, 6, "Defender's Blessing"));
        minion.addEffect(std::make_unique<EnchantmentEffect>(effect));
        return minion;
    } else if (cardKey == "5Pyrom") {
        auto minion = Minion("Unstable Pyromancer", cardKey, 10, 2, MinionType::general, 5, true, Rarity::common);
        auto targets = EffectTargetCriteria(EffectTargets::allMinions);
        auto effect = DamageEffect("Start of Combat: Deal 3 damage to ALL minions",
                                   TriggerType::startOfCombat,
                                   SourceCriteria(TriggerSource::none),
                                   DamageEffectData(targets, 3));
        minion.addEffect(std::make_unique<DamageEffect>(effect));
        return minion;
    } else if (cardKey == "5Robot") {
        auto minion = Minion("Replicating Robot", cardKey, 4, 8, MinionType::mech, 5, true, Rarity::common);
        minion.addDivineShield();
        auto targets = EffectTargetCriteria(EffectTargets::friendlyPlayer);
        auto effect = SummonEffect("Start of Combat: Summon a 4/8 Replicating Robot",
                                   TriggerType::startOfCombat,
                                   SourceCriteria(TriggerSource::self),
                                   SummonEffectData(targets, MinionBuilder::getMinion("5RobotToken")));
        minion.addEffect(std::make_unique<SummonEffect>(effect));
        return minion;
    } else if (cardKey == "5RobotToken") {
        //Replicating robot,4/8,divine shield,token
        auto minion = Minion("Replicating Robot", cardKey, 4, 8, MinionType::mech, 5, false, Rarity::common);
        minion.addDivineShield();
        return minion;
    } else if (cardKey == "6Felstomper") {
        //Felstomer, after you summon minion, give your minions +3 attack
        auto minion = Minion("Felstomper", cardKey, 8, 8, MinionType::demon, 6, true, Rarity::common);
        auto targets = EffectTargetCriteria(EffectTargets::friendlyMinions);
        auto effect = EnchantmentEffect("After you summon a minion, give your minions +3 attack",
                                        TriggerType::afterSummon,
                                        SourceCriteria(TriggerSource::friendlyMinions),
                                        EnchantmentEffectData(targets, 3, 0, "Felstomper's Blessing"));
        minion.addEffect(std::make_unique<EnchantmentEffect>(effect));
        return minion;
    } else if (cardKey == "6Blademaster") {
        //Blademaster,6/18,divine,shield,megawindfury
        auto minion = Minion("Naga Blademaster", cardKey, 6, 18, MinionType::naga, 6, true, Rarity::common);
        minion.addDivineShield();
        minion.setRemainingAttacks(4);
        return minion;
    } else if (cardKey == "6Golem") {
        auto minion = Minion("Golem", cardKey, 3, 20, MinionType::general, 6, true, Rarity::common);
        minion.addTaunt();
        auto targets = EffectTargetCriteria(EffectTargets::enemyMinions);
        auto effect = DamageEffect("After this takes damage, deal 2 damage to all enemy minions",
                                   TriggerType::afterTakeDamage,
                                   SourceCriteria(TriggerSource::self),
                                   DamageEffectData(targets, 2));
        minion.addEffect(std::make_unique<DamageEffect>(effect));
        return minion;
    }

    throw std::invalid_argument("Invalid minion name " + cardKey);

}
