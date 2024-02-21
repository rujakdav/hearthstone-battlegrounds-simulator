#pragma once

#include "../../../tasks/DamageTask.h"
#include "enums/mechanics/effects/EffectTargets.h"
#include "mechanics/common/criterias/targets/EffectTargetCriteria.h"

/**
 * @brief The DamageEffectData class
 * This class is used to store data about damage effects
 */
class DamageEffectData {
private:
    EffectTargetCriteria effectTargetCriteria; /**< The criteria for the effect targets */
    int amount; /**< The amount of damage */

public:

    int getAmount() const;

    EffectTargetCriteria &getTargetsModel() ;

    DamageEffectData(EffectTargetCriteria &targetsModel, int amount);
};


