#pragma once

#include <map>
#include "enums/mechanics/common/triggerType.h"
#include "../entities/Player.h"
#include "controllers/phases/PhaseController.h"

/**
 * @brief The ActionsCenter class
 * This class is used to store the triggers and the minions that are subscribed to them
 */
class ActionsCenter {
private:
    std::map<TriggerType, std::vector<Minion *>> actionsMap;
public:

    /**
     * @brief This method is used to subscribe a minion to a trigger
     * @param minion
     */
    void subscribe(Minion *minion);

    /**
     * @brief This method is used to unsubscribe a minion from a trigger
     * @param minion
     */
    void unsubscribe(Minion *minion);


    /**
     * @brief This method is used to subscribe a minion with an aura effect to a trigger
     * @param minion
     * @param auraEffect
     */
    void subscribeEffect(Minion *minion, const std::unique_ptr<IEffect>& auraEffect);

    /**
     * @brief This method is used to unsubscribe a minion with an aura effect from a trigger
     * @param minion
     * @param auraEffect
     */
    void unsubscribeEffect(Minion *minion, const std::unique_ptr<IEffect>& auraEffect);

    void print();



    std::map<TriggerType, std::vector<Minion *>> &getActionsMap() ;

};

