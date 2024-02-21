
#pragma once


#include <vector>
#include "../components/IDestructible.h"
#include "ITask.h"

/**
 * @brief The HealTask class
 * This class is used to represent a heal tasks
 */
class HealTask: public ITask {
    std::vector<IDestructible *> targets; /**< The targets */
    int amount; /**< The amount to be healed */
public:
    const std::vector<IDestructible *> &getTargets() const;

    int getAmount() const;

    HealTask(IDestructible *target, int amount);
    HealTask(const std::vector<IDestructible *> &targets, int amount);

    void execute() override;

};
