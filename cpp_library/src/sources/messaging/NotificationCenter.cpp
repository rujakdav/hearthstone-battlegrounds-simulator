
#include "../../headers/messaging/ActionsCenter.h"
#include "../../headers/utils/Utils.h"
#include "../../headers/mechanics/effects/HealEffect.h"
#include "../../headers/mechanics/effects/DamageEffect.h"


void ActionsCenter::subscribe(Minion *minion) {
    //for every effect of minion we get the trigger type
    //and add the minion to the map if it's not already there
    for (auto &effect: minion->getEffects()) {
        auto triggerType = effect->getTriggerType();
        // If trigger type not found in the map, create a new vector and add the minion
        if (actionsMap.find(triggerType) == actionsMap.end()) {
            actionsMap[triggerType].push_back(minion);
        } else {
            // If trigger type found in the map, check if the minion is already subscribed
            if (auto const &minions = actionsMap[triggerType]; std::find(minions.begin(), minions.end(), minion) !=
                                                               minions.end()) {
                return;
            }
            // If minion is not subscribed, add it to the vector
            actionsMap[triggerType].push_back(minion);

        }
    }

}

void ActionsCenter::print() {
    /*for (auto &i: actionsMap) {
        std::cout << Utils::getTriggerTypeString(i.first) << std::endl;
        for (auto &j: i.second) {
            std::cout << j->getName() << std::endl;
        }
    }*/
}


void ActionsCenter::unsubscribe(Minion *minion) {

    for (auto &entry: actionsMap) {
        auto &minions = entry.second;
        for(auto it = minions.begin(); it != minions.end(); ++it) {
            if (*it == minion) {
                minions.erase(it);
                break;
            }
        }
        //minions.erase(std::remove(minions.begin(), minions.end(), minion), minions.end());
    }

}

std::map<TriggerType, std::vector<Minion *>> &ActionsCenter::getActionsMap() {
    return actionsMap;
}

void ActionsCenter::subscribeEffect(Minion *minion, const std::unique_ptr<IEffect> &auraEffect) {
    auto triggerType = auraEffect->getTriggerType();

    // If trigger type not found in the map, create a new vector and add the minion
    /*if (actionsMap.find(triggerType) == actionsMap.end()) {
        actionsMap[triggerType].push_back(minion);
    }*/
    // If trigger type not found in the map, create a new vector and add the minion
    if (actionsMap.find(triggerType) == actionsMap.end()) {
        actionsMap[triggerType].push_back(minion);
    } else {
        // If trigger type found in the map, check if the minion is already subscribed
        if (auto const &minions = actionsMap[triggerType]; std::find(minions.begin(), minions.end(), minion) !=
                                                           minions.end()) {
            return;
        }
        // If minion is not subscribed, add it to the vector
        actionsMap[triggerType].push_back(minion);

    }

}

void ActionsCenter::unsubscribeEffect(Minion *minion, const std::unique_ptr<IEffect> &auraEffect) {

    //first we check if for that trigger type there is a minion with another effect with same trigger type
    auto triggerType = auraEffect->getTriggerType();
    if (actionsMap.find(triggerType) != actionsMap.end()) {
        auto const &minions = actionsMap[triggerType];
        for (auto &minionInMap: minions) {
            if (minionInMap->getId() == minion->getId()) {
                for (auto &effect: minionInMap->getEffects()) {
                    //there exists another unique effect with same trigger type, so we don't remove the minion
                    if (effect->getTriggerType() == triggerType && effect->getOwnerId() != auraEffect->getOwnerId()) {
                        return;
                    }
                }
                //there is no other effect with same trigger type, so we remove the minion
                actionsMap[triggerType].erase(
                        std::remove(actionsMap[triggerType].begin(), actionsMap[triggerType].end(),
                                    minion), actionsMap[triggerType].end());
                break;
            }
        }
    }
}


