#pragma once

#include "enums/mechanics/effects/EffectTargets.h"
#include "RandomTargets.h"
#include "mechanics/common/criterias/filters/IFilter.h"

/**
 * @brief The EffectTargetCriteria class
 * This class is used to filter effect targets
 */
class EffectTargetCriteria : public RandomTargets {
private:
    EffectTargets effectTargets;
    const std::unique_ptr<IFilter> filter;
public:
    EffectTargetCriteria(EffectTargets triggerTargets, const std::unique_ptr<IFilter> filter, bool isRandom, int howManyRandomTargets);

    EffectTargetCriteria(EffectTargets triggerTargets, bool isRandom, int howManyRandomTargets);
    EffectTargetCriteria(EffectTargets triggerTargets, const std::unique_ptr<IFilter> filter);
    EffectTargetCriteria(EffectTargets triggerTargets);

    EffectTargets getTriggerTargets() const;


    EffectTargetCriteria(const EffectTargetCriteria &other);
    bool applyFilter(const Minion& minion);
    bool applyFilter(const Player& player);
};
