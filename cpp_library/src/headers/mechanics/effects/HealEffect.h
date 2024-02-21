
#pragma once


#include "IEffect.h"
#include "enums/mechanics/common/triggerType.h"
#include "enums/mechanics/common/triggerSource.h"
#include "../common/data/HealEffectData.h"

class HealEffect : public IEffect {
private:
    HealEffectData data;
public:
    HealEffect(const std::string &description, TriggerType triggerType, SourceCriteria sourceCriteria,
               const HealEffectData &data);

    void execute(Minion *minion, PhaseController* game) override;

    std::unique_ptr<IEffect> clone() override;
};
