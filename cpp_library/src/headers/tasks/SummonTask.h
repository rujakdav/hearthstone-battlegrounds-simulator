
#pragma once


#include <vector>
#include "../components/IDestructible.h"
#include "ITask.h"
#include "../entities/Player.h"

/**
 * @brief The SummonTask class
 * This class is used to represent a summon tasks
 */
class SummonTask: public ITask {
    std::vector<Player *> players; /**< The players */
    Minion minionToSummon; /**< The minion to be summoned */
public:
    const std::vector<Player *> &getPlayers() const;

    const Minion &getMinionToSummon() const;

    SummonTask(const std::vector<Player *> &players, const Minion &minionToSummon);

    void execute() override;

};
