
#pragma once

#include "../entities/Minion.h"
#include "ITask.h"

/**
 * @brief The AttackTask class
 * This class is used to represent an attack tasks
 */
class AttackTask : public ITask {

public:
    Minion* attacker; /**< The attacker */
    Minion* defender; /**< The defender */
    AttackTask(Minion *attacker, Minion *defender);
    void execute() override;
};
