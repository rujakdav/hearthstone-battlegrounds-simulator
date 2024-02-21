#pragma once

#include "IFilter.h"
#include <functional>

/**
 * @brief The PlayerFilter class
 * This class is used to filter players
 */
class PlayerFilter : public IFilter {
private:
    std::function<bool(const Player&)> playerFilterFunction; /**< The player filter function */

public:
    PlayerFilter(std::function<bool(const Player&)> filterFunction);
    bool isValid(const Minion& minion) const override;
    bool isValid(const Player& player) const override;
    PlayerFilter(const PlayerFilter& other);
    std::unique_ptr<IFilter> clone() const override;
};
