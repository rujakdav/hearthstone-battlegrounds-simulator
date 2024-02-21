
#include "../../../headers/mechanics/effects/HealEffect.h"
#include "mechanics/common/TargetsBuilder.h"
#include "../../../headers/tasks/HealTask.h"


HealEffect::HealEffect(const std::string &description, TriggerType triggerType, SourceCriteria sourceCriteria,
                       const HealEffectData &data) : IEffect(description, triggerType, sourceCriteria), data(data) {}


void HealEffect::execute(Minion *minion, PhaseController *game) {
    if (minion->getZone() == Zone::graveyard)
        return;
    std::vector<IDestructible *> myVector = TargetsBuilder(data.getTargetsModel()).getIDestructible(minion,
                                                                                                    game);
    HealTask task = HealTask(myVector, data.getAmount());
    task.execute();
}

std::unique_ptr<IEffect> HealEffect::clone() {
    return std::make_unique<HealEffect>(*this);
}
