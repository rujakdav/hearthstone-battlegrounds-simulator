#pragma once

#include <vector>
#include "Minion.h"
#include "../components//IArmored.h"
#include "../messaging/observer/PlayerSubject.h"
#include "utils/IDGenerator.h"
#include <iostream>


/**
 * @brief The Player class represents a player in the game
 */
class Player : public IDestructible, public IArmored, public PlayerObserver, public PlayerSubject {


private:
    const int maxMinionsOnBoard = 7; /**< The maximum amount of minions that can be on the board */
    const int maxMinionsInHand = 10;
    int levelUpCost = 5; /**< The cost to level up the tavern */
    int refreshCost = 1; /**< The cost to refresh the tavern */

    int buyCost = 3; /**< The cost to buy a minion */
    std::string name; /**< The name of the player */
    std::string id = IDGenerator::getInstance().generateID(); /**< The id of the player */
    int tavernTier = 1; /**< The tavern tier of the player */
    std::string cardKey; /**< The card key of the player */
    std::vector<Minion *> board; /**< The board containing the minions of the player */
    std::vector<Minion *> graveyard; /**< The graveyard containing the dead minions of the player */
    std::vector<Minion> hand; /**< The hand of the player */
    std::vector<GameObserver *> observers; /**< The observers of the player */
    int currentGold = 3; /**< The current gold of the player */
    int startOfTurnGold = 10; /**< The gold the player starts with */
public:

    const int getMaxMinionsInHand() const;

    int getBuyCost() const;

    void subscribeMinion(Minion *minion) override;


    void unsubscribeMinion(Minion *minion) override;

    void subscribeMinionEffect(Minion *minion, const std::unique_ptr<IEffect> &auraEffect) override;

    virtual void unsubscribeMinionEffect(Minion *minion, const std::unique_ptr<IEffect> &auraEffect) override;

    Minion *getMinionFromGraveyardById(std::string id);

    void removeMinionFromBoardById(std::string minionId);

    void decreaseLevelUpCost();

    int getLevelUpCost() const;

    int getRefreshCost() const;

    const std::vector<Minion> &getHand() const;

    std::vector<Minion> &getHand();

    Minion *getMinionFromBoardById(std::string id);



    /**
     * @brief Adds a minion to the hand
     * @param minion
     */
    void addMinionToHand(Minion minion);

    /**
     * @brief Removes a minion from the hand
     * @param minion
     */
    void removeMinionFromHand(const Minion &minion);


public:
    int getStartOfTurnGold() const;

    int getCurrentGold() const;

    int getMaxGold() const;

    void increaseStartOfTurnGold();

    void setCurrentGold(int currentGold);

    void addGold(int amount);

    void spendGold(int amount);

    bool canAfford(int amount);

    void levelUp();

    int calculateDamageToDeal();

    const std::string &getName() const;


    const std::string &getId() const;

    void registerObserver(GameObserver *observer) override;

    void unregisterObserver(GameObserver *observer) override;

    void notifyObservers(Minion *minion, TriggerType triggerType) override;

    void update(Minion *minion, TriggerType triggerType) override;

    std::vector<Minion*> &getBoard();

    Player(const std::string &name, const std::string &cardKey);
    ~Player();

    const int getMaxMinionsOnBoard() const;

    Player(const Player &other);

    int getTavernTier() const;

    /** Gets the minion from the board by id
     * @param id
     * @return Minion
     */
    int getIndexOfMinionById(std::string minionId);


    /**
     * @brief Returns the maximum amount of minions to purchase for the given tier
     */
    int getMaxMinionsForTier();


    void setBoard(std::vector<Minion*> minions);

    void print() const;

    /**
     * @brief Adds a minion to the board
     * @param minion
     */
    void addMinionToBoard(Minion minion);

    /**
     * @brief Updates the minions on the board with the given aura
     */
    void auraUpdate(const Minion *minionWithAura);

    /**
     * @brief Removes a minion from the board with the given index
     * @param minionToRemove
     */
    void removeMinionFromBoardByIndex(int minionToRemoveIndex);

    void takeDamage(Damage &damage) override;
};