#pragma once

#include <string>
#include "mechanics/common/criterias/targets/EffectTargetCriteria.h"

/**
 * @brief The EnchantmentEffectData class
 * This class is used to store data about enchantment effects
 */
class EnchantmentEffectData {
private:
    EffectTargetCriteria targetsModel; /**< The criteria for the effect targets */
    int attackIncrease; /**< The amount of attack to increase */
    int healthIncrease; /**< The amount of health to increase */
    std::string name; /**< The name of the enchantment */
public:
    const std::string &getName() const;

     EffectTargetCriteria &getTargetsModel() ;

    int getHealthIncrease() const;

    int getAttackIncrease() const;

    EnchantmentEffectData(EffectTargetCriteria &targetsModel, int attackIncrease, int healthIncrease, const std::string& name);

};



