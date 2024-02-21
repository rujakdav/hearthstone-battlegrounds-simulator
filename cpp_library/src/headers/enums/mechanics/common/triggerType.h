
#pragma once

#include <iostream>

enum class TriggerType
{
    none,
    startOfCombat,
    onAttack,
    afterAttacked,
    afterSummon,
    afterTakeDamage,
    deathrattle,
    afterDivineShieldLoss,
    onHeal,
    afterAttackIncrease,
    endOfTurn,
};

