#pragma once


#include "mechanics/common/criterias/targets/EffectTargetCriteria.h"
#include "../../../entities/Minion.h"

/**
 * @brief The SummonEffectData class
 * This class is used to store data about summon effects
 */
class SummonEffectData {
private:
    EffectTargetCriteria targetsModel; /**< The criteria for the effect targets */
    Minion minionToSummon; /**< The minion to summon */
public:
    EffectTargetCriteria &getTargetsModel();

    const Minion &getMinionToSummon() const;

    SummonEffectData(EffectTargetCriteria &targetsModel, const Minion &minionToSummon);

};
