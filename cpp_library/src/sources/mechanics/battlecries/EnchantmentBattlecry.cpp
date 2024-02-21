
#include <stdexcept>
#include "../../../headers/mechanics/battlecries/EnchantmentBattlecry.h"
#include "../../../headers/entities/Minion.h"
#include "tasks/EnchantmentTask.h"

const Enchantment &EnchantmentBattlecry::getEnchantment() const {
    return enchantment;
}

void EnchantmentBattlecry::execute(RecruitPhaseController *game) {
    if (!targetsSet)
        throw std::runtime_error("Targets not set");

    auto enchantmentTask = EnchantmentTask(targets, enchantment);
    enchantmentTask.execute();
}

EnchantmentBattlecry::EnchantmentBattlecry(const std::string &description,
                                           const BattlecryTargetCriteria &targetCriteria,
                                           const Enchantment &enchantment) : IBattlecry(description,
                                                                                        targetCriteria),
                                                                             enchantment(enchantment) {}

void EnchantmentBattlecry::setTargets(std::vector<Minion *> targets) {
    this->targets = targets;
    targetsSet = true;
}

void EnchantmentBattlecry::setTargets(Player *player) {
    throw std::runtime_error("Only minions can be targeted");
}

std::unique_ptr<IBattlecry> EnchantmentBattlecry::clone() {
    return std::make_unique<EnchantmentBattlecry>(*this);
}





