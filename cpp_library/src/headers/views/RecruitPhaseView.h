#pragma once

#include "../entities/Player.h"
#include "../entities/Minion.h"
#include <vector>
#include <string>

/**
 * @brief The RecruitPhaseView class
 * This class is used to represent the recruit phase view
 */
class RecruitPhaseView {

public:
    /**
     * @brief displayRecruitPhaseInfo
     * This method is used to display the recruit phase info
     * @param player
     * @param minionsToPurchase
     */
    void displayRecruitPhaseInfo(const Player *player, const std::vector<Minion> *minionsToPurchase);

    /**
     * @brief This method is used to display the choose targets info
     */
    static void displayChooseTargetsInfo();

    /**
     * @Brief Displays the options of recruit phase
     * @param player
     */
    void displayOptions( Player *player);


    /**
     * @brief This method is used to display the error
     */
    static void displayError(const std::string &message);


    /**
     * @Brief Displays the player info
     * @param player
     */
    void displayPlayerInfo(const Player *player);

    /**
     * @brief This method is used to display the minion info
     * @param player
     */
    void displayMinionsInHand(const Player *player);

    /**
     * @brief This method is used to display the minions to purchase
     * @param minionsToPurchase
     */
    void displayMinionsToPurchase(const std::vector<Minion> *minionsToPurchase);

    /**
     * @brief This method is used to display the sufficient funds info
     * @param cost
     * @param player
     * @return
     */
    std::string getSufficientFundsInfo(int cost, const Player *player);

    /**
     * @brief This method is used to display the board of the player
     * @param player
     */
    void displayBoard( Player *player);

    /**
     * @brief This method is used to display the board of minions
     * @param vectorToDisplay
     */
    static void boardToDisplay(const std::vector<Minion *> vectorToDisplay);

};

