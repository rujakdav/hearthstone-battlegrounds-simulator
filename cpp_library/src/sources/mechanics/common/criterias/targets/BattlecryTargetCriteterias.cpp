#include "mechanics/common/criterias/targets/BattlecryTargetCriterias.h"

BattlecryTargets BattlecryTargetCriteria::getBattlecryTargets() const {
    return battlecryTargets;
}

BattlecryTargetCriteria::BattlecryTargetCriteria(BattlecryTargets battlecryTargets,
                                                 const std::unique_ptr<IFilter> filter) :
        battlecryTargets(battlecryTargets),
        filter(filter->clone()) {}


bool BattlecryTargetCriteria::applyFilter(const Minion &minion) {
    if (filter == nullptr)
        return true;
    return filter->isValid(minion);
}

bool BattlecryTargetCriteria::applyFilter(const Player &player) {
    if (filter == nullptr)
        return true;
    return filter->isValid(player);
}

BattlecryTargetCriteria::BattlecryTargetCriteria(BattlecryTargets battlecryTargets) :
        battlecryTargets(battlecryTargets),
        filter(nullptr) {
    // Create a new DefaultFilter instance
}


BattlecryTargetCriteria::BattlecryTargetCriteria(const BattlecryTargetCriteria &other) :
        battlecryTargets(other.battlecryTargets),
        filter(other.filter ? other.filter->clone() : nullptr) {}
