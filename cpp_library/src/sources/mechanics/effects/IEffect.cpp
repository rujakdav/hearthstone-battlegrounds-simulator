
#include "../../../headers/mechanics/effects/IEffect.h"

IEffect::IEffect(const std::string &description, TriggerType triggerType, SourceCriteria sourceCriteria) : IOwned(""),
                                                                                                           description(
                                                                                                                   description),
                                                                                                           triggerType(
                                                                                                                   triggerType),
                                                                                                           sourceCriteria(
                                                                                                                   sourceCriteria) {

}

IEffect::IEffect(const std::string &description, TriggerType triggerType, SourceCriteria sourceCriteria,
                 const std::string &ownerId) : IOwned(ownerId), description(description), triggerType(triggerType),
                                               sourceCriteria(sourceCriteria) {

}

void IEffect::setPriority(int priority) {
    IEffect::priority = priority;
}

int IEffect::getPriority() const {
    return priority;
}

const std::string &IEffect::getDescription() const {
    return description;
}

TriggerType IEffect::getTriggerType() const {
    return triggerType;
}

const SourceCriteria &IEffect::getSourceCriteria() const {
    return sourceCriteria;
}
