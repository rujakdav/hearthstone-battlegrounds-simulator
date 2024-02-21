#pragma once

#include "enums/mechanics/common/triggerSource.h"
#include "mechanics/common/criterias/filters/IFilter.h"

/**
 * @brief The SourceCriteria class
 * This class is used to filter trigger sources
 */
class SourceCriteria {
private:
    TriggerSource triggerSource;
    const std::unique_ptr<IFilter> filter;

public:
    SourceCriteria(TriggerSource triggerSource, const std::unique_ptr<IFilter> filter);

    SourceCriteria(const SourceCriteria &other);

    explicit SourceCriteria(TriggerSource triggerSource);

    TriggerSource getTriggerSource() const;

    bool applyFilter(const Minion &minion) const;

    bool applyFilter(const Player &player) const;

    bool checkTriggerValidity(const Minion *baseMinion, const Minion *effectMinion) const;

};