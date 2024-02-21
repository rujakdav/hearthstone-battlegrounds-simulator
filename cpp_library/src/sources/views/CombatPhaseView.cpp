#include "views/CombatPhaseView.h"

void CombatPhaseView::displayPlayers(Player *player1, Player *player2) {
    if (printMode == PrintMode::noPrint) {
        return;
    }

    //print names and health and armor of players
    std::cout << "Player 1:" << player1->getName() << " " << player1->getHealthPoints() << " " << player1->getArmor()
              << "\n";
    for (auto &minion: player1->getBoard()) {
        std::cout << minion->getName() << " " << minion->getAttack() << " " << minion->getHealthPoints() << "\n";
    }
    std::cout << "Player 2:" << player2->getName() << " " << player2->getHealthPoints() << " " << player2->getArmor()
              << "\n";
    for (auto &minion: player2->getBoard()) {
        std::cout << minion->getName() << " " << minion->getAttack() << " " << minion->getHealthPoints() << "\n";
    }


}

void CombatPhaseView::displayCombatResult(Player *winner, Player *loser, bool isDraw) {
    if (printMode == PrintMode::noPrint) {
        return;
    }

    if (isDraw) {
        std::cout << "Draw!\n";
        return;
    }
    std::cout << "Player " << winner->getName() << " won!\n";
    std::cout << "Damage dealt: " << winner->calculateDamageToDeal() << "\n";
    //std::cout << "Remaining Health of Player " << loser->getName() << ": " << loser->getHealthPoints() << "\n";
}

void CombatPhaseView::displayAttackingMinion(Minion *attackingMinion) {
    if (printMode == PrintMode::noPrint) {
        return;
    }
    std::cout << "Attacking Minion:\n";
    std::cout << attackingMinion->getName() << " " << attackingMinion->getAttack() << " "
              << attackingMinion->getHealthPoints() << "\n";
}

void CombatPhaseView::displayAttackingPlayer(Player *attackingPlayer) {
    if (printMode == PrintMode::noPrint) {
        return;
    }

    std::cout << "Attacking Player:\n";
    std::cout << attackingPlayer->getName() << "\n";

}

void CombatPhaseView::setPrintMode(PrintMode printMode) {
    CombatPhaseView::printMode = printMode;
}

void CombatPhaseView::displayDefendingMinion(Minion *defendingMinion) {
    if (printMode == PrintMode::noPrint) {
        return;
    }
    std::cout << "Defending Minion:\n";
    std::cout << defendingMinion->getName() << " " << defendingMinion->getAttack() << " "
              << defendingMinion->getHealthPoints() << "\n";

}

