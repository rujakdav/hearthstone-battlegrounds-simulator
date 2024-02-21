#include "../../headers/tasks//DamageTask.h"


const std::vector<IDestructible *> &DamageTask::getTargets() const {
    return targets;
}

void DamageTask::execute() {
    for (auto &target: targets) {
        target->takeDamage(damage);
    }
}

DamageTask::DamageTask(const std::vector<IDestructible *> &targets, Damage &damage) : targets(targets),
                                                                                      damage(damage) {}

DamageTask::DamageTask(IDestructible *target, Damage &damage) : damage(damage) {
    targets.push_back(target);

}

Damage &DamageTask::getDamage() const {
    return damage;
}

