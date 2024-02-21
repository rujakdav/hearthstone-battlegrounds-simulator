#include "../../../../headers/mechanics/common/data/HealEffectData.h"


int HealEffectData::getAmount() const {
    return amount;
}

HealEffectData::HealEffectData(EffectTargetCriteria &targetsModel, int amount) : targetsModel(targetsModel),
                                                                                 amount(amount) {}

EffectTargetCriteria &HealEffectData::getTargetsModel() {
    return targetsModel;
}
