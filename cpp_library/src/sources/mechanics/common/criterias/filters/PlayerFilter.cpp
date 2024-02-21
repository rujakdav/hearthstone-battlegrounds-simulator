#include "../../../../../headers/mechanics/common/criterias/filters/PlayerFilter.h"

PlayerFilter::PlayerFilter(std::function<bool(const Player &)> filterFunction) : playerFilterFunction(filterFunction) {}

bool PlayerFilter::isValid(const Minion &minion) const {
    return false;
}

bool PlayerFilter::isValid(const Player &player) const {
    return playerFilterFunction(player);
}

PlayerFilter::PlayerFilter(const PlayerFilter &other)
        : playerFilterFunction(other.playerFilterFunction) {}

std::unique_ptr<IFilter> PlayerFilter::clone() const {
    return std::make_unique<PlayerFilter>(*this);
}