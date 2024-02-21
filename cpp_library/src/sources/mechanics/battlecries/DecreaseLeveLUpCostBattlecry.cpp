#include "../../../headers/entities/Player.h"
#include "mechanics/battlecries/DecreaseLeveLUpCostBattlecry.h"

std::unique_ptr<IBattlecry> DecreaseLeveLUpCostBattlecry::clone() {
    return std::make_unique<DecreaseLeveLUpCostBattlecry>(*this);
}

DecreaseLeveLUpCostBattlecry::DecreaseLeveLUpCostBattlecry(const std::string &description,
                                                           const BattlecryTargetCriteria &targetCriteria,
                                                           int amount) : IBattlecry(description, targetCriteria),
                                                                         amount(amount) {
    if (amount < 0)
        throw std::runtime_error("Amount must be positive");
}

void DecreaseLeveLUpCostBattlecry::setTargets(Player *player) {
    this->player = player;
    targetsSet = true;

}

void DecreaseLeveLUpCostBattlecry::setTargets(std::vector<Minion *> targets) {
    throw std::runtime_error("Only players can be targeted");

}

void DecreaseLeveLUpCostBattlecry::execute(RecruitPhaseController *game) {
    if (!targetsSet)
        throw std::runtime_error("Targets not set");

    for (int i = 0; i < amount; i++)
        player->decreaseLevelUpCost();

}


