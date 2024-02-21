#pragma once


#include <vector>
#include "entities/Minion.h"

/**
 * @brief The EnchantmentTask class
 * This class is used to represent an enchantment tasks
 */
class EnchantmentTask : public ITask {
private:
    std::vector<Minion *> targets; /**< The targets */
    Enchantment &enchantment; /**< The enchantment to be applied */
public:
    EnchantmentTask(const std::vector<Minion *> &targets, Enchantment &enchantment);
    EnchantmentTask(Minion * &target, Enchantment &enchantment);

    void execute() override;
};


