
#pragma once

#include "PlayerObserver.h"
#include "enums/mechanics/common/triggerType.h"

/**
 * @brief The MinionSubject class
 * This class is used to implement the observer pattern between minions and players
 */
class MinionSubject {
public:
    /**
     * @brief This method is used to register an observer
     * @param observer
     */
    virtual void registerObserver(PlayerObserver *observer) = 0;

    /**
     * @brief This method is used to unregister an observer
     * @param observer
     */
    virtual void unregisterObserver(PlayerObserver *observer) = 0;

    /**
     * @brief This method is used to notify the observers
     * @param triggerType
     */
    virtual void notifyObservers(TriggerType triggerType) = 0;
};