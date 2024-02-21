#pragma once

#include "IEffect.h"
#include "../common/data/EnchantmentEffectData.h"

class EnchantmentEffect : public IEffect {
private:
    EnchantmentEffectData data;
public:

    EnchantmentEffect(const std::string &description, TriggerType triggerType,
                      SourceCriteria sourceCriteria,
                      const EnchantmentEffectData &data);

    void execute(Minion *minion, PhaseController *game) override;

    std::unique_ptr<IEffect> clone() override;
};

