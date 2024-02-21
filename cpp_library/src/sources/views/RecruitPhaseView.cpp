#include "../../headers/views/RecruitPhaseView.h"
#include "config/OptionKeys.h"
#include "utils/Utils.h"
#include <iostream>

void RecruitPhaseView::displayRecruitPhaseInfo(const Player *player, const std::vector<Minion> *minionsToPurchase) {
    displayPlayerInfo(player);
    displayMinionsToPurchase(minionsToPurchase);
}

void RecruitPhaseView::displayChooseTargetsInfo() {
    std::cout << "Choose the target for the anyMinion battlecry:" << std::endl;
    std::cout << "1. Target a minion from the board" << std::endl;
    std::cout << "2. Target a minion from minions to purchase" << std::endl;
}

void RecruitPhaseView::displayOptions( Player *player) {
    std::cout << "Choose an option:" << std::endl;
    std::cout << OptionKeys::OPTION_REFRESH_MINIONS << " - Refresh minions to purchase"
              << getSufficientFundsInfo(player->getRefreshCost(), player) << std::endl;
    std::cout << OptionKeys::OPTION_FREEZE << " - Freeze/unfreeze minions" << std::endl;
    std::cout << OptionKeys::OPTION_LEVEL_UP << " - Level up" << getSufficientFundsInfo(player->getLevelUpCost(), player) << std::endl;
    std::cout << OptionKeys::OPTION_BUY_MINION << " - Buy minion" << getSufficientFundsInfo(player->getBuyCost(), player) << std::endl;
    std::cout << OptionKeys::OPTION_SELL_MINION << " - Sell minion" << std::endl;
    std::cout << OptionKeys::OPTION_DISPLAY_MINIONS_IN_HAND << " - Print hand" << std::endl;
    std::cout << OptionKeys::OPTION_DISPLAY_PLAYER_INFO << " - Print player info" << std::endl;
    std::cout << OptionKeys::OPTION_PLAY_MINION << " - Play minion" << std::endl;
    std::cout << OptionKeys::OPTION_SWAP_MINIONS << " - Swap minions on board" << std::endl;
    std::cout << OptionKeys::OPTION_END_TURN << " - End turn" << std::endl;
}

void RecruitPhaseView::displayError(const std::string &message) {
    std::cout << "Error: " << message << std::endl;
}

void RecruitPhaseView::displayPlayerInfo(const Player *player) {
    std::cout << "Player: " << player->getName() << ", Health: " << player->getHealthPoints()
              << ", Armor: " << player->getArmor() << std::endl;
    std::cout << "Gold: " << player->getCurrentGold() << "/" << player->getMaxGold() <<
              ", Tavern Tier: " << player->getTavernTier() << std::endl << std::endl;
}

void RecruitPhaseView::displayMinionsInHand(const Player *player) {
    if (player->getHand().empty()) {
        std::cout << "You have an empty hand!" << std::endl;
        return;
    } else {
        std::cout << "Minions in hand:" << std::endl;
        int i = 1;
        for (const auto &minion: player->getHand()) {
            std::cout << i << " - ";
            std::cout << "Minion Type: " << Utils::getMinionTypeString(minion.getType()) <<
                      " - Name: " << minion.getName() <<
                      " - Attack/Health: " << minion.getAttack() << "/" << minion.getHealthPoints() <<
                      " - Tavern Tier: " << minion.getTavernTier() << std::endl;
            std::cout << std::endl;
            i++;
        }
    }
}

void RecruitPhaseView::displayMinionsToPurchase(const std::vector<Minion> *minionsToPurchase) {
    std::cout << "Minions available to purchase:" << std::endl;
    int i = 1;
    for (const auto &minion: *minionsToPurchase) {
        std::cout << i << " - ";
        std::cout << "Minion Type: " << Utils::getMinionTypeString(minion.getType()) <<
                  " - Name: " << minion.getName() <<
                  " - Attack/Health: " << minion.getAttack() << "/" << minion.getHealthPoints() <<
                  " - Tavern Tier: " << minion.getTavernTier() << std::endl;
        std::cout << std::endl;
        i++;
    }
}

std::string RecruitPhaseView::getSufficientFundsInfo(int cost, const Player *player) {
    if (player->getCurrentGold() >= cost) {
        return " [Cost: " + std::to_string(cost) + "]";
    } else {
        return " [Cost: " + std::to_string(cost) + " (Insufficient funds)]";
    }
}

void RecruitPhaseView::displayBoard( Player *player) {
    std::cout << "Your board:" << std::endl;
    if (player->getBoard().empty()) {
        std::cout << "You have no minions on board!" << std::endl;
        return;
    }
    int i = 1;
    for (const auto &minion: player->getBoard()) {
        std::cout << i << " - ";
        std::cout << "Minion Type: " << Utils::getMinionTypeString(minion->getType()) <<
                  " - Name: " << minion->getName() <<
                  " - Attack/Health: " << minion->getAttack() << "/" << minion->getHealthPoints() <<
                  " - Tavern Tier: " << minion->getTavernTier() << std::endl;
        std::cout << std::endl;
        i++;
    }
}

void RecruitPhaseView::boardToDisplay(const std::vector<Minion *> vectorToDisplay) {
    std::cout << "Board:" << std::endl;
    int i = 1;
    for (const auto &minion: vectorToDisplay) {
        std::cout << i << " - ";
        std::cout << "Minion Type: " << Utils::getMinionTypeString(minion->getType()) <<
                  " - Name: " << minion->getName() <<
                  " - Attack/Health: " << minion->getAttack() << "/" << minion->getHealthPoints() <<
                  " - Tavern Tier: " << minion->getTavernTier() << std::endl;
        std::cout << std::endl;
        i++;
    }
}


