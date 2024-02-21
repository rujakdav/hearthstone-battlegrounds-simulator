
#include "../../../headers/mechanics/effects/EnchantmentEffect.h"
#include "mechanics/common/TargetsBuilder.h"
#include "tasks/EnchantmentTask.h"


EnchantmentEffect::EnchantmentEffect(const std::string &description, TriggerType triggerType,
                                     SourceCriteria sourceCriteria,
                                     const EnchantmentEffectData &data) : IEffect(description, triggerType,
                                                                                  sourceCriteria), data(data) {


}

void EnchantmentEffect::execute(Minion *minion, PhaseController *game) {
    if (minion->getZone() != Zone::play)
        return;
    std::vector<Minion *> myVector = TargetsBuilder(data.getTargetsModel()).getMinions(minion,
                                                                                       game);

    auto enchantment = Enchantment(data.getName(), data.getAttackIncrease(), data.getHealthIncrease());
    auto enchantmentTask = EnchantmentTask(myVector, enchantment);
    enchantmentTask.execute();
}

std::unique_ptr<IEffect> EnchantmentEffect::clone() {
    return std::make_unique<EnchantmentEffect>(*this);
}
