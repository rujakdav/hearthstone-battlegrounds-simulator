#include "../../../../headers/mechanics/common/data/SummonEffectData.h"

SummonEffectData::SummonEffectData(EffectTargetCriteria &targetsModel, const Minion &minionToSummon) : targetsModel(
        targetsModel), minionToSummon(minionToSummon) {}


const Minion &SummonEffectData::getMinionToSummon() const {
    return minionToSummon;
}

 EffectTargetCriteria &SummonEffectData::getTargetsModel()  {
    return targetsModel;
}

