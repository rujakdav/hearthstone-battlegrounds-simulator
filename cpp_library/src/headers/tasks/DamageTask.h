#pragma once

#include <vector>
#include "../components/IDestructible.h"
#include "ITask.h"
#include "../entities/Minion.h"


/**
 * @brief The DamageTask class
 * This class is used to represent a damage tasks
 */
class DamageTask : public ITask {
public:
    std::vector<IDestructible *> targets; /**< The targets */
    Damage &damage; /**< The damage to be dealt */
public:

    DamageTask(const std::vector<IDestructible *> &targets, Damage &damage);

    DamageTask(IDestructible *target, Damage &damage);

    const std::vector<IDestructible *> &getTargets() const;

    Damage &getDamage() const;

    void execute() override;

};

