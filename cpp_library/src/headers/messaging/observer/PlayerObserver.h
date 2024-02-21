
#pragma once


#include "enums/mechanics/common/triggerType.h"

class Minion;

/**
 * @brief The PlayerObserver class
 * This class is used to implement the observer pattern between minions and players
 */
class PlayerObserver {
public:
    /**
     * @brief This method is used to update the observer
     * @param minion
     * @param triggerType
     */
    virtual void update(Minion *minion, TriggerType triggerType) = 0;
};