#include "controllers/phases/CombatPhaseController.h"
#include "utils/Utils.h"
#include "tasks/AttackTask.h"
#include "mechanics/effects/IEffect.h"
#include "messaging/ActionsCenter.h"
#include "builders/MinionBuilder.h"


void CombatPhaseController::executeCombat() {
    combatPhaseView.displayPlayers(player1, player2);
    update(TriggerType::startOfCombat);

    int attackerPlayerIndex;
    if (player1->getBoard().size() > player2->getBoard().size()) {
        attackerPlayerIndex = 0;
    } else if (player1->getBoard().size() < player2->getBoard().size())
        attackerPlayerIndex = 1;
    else
        attackerPlayerIndex = Utils::getRandomNumber(0, 1);

    while (!player1->getBoard().empty() && !player2->getBoard().empty()) {
        int attackerMinionIndex;
        int defenderMinionIndex;

        if (attackerPlayerIndex == 0) {
            attackerMinionIndex = findAttacker(player1);
            defenderMinionIndex = findDefender(player2);
            combatPhaseView.displayAttackingPlayer(player1);
        } else {
            attackerMinionIndex = findAttacker(player2);
            defenderMinionIndex = findDefender(player1);
            combatPhaseView.displayAttackingPlayer(player2);
        }

        auto attackerMinion = getAttackerPlayer(attackerPlayerIndex)->getBoard()[attackerMinionIndex];
        auto const &attackerId = attackerMinion->getId();

        for (int i = 0; i < attackerMinion->getRemainingAttacks(); i++) {
            auto defenderMinion = getDefenderPlayer(attackerPlayerIndex)->getBoard()[defenderMinionIndex];

            AttackTask attackTask(attackerMinion,
                                  defenderMinion);
            combatPhaseView.displayAttackingMinion(attackerMinion);
            combatPhaseView.displayDefendingMinion(defenderMinion);

            attackTask.execute();


            checkForDeadMinions();

            //if we cant find attacker minion, it means that it died during the attack
            if (getAttackerPlayer(attackerPlayerIndex)->getIndexOfMinionById(attackerId) == -1)
                break;

            //if defender has no more minions
            if (getDefenderPlayer(attackerPlayerIndex)->getBoard().empty())
                break;
            //else we generate another defender minion index
            defenderMinionIndex = findDefender(getDefenderPlayer(attackerPlayerIndex));
            if (defenderMinionIndex == -1)
                break;
        }

        attackerPlayerIndex = 1 - attackerPlayerIndex;  // Switch players

    }

    checkWinCondition();
    player1->unregisterObserver(this);
    player2->unregisterObserver(this);
}

int CombatPhaseController::findAttacker(Player *player) {
    int attackerMinionIndex = -1;

    for (int i = 0; i < player->getBoard().size(); i++) {
        if (!player->getBoard()[i]->isHasAttacked()) {
            attackerMinionIndex = i;
            break;
        }
    }

    if (attackerMinionIndex == -1) {
        for (auto j: player->getBoard()) {
            j->changeHasAttacked();
            j->setRemainingAttacks(j->getMaxRemainingAttacks());
        }
        attackerMinionIndex = 0;
    }

    return attackerMinionIndex;
}

int CombatPhaseController::findDefender(Player *player) {
    int defenderMinionIndex = -1;
    std::vector<int> tauntIndexes;

    for (int i = 0; i < player->getBoard().size(); i++) {
        if (player->getBoard()[i]->hasTaunt())
            tauntIndexes.push_back(i);
    }

    if (tauntIndexes.empty())
        defenderMinionIndex = Utils::getRandomNumber(0, player->getBoard().size() - 1);
    else
        defenderMinionIndex = Utils::getRandomNumberFromArray(tauntIndexes);

    return defenderMinionIndex;
}

Player *CombatPhaseController::getAttackerPlayer(int attackerPlayerIndex) {
    return (attackerPlayerIndex == 0) ? player1 : player2;
}

Player *CombatPhaseController::getDefenderPlayer(int attackerPlayerIndex) {
    return (attackerPlayerIndex == 0) ? player2 : player1;
}

void CombatPhaseController::update(Minion *minion, TriggerType triggerType, Player *player) {
    if (totalNodes == maxNodes)
        return;
    bool isFirst = this->root == nullptr;
    std::vector<std::tuple<Minion *, std::unique_ptr<IEffect>>> effectsToExecute;
    std::vector<Minion *> minions(actionsCenter->getActionsMap()[triggerType].begin(),
                                  actionsCenter->getActionsMap()[triggerType].end());
    if (minions.empty())
        actionsCenter->getActionsMap().erase(triggerType);

    for (auto &subscribedMinion: minions) {
        const auto &effects = subscribedMinion->getEffects();
        for (const auto &effect: effects) {
            /*
            if minion effect is triggered by a that trigger type
                (e.g. if the effect is triggered by after a minion attacks, the trigger type must be afterAttack)
            and if the minion that triggered the effect is a valid source
                (e.g. if the effect is triggered by a friendly minion, the source must be a friendly minion)
            and if the minion that triggered the effect passes the filter
                (e.g. if the effect is triggered by a pirate, the source must be a pirate)
            only then we add the effect to the list of effects to execute
             */
            if (effect->getTriggerType() == triggerType &&
                effect->getSourceCriteria().checkTriggerValidity(minion, subscribedMinion) &&
                effect->getSourceCriteria().applyFilter(*subscribedMinion)) {
                effectsToExecute.emplace_back(subscribedMinion, effect->clone());
            }
        }
    }
    if (effectsToExecute.empty()) {
        return;
    }
    if (root == nullptr) {
        root = new TreeNode(triggerType);
        totalNodes++;
        lastNode = root;
    }
    sortEffects(effectsToExecute);
    for (const auto &tuple: effectsToExecute) {
        auto effect = std::get<1>(tuple)->clone();
        auto minionPtr = std::get<0>(tuple);
        auto *effectNode = new TreeNode(effect->clone(), minionPtr, this);
        lastNode->addChild(effectNode);
        totalNodes++;
    }
    if (isFirst) {
        traverse(root);
    }
    if (totalNodes == visitedNodes && totalNodes != 0) {
        totalNodes = 0;
        visitedNodes = 0;
        root = nullptr;
        lastNode = nullptr;
        checkForDeadMinions();
    }
}

void CombatPhaseController::print() {
    player1->print();
    player2->print();
}

void CombatPhaseController::subscribeMinion(Minion *minion) {
    actionsCenter->subscribe(minion);
}

void CombatPhaseController::init() {
    for (auto &player1Minion: player1->getBoard()) {
        subscribeMinion(player1Minion);
    }
    for (auto &player2Minion: player2->getBoard()) {
        subscribeMinion(player2Minion);
    }
}

Player *CombatPhaseController::getFriendlyPlayer(Minion *minion) {
    return minion->getOwnerId() == player1->getId() ? player1 : player2;
}

Player *CombatPhaseController::getEnemyPlayer(Minion *minion) {
    return minion->getOwnerId() == player1->getId() ? player2 : player1;
}

void CombatPhaseController::checkForDeadMinions() {

    for (int i = 0; i < player1->getBoard().size(); i++) {
        if (player1->getBoard()[i]->getHealthPoints() <= 0) {
            auto minionId = player1->getBoard()[i]->getId();
            auto minionCardKey = player1->getBoard()[i]->getCardKey();
            update(player1->getMinionFromBoardById(minionId), TriggerType::deathrattle, player1);

            player1->unsubscribeMinion(player1->getMinionFromBoardById(minionId));
            player1->getMinionFromBoardById(minionId)->unregisterObserver(player1);

            player1->removeMinionFromBoardById(minionId);
            //player1->getMinionFromGraveyardById(minionId).unregisterObserver(player1);
            //we replace minion in graveyard with new one, because we need to reset its stats
            //player1->getMinionFromGraveyardById(minionId) = MinionBuilder::getMinion(minionCardKey);

        }
    }
    for (int i = 0; i < player2->getBoard().size(); i++) {
        if (player2->getBoard()[i]->getHealthPoints() <= 0) {
            auto minionId = player2->getBoard()[i]->getId();
            auto minionCardKey = player2->getBoard()[i]->getCardKey();
            update(player2->getMinionFromBoardById(minionId), TriggerType::deathrattle, player2);
            player2->unsubscribeMinion(player2->getMinionFromBoardById(minionId));

            player2->getMinionFromBoardById(minionId)->unregisterObserver(player2);
            player2->removeMinionFromBoardById(minionId);
            //we replace minion in graveyard with new one, because we need to reset its stats
            //player2->getMinionFromGraveyardById(minionId) = MinionBuilder::getMinion(minionCardKey);
        }
    }

}

void CombatPhaseController::checkWinCondition() {

    if (player1->getBoard().empty() && player2->getBoard().empty()) {
        combatPhaseView.displayCombatResult(player1, player2, true);

    } else if (player1->getBoard().empty()) {
        combatPhaseView.displayCombatResult(player2, player1, false);
        auto damageToDeal = Damage(player2->calculateDamageToDeal());
        player1->takeDamage(damageToDeal);

    } else {
        combatPhaseView.displayCombatResult(player1, player2, false);
        auto damageToDeal = Damage(player1->calculateDamageToDeal());
        player2->takeDamage(damageToDeal);
    }

}

Player *CombatPhaseController::getPlayerById(std::string id) {
    if (player1->getId() == id)
        return player1;
    else
        return player2;
}

void CombatPhaseController::unsubscribeMinion(Minion *minion) {
    actionsCenter->unsubscribe(minion);
}

CombatPhaseController::CombatPhaseController(Player *player1, Player *player2) : player1(player1),
                                                                                 player2(player2) {

    player1->registerObserver(this);
    player2->registerObserver(this);
    actionsCenter = std::make_unique<ActionsCenter>();
}


void CombatPhaseController::update(TriggerType triggerType) {
    update(nullptr, triggerType, nullptr);
}


void CombatPhaseController::subscribeMinionEffect(Minion *minion, const std::unique_ptr<IEffect> &auraEffect) {
    actionsCenter->subscribeEffect(minion, auraEffect);
}

void CombatPhaseController::unsubscribeMinionEffect(Minion *minion, const std::unique_ptr<IEffect> &auraEffect) {
    actionsCenter->unsubscribeEffect(minion, auraEffect);

}

void CombatPhaseController::sortEffects(std::vector<std::tuple<Minion *, std::unique_ptr<IEffect>>> &effectsToExecute) {
    auto customSort = [this](const std::tuple<Minion *, std::unique_ptr<IEffect>> &tuple1, const std
    ::tuple<Minion *, std::unique_ptr<IEffect>> &tuple2) {
        // Compare based on effect priority
        int priority1 = std::get<1>(tuple1)->getPriority();
        int priority2 = std::get<1>(tuple2)->getPriority();

        if (priority1 != priority2) {
            return priority1 < priority2;
        }
        // If effect priorities are the same, sort by index
        return this->getPlayerById(std::get<0>(tuple1)->getOwnerId())->getIndexOfMinionById(
                std::get<0>(tuple1)->getId()) <
               this->getPlayerById(std::get<0>(tuple2)->getOwnerId())->getIndexOfMinionById(
                       std::get<0>(tuple2)->getId());

    };

    std::sort(effectsToExecute.begin(), effectsToExecute.end(), customSort);

}

void CombatPhaseController::setPrintMode(PrintMode printMode) {
    combatPhaseView.setPrintMode(printMode);
}



