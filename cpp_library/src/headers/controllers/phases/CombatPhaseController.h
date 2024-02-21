#pragma once

#include "entities/Player.h"
#include "PhaseController.h"
#include "views/CombatPhaseView.h"


/**
 * @brief The CombatPhaseController class
 * This class is used to control the combat phase
 */
class CombatPhaseController : public GameObserver, public PhaseController {
private:
    Player *player1;
    Player *player2;
    CombatPhaseView combatPhaseView = CombatPhaseView();
public:

    CombatPhaseController(Player *player1, Player *player2);


    void update(TriggerType triggerType);

    void update(Minion *minion, TriggerType triggerType, Player *player) override;

    /**
     * @brief Executes the combat phase
     */
    void executeCombat();

    void init() override;

    /**
     * @brief Returns the player with the given id
     * @param id
     * @return Player*
     */
    Player *getPlayerById(std::string id);


    Player *getFriendlyPlayer(Minion *minion) override;


    Player *getEnemyPlayer(Minion *minion) override;

    void print();


    void subscribeMinion(Minion *minion) override;

    void unsubscribeMinion(Minion *minion) override;

    void subscribeMinionEffect(Minion *minion, const std::unique_ptr<IEffect> &auraEffect) override;

    void unsubscribeMinionEffect(Minion *minion, const std::unique_ptr<IEffect> &auraEffect) override;

    /**
     * @brief Sets the print mode
     * @param printMode
     */
    void setPrintMode(PrintMode printMode);


    /**
     * @brief Finds the attacker minion index
     * @param attackerPlayerIndex
     * @param defenderPlayerIndex
     */
    int findAttacker(Player *player);

    /**
     * @brief Finds the defender minion index
     * @param attackerPlayerIndex
     * @param defenderPlayerIndex
     */
    int findDefender(Player *player);

    Player *getAttackerPlayer(int attackerPlayerIndex);

    Player *getDefenderPlayer(int attackerPlayerIndex);

    /**
     * @brief Checks and removes dead minions
     */
    void checkForDeadMinions();

    /**
     * @brief Checks if the combat is over
     */
    void checkWinCondition();

    /**
     * @brief Sorts the effects to execute
     * @param effectsToExecute
     */
    void sortEffects(std::vector<std::tuple<Minion *, std::unique_ptr<IEffect>>> &effectsToExecute);
};
