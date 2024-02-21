
#pragma once

class Player;

class GameObserver {
public:
    /**
     * @brief update
     * This method is called when a trigger is activated
     * @param triggerType The type of the trigger
     * @param player The player that activated the trigger
     * @param triggerType The type of the trigger
     * @param player The player that activated the trigger
     */
    virtual void update(Minion*minion,TriggerType triggerType, Player *player) = 0;

    /**
     * @brief This method is used to subscribe a minion to the actions center
     * @param minion
     */
    virtual void subscribeMinion(Minion *minion) = 0;

    /**
     * @brief This method is used to unsubscribe a minion from the actions center
     * @param minion
     */
    virtual void unsubscribeMinion(Minion *minion) = 0;

    /**
     * @brief This method is used to subscribe a minion effect to the actions center
     * @param minion
     */
    virtual void subscribeMinionEffect(Minion *minion, const std::unique_ptr<IEffect>& auraEffect) = 0;

    /**
     * @brief This method is used to unsubscribe a minion effect from the actions center
     * @param minion
     */
    virtual void unsubscribeMinionEffect(Minion *minion, const std::unique_ptr<IEffect>& auraEffect) = 0;
};