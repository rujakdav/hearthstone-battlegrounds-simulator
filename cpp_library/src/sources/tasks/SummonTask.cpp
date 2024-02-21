#include "../../headers/tasks/SummonTask.h"

SummonTask::SummonTask(const std::vector<Player *> &players, const Minion &minionToSummon) : players(players),
                                                                                             minionToSummon(
                                                                                                     minionToSummon) {}

const std::vector<Player *> &SummonTask::getPlayers() const {
    return players;
}

const Minion &SummonTask::getMinionToSummon() const {
    return minionToSummon;
}

void SummonTask::execute() {
    for (auto player: players) {
        player->addMinionToBoard(minionToSummon);
    }
}
