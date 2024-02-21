#include "../../../../headers/mechanics/common/data/DamageEffectData.h"


int DamageEffectData::getAmount() const {
    return amount;
}

DamageEffectData::DamageEffectData(EffectTargetCriteria &targetsModel, int amount) : effectTargetCriteria(targetsModel),
                                                                                     amount(amount) {}

EffectTargetCriteria &DamageEffectData::getTargetsModel() {
    return effectTargetCriteria;
}

