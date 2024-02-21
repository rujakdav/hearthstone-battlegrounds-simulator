
#include "../../headers/tasks/AttackTask.h"
#include "../../headers/tasks/DamageTask.h"

AttackTask::AttackTask(Minion *attacker, Minion *defender) : attacker(attacker), defender(defender) {}

void AttackTask::execute() {

    attacker->notifyObservers(TriggerType::onAttack);
    if (attacker->getZone() == Zone::play && defender->getZone() == Zone::play) {
        auto attackerDamage = Damage(defender->getAttack(), defender->isPoisonous());
        auto defenderDamage = Damage(attacker->getAttack(), attacker->isPoisonous());
        auto attackerDamageTask = DamageTask(attacker, attackerDamage);
        auto defenderDamageTask = DamageTask(defender,
                                             defenderDamage);

        attacker->changeHasAttacked();
        attacker->reduceRemainingAttacks();
        attackerDamageTask.execute();
        defenderDamageTask.execute();
        if (attacker->getZone() == Zone::play && defender->getZone() == Zone::play)
            defender->notifyObservers(TriggerType::afterAttacked);
    }


}
