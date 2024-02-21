#include "../../../../headers/mechanics/common/data/EnchantmentEffectData.h"

EnchantmentEffectData::EnchantmentEffectData(EffectTargetCriteria &targetsModel, int attackIncrease, int healthIncrease,
                                             const std::string &name)
        : targetsModel(targetsModel), attackIncrease(attackIncrease), healthIncrease(healthIncrease), name(name) {}


int EnchantmentEffectData::getHealthIncrease() const {
    return healthIncrease;
}

int EnchantmentEffectData::getAttackIncrease() const {
    return attackIncrease;
}

const std::string &EnchantmentEffectData::getName() const {
    return name;
}

EffectTargetCriteria &EnchantmentEffectData::getTargetsModel() {
    return targetsModel;
}
