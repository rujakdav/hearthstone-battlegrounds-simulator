

#pragma once

#include <functional>
#include "IFilter.h"

/**
 * @brief The MinionFilter class
 * This class is used to filter minions
 */
class MinionFilter : public IFilter{
private:
    std::function<bool(const Minion&)> minionFilterFunction = [](const Minion &) { return true; }; /**< The minion filter function */
public:
    MinionFilter() = default;
    MinionFilter(std::function<bool(const Minion&)> filterFunction);
    bool isValid(const Minion& minion) const override;
    bool isValid(const Player& player) const override;
    MinionFilter(const MinionFilter& other);
    std::unique_ptr<IFilter> clone() const override;

};



