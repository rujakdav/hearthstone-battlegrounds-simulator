
#pragma once

#include "../../tasks/ITask.h"
#include "mechanics/common/criterias/source/SourceCriteria.h"
#include "enums/mechanics/common/triggerType.h"
#include "../common/IOwned.h"
#include <string>

class Minion;

class PhaseController;

class IEffect : public IOwned {
private:
    int priority = 0;
public:
    void setPriority(int priority);

private:
    std::string description;
    TriggerType triggerType;
    SourceCriteria sourceCriteria;
public:

    IEffect(const std::string &description, TriggerType triggerType, SourceCriteria sourceCriteria);

    IEffect(const std::string &description, TriggerType triggerType, SourceCriteria sourceCriteria,
            const std::string &ownerId);

    int getPriority() const;

    const std::string &getDescription() const;

    TriggerType getTriggerType() const;

    const SourceCriteria &getSourceCriteria() const;

    virtual void execute(Minion *minion, PhaseController *game) = 0;

    virtual std::unique_ptr<IEffect> clone() = 0;

    virtual ~IEffect() = default;
};
