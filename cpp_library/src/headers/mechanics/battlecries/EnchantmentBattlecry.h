#pragma once

#include "IBattlecry.h"
#include "../enchantments/Enchantment.h"

/**
 * @brief The EnchantmentBattlecry class
 * This class is used to represent an enchantment battlecry
 */
class EnchantmentBattlecry : public IBattlecry {

private:
    Enchantment enchantment; /**< The enchantment */
    std::vector<Minion *> targets; /**< The MINION targets */
public:
    const Enchantment &getEnchantment() const;

    EnchantmentBattlecry(const std::string &description, const BattlecryTargetCriteria &targetCriteria,
                         const Enchantment &enchantment);

    void execute(RecruitPhaseController *game)override;

    void setTargets(std::vector<Minion *> targets) override;

    void setTargets(Player *player) override;

    std::unique_ptr<IBattlecry> clone() override;


};
