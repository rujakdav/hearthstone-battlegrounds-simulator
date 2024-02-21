#include "enums/mechanics/effects/EffectTargets.h"
#include "mechanics/common/criterias/targets/EffectTargetCriteria.h"


EffectTargets EffectTargetCriteria::getTriggerTargets() const {
    return effectTargets;
}

EffectTargetCriteria::EffectTargetCriteria(EffectTargets triggerTargets, const std::unique_ptr<IFilter> filter) : RandomTargets(
        false, 0),
                                                                                                                  effectTargets(
                                                                                                               triggerTargets),
                                                                                                                  filter(filter->clone()) {}

EffectTargetCriteria::EffectTargetCriteria(EffectTargets triggerTargets, const std::unique_ptr<IFilter> filter, bool isRandom,
                                           int howManyRandomTargets) : RandomTargets(
        isRandom, howManyRandomTargets),
                                                                       effectTargets(triggerTargets),
                                                                       filter(filter->clone()) {}

bool EffectTargetCriteria::applyFilter(const Minion &minion) {
    if (filter == nullptr)
        return true;
    return filter->isValid(minion);
}

bool EffectTargetCriteria::applyFilter(const Player &player) {
    if (filter == nullptr)
        return true;
    return filter->isValid(player);
}

EffectTargetCriteria::EffectTargetCriteria(EffectTargets triggerTargets) : RandomTargets(false, 0),
                                                                           effectTargets(triggerTargets),
                                                                           filter(nullptr) {
    // Create a new DefaultFilter instance
}

EffectTargetCriteria::EffectTargetCriteria(EffectTargets triggerTargets, bool isRandom, int howManyRandomTargets) : RandomTargets(
        isRandom, howManyRandomTargets),
                                                                                                                    effectTargets(
                                                                                                                 triggerTargets),
                                                                                                                    filter(nullptr) {}

EffectTargetCriteria::EffectTargetCriteria(const EffectTargetCriteria &other)
        : RandomTargets(other), effectTargets(other.effectTargets),
          filter(other.filter ? other.filter->clone() : nullptr) {}
