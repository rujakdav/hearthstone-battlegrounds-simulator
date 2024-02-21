
#pragma once


#include <string>
#include "enums/mechanics/common/triggerSource.h"
#include "enums/mechanics/common/triggerType.h"
#include "../common/data/DamageEffectData.h"
#include "IEffect.h"


class DamageEffect : public IEffect {
private:
    DamageEffectData data;
public:
    DamageEffect(const std::string &description, TriggerType triggerType, SourceCriteria sourceCriteria,
                 const DamageEffectData &damageEffectData);

    void execute(Minion *minion, PhaseController *game) override;

    std::unique_ptr<IEffect> clone() override;
};
