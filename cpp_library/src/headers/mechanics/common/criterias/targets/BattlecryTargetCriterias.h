#pragma once

#include "RandomTargets.h"
#include "mechanics/common/criterias/filters/IFilter.h"
#include "enums/mechanics/battlecries/battlecryTargets.h"

/**
 * @brief The BattlecryTargetCriteria class
 * This class is used to filter battlecry targets
 */
class BattlecryTargetCriteria {
private:
    BattlecryTargets battlecryTargets;
    const std::unique_ptr<IFilter> filter;

public:


    BattlecryTargetCriteria(BattlecryTargets battlecryTargets, const std::unique_ptr<IFilter> filter);

    BattlecryTargetCriteria(BattlecryTargets battlecryTargets);

    BattlecryTargets getBattlecryTargets() const;

    BattlecryTargetCriteria(const BattlecryTargetCriteria &other);

    bool applyFilter(const Minion &minion);

    bool applyFilter(const Player &player);
};
