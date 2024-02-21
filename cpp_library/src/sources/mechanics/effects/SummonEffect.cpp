
#include "../../../headers/mechanics/effects/SummonEffect.h"
#include "mechanics/common/TargetsBuilder.h"
#include "../../../headers/tasks/SummonTask.h"

SummonEffect::SummonEffect(const std::string &description, TriggerType triggerType, SourceCriteria triggerSource,
                           const SummonEffectData &data) : IEffect(description, triggerType, triggerSource),
                                                           data(data) {}


void SummonEffect::execute(Minion *minion, PhaseController *game) {
    if (minion->getZone() == Zone::graveyard)
        return;
    std::vector<Player *> myVector = TargetsBuilder(data.getTargetsModel()).getPlayers(minion,
                                                                                       game);
    SummonTask task = SummonTask(myVector, data.getMinionToSummon());
    task.execute();
}

std::unique_ptr<IEffect> SummonEffect::clone() {
    return std::make_unique<SummonEffect>(*this);
}
