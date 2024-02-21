
#include <stdexcept>
#include "../../headers/tasks/HealTask.h"

const std::vector<IDestructible *> &HealTask::getTargets() const {
    return targets;
}

int HealTask::getAmount() const {
    return amount;
}

HealTask::HealTask(const std::vector<IDestructible *> &targets, int amount) : targets(targets), amount(amount) {
    if(amount < 0)
        throw std::invalid_argument("Heal amount cannot be negative");
}

HealTask::HealTask(IDestructible *target, int amount) {
    if(amount < 0)
        throw std::invalid_argument("Heal amount cannot be negative");
    targets.push_back(target);
    this->amount = amount;
}

void HealTask::execute() {
    for (auto target: targets) {
        target->heal(amount);
    }
}
