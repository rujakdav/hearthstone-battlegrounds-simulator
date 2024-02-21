#pragma once

#include <functional>
#include "IFilter.h"

/**
 * @brief The MixedFilter class
 * This class is used to filter both minions and players
 */
class MixedFilter : public IFilter {
private:
    std::function<bool(const Minion&)> minionFilterFunction; /**< The minion filter function */
    std::function<bool(const Player&)> playerFilterFunction; /**< The player filter function */

public:
    MixedFilter(std::function<bool(const Minion&)> minionFilter, std::function<bool(const Player&)> playerFilter);
    bool isValid(const Minion& minion) const override;
    bool isValid(const Player& player) const override;
    MixedFilter(const MixedFilter& other);
    std::unique_ptr<IFilter> clone() const override;
};
