#include "../../../../../headers/mechanics/common/criterias/filters/MixedFilter.h"

MixedFilter::MixedFilter(std::function<bool(const Minion &)> minionFilter,
                         std::function<bool(const Player &)> playerFilter)
        : minionFilterFunction(minionFilter), playerFilterFunction(playerFilter) {}

bool MixedFilter::isValid(const Minion &minion) const {
    return minionFilterFunction(minion);
}

bool MixedFilter::isValid(const Player &player) const {
    return playerFilterFunction(player);
}

MixedFilter::MixedFilter(const MixedFilter &other)
        : minionFilterFunction(other.minionFilterFunction), playerFilterFunction(other.playerFilterFunction) {}

std::unique_ptr<IFilter> MixedFilter::clone() const {
    return std::make_unique<MixedFilter>(*this);
}
