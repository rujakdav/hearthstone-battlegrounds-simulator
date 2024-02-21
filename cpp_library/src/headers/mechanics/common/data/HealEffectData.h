#pragma once

#include "mechanics/common/criterias/targets/EffectTargetCriteria.h"

/**
 * @brief The HealEffectData class
 * This class is used to store data about heal effects
 */
class HealEffectData {
private:
    EffectTargetCriteria targetsModel; /**< The criteria for the effect targets */
    int amount; /**< The amount of heal */
public:
    EffectTargetCriteria &getTargetsModel();

    int getAmount() const;

    HealEffectData(EffectTargetCriteria &targetsModel, int amount);

};
