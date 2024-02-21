
#pragma once


#include "IEffect.h"
#include "enums/mechanics/common/triggerType.h"
#include "enums/mechanics/common/triggerSource.h"
#include "../common/data/SummonEffectData.h"


class SummonEffect : public IEffect {
private:
    SummonEffectData data;
public:
    SummonEffect(const std::string &description, TriggerType triggerType, SourceCriteria triggerSource,
                 const SummonEffectData &data);


    void execute(Minion *minion, PhaseController* game) override;

    std::unique_ptr<IEffect> clone() override;
};
