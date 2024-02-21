#include <catch2/catch_test_macros.hpp>
#include "messaging/ActionsCenter.h"
#include "enums/mechanics/effects/EffectTargets.h"
#include "mechanics/common/criterias/targets/EffectTargetCriteria.h"
#include "builders/MinionBuilder.h"
#include "mechanics/common/data/SummonEffectData.h"
#include "mechanics/effects/SummonEffect.h"


TEST_CASE("ActionsCenter subscription and unsubscription", "[ActionsCenter]") {
    ActionsCenter actionsCenter;

    auto testMinion = Minion("Imprisoner", "is1", 2, 2, MinionType::demon, 1, true, Rarity::common);
    auto targets = EffectTargetCriteria(EffectTargets::friendlyPlayer);
    auto effect = SummonEffect("End of Turn: Summon a 1/1 Imp.",
                               TriggerType::endOfTurn,
                               SourceCriteria(TriggerSource::self),
                               SummonEffectData(targets, MinionBuilder::getMinion("1Imp")));
    testMinion.addEffect(std::make_unique<SummonEffect>(effect));


    actionsCenter.subscribe(&testMinion);

    REQUIRE(actionsCenter.getActionsMap()[TriggerType::endOfTurn].size() == 1);

    actionsCenter.unsubscribe(&testMinion);


    REQUIRE(actionsCenter.getActionsMap()[TriggerType::endOfTurn].empty());
}

TEST_CASE("ActionsCenter subscription and unsubscription with aura effect", "[ActionsCenter]") {

    ActionsCenter actionsCenter;


    auto testMinion = Minion("Imprisoner", "is1", 2, 2, MinionType::demon, 1, true, Rarity::common);
    auto targets = EffectTargetCriteria(EffectTargets::friendlyPlayer);
    testMinion.addEffect(std::make_unique<SummonEffect>("End of Turn: Summon a 1/1 Imp.",
                                                        TriggerType::endOfTurn,
                                                        SourceCriteria(TriggerSource::self),
                                                        SummonEffectData(targets, MinionBuilder::getMinion("1Imp"))));

    actionsCenter.subscribe(&testMinion);


    std::unique_ptr<IEffect> testAuraEffect = std::make_unique<SummonEffect>(
            "End of Turn: Summon a 2/2 Imp.",
            TriggerType::endOfTurn,
            SourceCriteria(TriggerSource::self),
            SummonEffectData(targets, MinionBuilder::getMinion("1Imp")));
    auto testMinion2 = Minion("Imprisoner", "is1", 2, 2, MinionType::demon, 1, true, Rarity::common);
    testMinion2.addEffect(std::make_unique<SummonEffect>("End of Turn: Summon a 1/1 Imp.",
                                                         TriggerType::endOfTurn,
                                                         SourceCriteria(TriggerSource::self),
                                                         SummonEffectData(targets, MinionBuilder::getMinion("1Imp"))));


    actionsCenter.subscribeEffect(&testMinion2, testMinion2.getEffects()[0]);


    REQUIRE(actionsCenter.getActionsMap()[testAuraEffect->getTriggerType()].size() == 2);


    actionsCenter.unsubscribeEffect(&testMinion2, testMinion2.getEffects()[0]);


    REQUIRE(actionsCenter.getActionsMap()[testAuraEffect->getTriggerType()].size() == 1);
}
