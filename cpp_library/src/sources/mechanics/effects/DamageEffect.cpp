
#include "../../../headers/mechanics/effects/DamageEffect.h"
#include "mechanics/common/TargetsBuilder.h"


DamageEffect::DamageEffect(const std::string &description, TriggerType triggerType, SourceCriteria sourceCriteria,
                           const DamageEffectData &damageEffectData) : IEffect(description, triggerType,
                                                                               sourceCriteria),
                                                                       data(damageEffectData) {}

void DamageEffect::execute(Minion *minion, PhaseController *game) {
    if (minion->getZone() == Zone::graveyard)
        return;
    std::vector<IDestructible *> myVector = TargetsBuilder(data.getTargetsModel()).getIDestructible(minion,
                                                                                                    game);
    auto damage = Damage(data.getAmount());
    auto task = DamageTask(myVector, damage);
    task.execute();
}

std::unique_ptr<IEffect> DamageEffect::clone() {
    return std::make_unique<DamageEffect>(*this);
}





