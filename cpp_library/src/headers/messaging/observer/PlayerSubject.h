
#pragma once


#include "GameObserver.h"

/**
 * @brief The PlayerSubject class
 * This class is used to implement the observer pattern between players and game
 */
class PlayerSubject {
public:
    /**
     * @brief This method is used to register an observer
     * @param observer
     */
    virtual void registerObserver(GameObserver *observer) = 0;

    /**
     * @brief This method is used to unregister an observer
     * @param observer
     */
    virtual void unregisterObserver(GameObserver *observer) = 0;

    /**
     * @brief This method is used to notify the observers
     * @param triggerType
     */
    virtual void notifyObservers(Minion *minion, TriggerType triggerType) = 0;

    /**
     * @brief Subscribe a minion to the actions center
     * @param minion
     */
    virtual void subscribeMinion(Minion *minion) = 0;

    /**
     * @brief Unsubscribe a minion from the actions center
     * @param minion
     */
    virtual void unsubscribeMinion(Minion *minion) = 0;

    /**
     * @brief Subscribe a minion effect to the actions center
     * @param minion
     */
    virtual void subscribeMinionEffect(Minion *minion, const std::unique_ptr<IEffect>& auraEffect) = 0;

    /**
     * @brief Unsubscribes a minion effect from the actions center
     * @param minion
     */
    virtual void unsubscribeMinionEffect(Minion *minion, const std::unique_ptr<IEffect>& auraEffect) = 0;
};
