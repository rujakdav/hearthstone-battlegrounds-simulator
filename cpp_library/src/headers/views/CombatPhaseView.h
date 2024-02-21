#pragma once

#include <iostream>
#include "../entities/Player.h"
#include "enums/view/printMode.h"

/**
 * @brief The CombatPhaseView class
 * This class is used to represent the combat phase view
 */
class CombatPhaseView {
private:
    /**
     * @brief The PrintMode enum
     * This enum is used to represent the print mode
     */
    PrintMode printMode = PrintMode::print;
public:
    void setPrintMode(PrintMode printMode);

public:
    /**
     * @brief displayPlayers
     * This method is used to display the basic information of the players
     * @param player1
     * @param player2
     */
    void displayPlayers(Player *player1, Player *player2);

    /**
     * @brief Display the attacking minion
     * @param attackingMinion
     */
    void displayAttackingMinion(Minion *attackingMinion);

    /**
     * @brief Display the defending minion
     * @param attackingMinion
     */
    void displayDefendingMinion(Minion *defendingMinion);

    /**
     * @brief Display the attacking player
     * @param attackingPlayer
     */
    void displayAttackingPlayer(Player *attackingPlayer);

    /**
     * @brief Display the combat result
     * @param winner
     * @param loser
     * @param isDraw
     */
    void displayCombatResult(Player *winner, Player *loser, bool isDraw);
};




