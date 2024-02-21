#include "mechanics/common/criterias/source/SourceCriteria.h"
#include "entities/Minion.h"

TriggerSource SourceCriteria::getTriggerSource() const {
    return triggerSource;
}

bool SourceCriteria::applyFilter(const Minion &minion) const {

    if (filter == nullptr)
        return true;
    return filter->isValid(minion);
}

bool SourceCriteria::applyFilter(const Player &player) const {
    if (filter == nullptr)
        return true;
    return filter->isValid(player);
}

bool SourceCriteria::checkTriggerValidity(const Minion *baseMinion, const Minion *effectMinion) const {
    if (baseMinion == nullptr)
        return true;
    if (triggerSource == TriggerSource::none) {
        return true;
    } else if (triggerSource == TriggerSource::allMinions) {
        return true;
    } else if (triggerSource == TriggerSource::friendlyMinions) {
        return baseMinion->getOwnerId() == effectMinion->getOwnerId();
    } else if (triggerSource == TriggerSource::enemyMinions) {
        return !(baseMinion->getOwnerId() == effectMinion->getOwnerId());
    } else if (triggerSource == TriggerSource::self) {
        return baseMinion->getId() == effectMinion->getId();
    }
    return false;
}


SourceCriteria::SourceCriteria(TriggerSource triggerSource) : triggerSource(triggerSource), filter(nullptr) {}

SourceCriteria::SourceCriteria(TriggerSource triggerSource, const std::unique_ptr<IFilter> filter) : triggerSource(
        triggerSource),
                                                                                                     filter(filter->clone()) {}

SourceCriteria::SourceCriteria(const SourceCriteria &other)
        : triggerSource(other.triggerSource), filter(other.filter ? other.filter->clone() : nullptr) {}









