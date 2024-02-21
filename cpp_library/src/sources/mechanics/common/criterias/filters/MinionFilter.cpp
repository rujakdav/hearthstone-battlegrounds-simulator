#include "../../../../../headers/mechanics/common/criterias/filters/MinionFilter.h"

MinionFilter::MinionFilter(std::function<bool(const Minion &)> filterFunction) : minionFilterFunction(
        filterFunction) {}

bool MinionFilter::isValid(const Minion &minion) const {
    return minionFilterFunction(minion);
}

bool MinionFilter::isValid(const Player &player) const {
    return false;
}

MinionFilter::MinionFilter(const MinionFilter &other) {
    this->minionFilterFunction = other.minionFilterFunction;
}

std::unique_ptr<IFilter> MinionFilter::clone() const {
    return std::make_unique<MinionFilter>(*this);
}


