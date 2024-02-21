#include "controllers/phases/RecruitPhaseController.h"
#include "utils/Utils.h"
#include "builders/MinionBuilder.h"
#include "mechanics/effects/IEffect.h"
#include "config/OptionKeys.h"

void RecruitPhaseController::update(TriggerType triggerType) {
    update(nullptr, triggerType, nullptr);
}


void RecruitPhaseController::update(Minion *minion, TriggerType triggerType, Player *player) {
    if (totalNodes == maxNodes)
        return;
    bool isFirst = this->root == nullptr;


    /*if (minion != nullptr && player != nullptr) {
        std::cout << "Message " << "from minion "
                  << minion->getName()
                  <<
                  "\n from player " << player->getName() << ":\n" << Utils::getTriggerTypeString(triggerType)
                  << std::endl;
    } else
        std::cout << "Message "
                  << Utils::getTriggerTypeString(triggerType)
                  << std::endl;*/

    std::vector<std::tuple<Minion *, std::unique_ptr<IEffect>>> effectsToExecute;
    std::vector<Minion *> minions(actionsCenter->getActionsMap()[triggerType].begin(),
                                  actionsCenter->getActionsMap()[triggerType].end());

    if (minions.empty())
        actionsCenter->getActionsMap().erase(triggerType);

    for (auto &subscribedMinion: minions) {
        const auto &effects = subscribedMinion->getEffects();
        for (const auto &effect: effects) {
            /*
            if minion effect is triggered by a that trigger type
                (e.g. if the effect is triggered by after a minion attacks, the trigger type must be afterAttack)
            and if the minion that triggered the effect is a valid source
                (e.g. if the effect is triggered by a friendly minion, the source must be a friendly minion)
            and if the minion that triggered the effect passes the filter
                (e.g. if the effect is triggered by a pirate, the source must be a pirate)
            only then execute the effect
             */
            if (effect->getTriggerType() == triggerType &&
                effect->getSourceCriteria().checkTriggerValidity(minion, subscribedMinion) &&
                effect->getSourceCriteria().applyFilter(*subscribedMinion)) {
                effectsToExecute.emplace_back(subscribedMinion, effect->clone());
            }
        }
    }


    if (effectsToExecute.empty()) {
        return;
    }

    if (root == nullptr) {
        root = new TreeNode(triggerType);
        totalNodes++;
        lastNode = root;
    }


    sortEffects(effectsToExecute);
    for (const auto &tuple: effectsToExecute) {
        auto minionPtr = std::get<0>(tuple);
        auto *effectNode = new TreeNode(std::get<1>(tuple)->clone(), minionPtr, this);
        lastNode->addChild(effectNode);
        totalNodes++;
    }


    if (isFirst) {
        std::cout << "DFS TRAVERSAL" << std::endl;
        traverse(root);
    }
    if (totalNodes == visitedNodes && totalNodes != 0) {
        totalNodes = 0;
        visitedNodes = 0;
        root = nullptr;
        lastNode = nullptr;
        checkForDeadMinions();
    }
}

void RecruitPhaseController::subscribeMinion(Minion *minion) {
    actionsCenter->subscribe(minion);
}

void RecruitPhaseController::unsubscribeMinion(Minion *minion) {
    actionsCenter->unsubscribe(minion);
}

Player *RecruitPhaseController::getFriendlyPlayer(Minion *minion) {
    return player;
}

Player *RecruitPhaseController::getEnemyPlayer(Minion *minion) {
    return nullptr;
}

void RecruitPhaseController::init() {
    for (auto &minion: player->getBoard()) {
        subscribeMinion(minion);
    }
    player->registerObserver(this);

}

RecruitPhaseController::RecruitPhaseController(Player *player, MinionPool *minionPool, int currentTurn)
        : currentTurn(currentTurn),
          player(player), minionPool(
                minionPool) {
    actionsCenter = std::make_unique<ActionsCenter>();
}

void RecruitPhaseController::beginTurn() {
    if (currentTurn != 1) {
        player->increaseStartOfTurnGold();
        player->setCurrentGold(player->getStartOfTurnGold());
    }
    currentTurn++;
    if (isFrozen)
        isFrozen = false;
    else
        refreshMinionsToPurchase();

    recruitPhaseView.displayRecruitPhaseInfo(player, &minionsToPurchase);
    while (true) {
        recruitPhaseView.displayBoard(player);
        recruitPhaseView.displayOptions(player);


        // Get user input for the selected option
        std::string userInput = userInputController.getUserInput("Enter your choice: ");

        // Convert user input to an integer (assuming it's a valid integer)
        std::string option = userInput;

        if (option == "0")
            break;

        try {
            handleOption(option);
        }
        catch (std::invalid_argument &e) {
            RecruitPhaseView::displayError(e.what());
        }
    }
    player->notifyObservers(nullptr, TriggerType::endOfTurn);

    player->unregisterObserver(this);

}


void RecruitPhaseController::refreshMinionsToPurchase() {
    //first we return the minions we didn't purchase to global minion pool
    std::lock_guard<std::mutex> lock(minionPoolMutex);
    for (auto const &minion: minionsToPurchase) {

        minionPool->addMinions(minion.getCardKey(), minion.getTavernTier(), 1);
    }
    //then we get new minions and remove them from global minion pool
    int max = player->getMaxMinionsForTier();

    auto keys = minionPool->getRandomMinionKeysForTier(max, player->getTavernTier());
    minionsToPurchase.clear();
    for (auto const &key: keys) {
        auto minion = MinionBuilder::getMinion(key);
        minionPool->removeMinion(key, minion.getTavernTier());
        minionsToPurchase.push_back(minion);
    }
}

void RecruitPhaseController::changeFreeze() {
    isFrozen = !isFrozen;
}

void RecruitPhaseController::handleOption(const std::string &option) {
    switch (option[0]) {
        case OptionKeys::OPTION_REFRESH_MINIONS:
            handleRefreshMinionsOption();
            break;
        case OptionKeys::OPTION_FREEZE:
            changeFreeze();
            break;
        case OptionKeys::OPTION_LEVEL_UP:
            handleLevelUpOption();
            break;
        case OptionKeys::OPTION_BUY_MINION:
            handleBuyMinionOption();
            break;
        case OptionKeys::OPTION_SELL_MINION:
            handleSellMinionOption();
            break;
        case OptionKeys::OPTION_DISPLAY_MINIONS_IN_HAND:
            recruitPhaseView.displayMinionsInHand(player);
            break;
        case OptionKeys::OPTION_DISPLAY_PLAYER_INFO:
            recruitPhaseView.displayPlayerInfo(player);
            break;
        case OptionKeys::OPTION_PLAY_MINION:
            handlePlayMinionOption();
            break;
        case OptionKeys::OPTION_SWAP_MINIONS:
            handleSwapMinionsOption();
            break;
        case OptionKeys::OPTION_END_TURN:
            // End turn
            return;
        default:
            throw std::invalid_argument("Invalid option");
    }
}


void RecruitPhaseController::handleBuyMinionOption() {
    if (player->getCurrentGold() < player->getBuyCost()) {
        RecruitPhaseView::displayError("Not enough gold");
        return;
    }
    if (minionsToPurchase.empty()) {
        RecruitPhaseView::displayError("No minions available to purchase");
        return;
    }
    if (player->getBoard().size() == player->getMaxMinionsInHand()) {
        RecruitPhaseView::displayError("Hand is full");
        return;
    }

    // Get user input for the selected minion to buy
    std::string userInputMinion = userInputController.getUserInput("Enter the minion number to buy: ");
    int minionIndex = std::stoi(userInputMinion);

    if (minionIndex < 1 || minionIndex > minionsToPurchase.size()) {
        RecruitPhaseView::displayError("Invalid minion number");
        return;
    }

    // Add the selected minion to the player's hand
    Minion selectedMinion = minionsToPurchase[minionIndex - 1];
    player->spendGold(player->getLevelUpCost());
    player->addMinionToHand(selectedMinion);

    // Remove the bought minion from the available minions
    minionsToPurchase.erase(minionsToPurchase.begin() + (minionIndex - 1));
    recruitPhaseView.displayMinionsInHand(player);
    recruitPhaseView.displayMinionsToPurchase(&minionsToPurchase);

}

void RecruitPhaseController::handleLevelUpOption() {
    if (player->getCurrentGold() < player->getLevelUpCost()) {
        RecruitPhaseView::displayError("Not enough gold");
        return;
    }
    player->spendGold(player->getLevelUpCost());
    player->levelUp();

}

void RecruitPhaseController::handleRefreshMinionsOption() {
    if (player->getCurrentGold() < player->getRefreshCost()) {
        RecruitPhaseView::displayError("Not enough gold");
        return;
    }
    player->spendGold(player->getRefreshCost());
    refreshMinionsToPurchase();
    recruitPhaseView.displayMinionsToPurchase(&minionsToPurchase);

}

void RecruitPhaseController::handleSellMinionOption() {
    if (player->getBoard().empty()) {
        RecruitPhaseView::displayError("You have no minions on the board");
        return;
    }

    // Display minions on the board
    recruitPhaseView.displayBoard(player);

    // Get user input for the selected minion to sell
    std::string userInputMinion = userInputController.getUserInput(
            "Enter the index of the minion on the board to sell: ");
    int minionIndex = std::stoi(userInputMinion);

    // Validate the selected index
    if (minionIndex < 1 || minionIndex > player->getBoard().size()) {
        RecruitPhaseView::displayError("Invalid minion index");
        return;
    }

    // Remove the selected minion from the player's board
    auto selectedMinion = player->getBoard()[minionIndex - 1];
    player->removeMinionFromBoardById(selectedMinion->getId());
    player->addGold(selectedMinion->getSellCost());
    std::lock_guard<std::mutex> lock(minionPoolMutex);
    minionPool->addMinions(selectedMinion->getCardKey(), selectedMinion->getTavernTier(), 1);

    // Display updated information
    recruitPhaseView.displayBoard(player);
}


void RecruitPhaseController::handlePlayMinionOption() {
    if (player->getHand().empty()) {
        RecruitPhaseView::displayError("You have no minions in hand");
        return;
    }
    if (player->getBoard().size() == player->getMaxMinionsOnBoard()) {
        RecruitPhaseView::displayError("Board is full");
        return;
    }
    recruitPhaseView.displayMinionsInHand(player);

    // Get user input for selecting a minion from hand
    int selectedMinionIndex;
    std::string userInputMinion = userInputController.getUserInput("Select a minion to play (enter the index): ");
    selectedMinionIndex = std::stoi(userInputMinion);

    // Validate the selected index
    if (selectedMinionIndex < 0 || selectedMinionIndex > player->getHand().size()) {
        RecruitPhaseView::displayError("Invalid minion index");
        return;
    }

    // Get the selected minion from hand
    auto selectedMinion = &(player->getHand()[selectedMinionIndex - 1]);

    //minion doesnt have battlecries, so we can just add it to board
    if (selectedMinion->getBattlecries().empty()) {

        auto minionToAdd = Minion(player->getHand()[selectedMinionIndex - 1]);
        player->removeMinionFromHand(*selectedMinion);
        player->addMinionToBoard(minionToAdd);

    } else {
        //minion is first summonned and then battlecries are executed
        player->removeMinionFromHand(*selectedMinion);
        auto minionToAdd = Minion(player->getHand()[selectedMinionIndex - 1]);
        player->addMinionToBoard(minionToAdd);

        for (auto const &battlecry: player->getMinionFromBoardById(selectedMinion->getId())->getBattlecries()) {
            setBattlecryTargets(*player->getMinionFromBoardById(selectedMinion->getId()),
                                player->getMinionFromBoardById(selectedMinion->getId())->getBattlecries()[0]);
        }

        for (auto const &battlecry: player->getMinionFromBoardById(selectedMinion->getId())->getBattlecries()) {
            root = new TreeNode(battlecry->clone(), this);
            totalNodes++;
            lastNode = root;
            traverse(root);
        }

        // Remove the played minion from the player's hand

        // Display updated information
        recruitPhaseView.displayMinionsInHand(player);
        recruitPhaseView.displayMinionsToPurchase(&minionsToPurchase);
    }
}

void
RecruitPhaseController::setBattlecryTargets(Minion &minion, std::unique_ptr<IBattlecry> &battlecryToTrigger) {

    if (battlecryToTrigger->getTargetCriteria().getBattlecryTargets() == BattlecryTargets::anyFriendlyMinion) {
        setFriendlyMinionBattlecryTargets(minion, battlecryToTrigger);
    } else if (battlecryToTrigger->getTargetCriteria().getBattlecryTargets() == BattlecryTargets::self) {
        setSelfBattlecryTargets(minion, battlecryToTrigger);
    } else if (battlecryToTrigger->getTargetCriteria().getBattlecryTargets() ==
               BattlecryTargets::allFriendlyMinions) {
        setAllFriendlyMinionsBattlecryTargets(minion, battlecryToTrigger);
    } else if (battlecryToTrigger->getTargetCriteria().getBattlecryTargets() == BattlecryTargets::friendlyPlayer) {
        setFriendlyPlayerBattlecryTargets(minion, battlecryToTrigger);
    } else if (battlecryToTrigger->getTargetCriteria().getBattlecryTargets() == BattlecryTargets::anyMinion) {
        setAnyMinionBattlecryTargets(minion, battlecryToTrigger);

    } else if (battlecryToTrigger->getTargetCriteria().getBattlecryTargets() ==
               BattlecryTargets::allOtherFriendlyMinions) {
        setAllOtherFriendlyMinionsBattlecryTargets(minion, battlecryToTrigger);
    } else {
        throw std::invalid_argument("Invalid battlecry target");
    }


}

void RecruitPhaseController::setFriendlyMinionBattlecryTargets(Minion &minion,
                                                               std::unique_ptr<IBattlecry> &battlecryToTrigger) {

    //first we check if board isnt empty
    if (player->getBoard().empty()) {
        battlecryToTrigger->setTargets({});
        return;
    }

    //then  we check if all minions arent filtered out
    bool allMinionsFilteredOut = true;
    for (const auto &boardMinion: player->getBoard()) {
        if (battlecryToTrigger->getTargetCriteria().applyFilter(*boardMinion)) {
            allMinionsFilteredOut = false;
            break;
        }
    }
    if (allMinionsFilteredOut) {
        battlecryToTrigger->setTargets({});
        return;
    }

    // We displayPlayers the friendly minions on the board with filter applied
    auto friendlyMinions = player->getBoard();

    std::vector<Minion *> filteredFriendlyMinions;
    for (auto &friendlyMinion: friendlyMinions) {
        if (battlecryToTrigger->getTargetCriteria().applyFilter(*friendlyMinion)) {
            filteredFriendlyMinions.push_back(friendlyMinion);
        }
    }
    recruitPhaseView.boardToDisplay(filteredFriendlyMinions);

    // Get user input for choosing a friendly minion
    int selectedMinionIndex;
    std::string userInputMinion = userInputController.getUserInput("Enter the index of the friendly minion: ");
    selectedMinionIndex = std::stoi(userInputMinion);

    // Validate the selected index
    if (selectedMinionIndex < 1 || selectedMinionIndex > filteredFriendlyMinions.size()) {
        RecruitPhaseView::displayError("Invalid minion index");
        return;
    }

    // Set the chosen minion as the target for the battlecries
    Minion *chosenMinion = player->getMinionFromBoardById(
            filteredFriendlyMinions[selectedMinionIndex - 1]->getId());
    std::vector<Minion *> battlecryTargets = {chosenMinion};

    // Set the targets for the battlecries
    battlecryToTrigger->setTargets(battlecryTargets);
}

void
RecruitPhaseController::setSelfBattlecryTargets(Minion &minion, std::unique_ptr<IBattlecry> &battlecryToTrigger) {
    // For BattlecryTargets::self, the target is the minion itself
    std::vector<Minion *> battlecryTargets = {&minion};

    // Set the targets for the battlecries
    battlecryToTrigger->setTargets(battlecryTargets);
}

void RecruitPhaseController::setAllFriendlyMinionsBattlecryTargets(Minion &minion,
                                                                   std::unique_ptr<IBattlecry> &battlecryToTrigger) {
    // Set the targets for the battlecries to all friendly minions on the board
    std::vector<Minion *> battlecryTargets;
    battlecryTargets.reserve(player->getBoard().size());
    for (auto &friendlyMinion: player->getBoard()) {
        battlecryTargets.push_back(friendlyMinion);
    }
    // Set the targets for the battlecries
    battlecryToTrigger->setTargets(battlecryTargets);
}

void RecruitPhaseController::setFriendlyPlayerBattlecryTargets(Minion &minion,
                                                               std::unique_ptr<IBattlecry> &battlecryToTrigger) {
    // Set the targets for the battlecries to the friendly player
    // Set the targets for the battlecries
    battlecryToTrigger->setTargets(player);
}

void RecruitPhaseController::setAnyMinionBattlecryTargets(Minion &minion,
                                                          std::unique_ptr<IBattlecry> &battlecryToTrigger) {
    recruitPhaseView.displayChooseTargetsInfo();

    // Get user input for the selected option
    std::string userInput = userInputController.getUserInput("Enter your choice: ");
    int option = std::stoi(userInput);

    if (option == 1) {
        // Target a minion from the board
        setFriendlyMinionBattlecryTargets(minion, battlecryToTrigger);
    } else if (option == 2) {
        // Target a minion from minionsToPurchase
        setMinionsToPurchaseBattlecryTargets(minion, battlecryToTrigger);
    } else {
        RecruitPhaseView::displayError("Invalid option");
    }
}

void RecruitPhaseController::setMinionsToPurchaseBattlecryTargets(Minion &minion,
                                                                  std::unique_ptr<IBattlecry> &battlecryToTrigger) {
    // Check if minionsToPurchase isn't empty
    if (minionsToPurchase.empty()) {
        battlecryToTrigger->setTargets({});
        return;
    }


    // We displayPlayers the friendly minions on the board with filter applied

    std::vector<Minion *> filteredMinionsToPurchase;
    for (auto &minionToPurchase: minionsToPurchase) {
        if (battlecryToTrigger->getTargetCriteria().applyFilter(minionToPurchase)) {
            filteredMinionsToPurchase.push_back(&minionToPurchase);
        }
    }
    recruitPhaseView.boardToDisplay(filteredMinionsToPurchase);

    // Get user input for choosing a minion from minionsToPurchase
    int selectedMinionIndex;
    std::string userInputMinion = userInputController.getUserInput("Enter the index of the minion to target: ");
    selectedMinionIndex = std::stoi(userInputMinion);

    // Validate the selected index
    if (selectedMinionIndex < 1 || selectedMinionIndex > filteredMinionsToPurchase.size()) {
        RecruitPhaseView::displayError("Invalid minion index");
        return;
    }

    // Set the chosen minion as the target for the battlecries
    Minion *chosenMinion = &getMinionToPurchaseWithId(filteredMinionsToPurchase[selectedMinionIndex - 1]->getId());;
    std::vector<Minion *> battlecryTargets = {chosenMinion};

    // Set the targets for the battlecries
    battlecryToTrigger->setTargets(battlecryTargets);
}

Minion &RecruitPhaseController::getMinionToPurchaseWithId(const std::string &basicString) {
    for (auto &minion: minionsToPurchase) {
        if (minion.getId() == basicString)
            return minion;
    }
    throw std::invalid_argument("Minion not found");
}

void RecruitPhaseController::setAllOtherFriendlyMinionsBattlecryTargets(Minion &minion,
                                                                        std::unique_ptr<IBattlecry> &battlecryToTrigger) {
    // Set the targets for the battlecries to all other friendly minions on the board
    std::vector<Minion *> battlecryTargets;
    for (auto &friendlyMinion: player->getBoard()) {
        if (&friendlyMinion->getId() != &minion.getId() &&
            battlecryToTrigger->getTargetCriteria().applyFilter(*friendlyMinion)) {
            battlecryTargets.push_back(friendlyMinion);
        }
    }
    // Set the targets for the battlecries
    battlecryToTrigger->setTargets(battlecryTargets);
}

void RecruitPhaseController::handleSwapMinionsOption() {
    if (player->getBoard().size() < 2) {
        RecruitPhaseView::displayError("Not enough minions on the board to perform a swap");
        return;
    }

    // Get user input for selecting two minions to swap
    int firstMinionIndex;
    int secondMinionIndex;
    std::string userInputFirstMinion = userInputController.getUserInput(
            "Enter the index of the first minion to swap: ");
    std::string userInputSecondMinion = userInputController.getUserInput(
            "Enter the index of the second minion to swap: ");

    firstMinionIndex = std::stoi(userInputFirstMinion);
    secondMinionIndex = std::stoi(userInputSecondMinion);

    // Validate the selected indices
    if (firstMinionIndex < 1 || firstMinionIndex > player->getBoard().size() ||
        secondMinionIndex < 1 || secondMinionIndex > player->getBoard().size()) {
        RecruitPhaseView::displayError("Invalid minion index");
        return;
    }

    // Swap the two selected minions on the board
    std::swap(player->getBoard()[firstMinionIndex - 1], player->getBoard()[secondMinionIndex - 1]);

    // Display updated information
    recruitPhaseView.displayBoard(player);
}

void RecruitPhaseController::subscribeMinionEffect(Minion *minion, const std::unique_ptr<IEffect> &auraEffect) {
    actionsCenter->subscribeEffect(minion, auraEffect);

}

void RecruitPhaseController::unsubscribeMinionEffect(Minion *minion, const std::unique_ptr<IEffect> &auraEffect) {
    actionsCenter->unsubscribeEffect(minion, auraEffect);

}

void
RecruitPhaseController::sortEffects(std::vector<std::tuple<Minion *, std::unique_ptr<IEffect>>> &effectsToExecute) {
    auto customSort = [this](const auto &tuple1, const auto &tuple2) {
        int priority1 = std::get<1>(tuple1)->getPriority();
        int priority2 = std::get<1>(tuple2)->getPriority();
        if (priority1 != priority2) {
            return priority1 < priority2;
        }
        return this->player->getIndexOfMinionById(std::get<0>(tuple1)->getId()) <
               this->player->getIndexOfMinionById(std::get<0>(tuple2)->getId());
    };

    std::sort(effectsToExecute.begin(), effectsToExecute.end(), customSort);
}

void RecruitPhaseController::checkForDeadMinions() {
    for (int i = 0; i < player->getBoard().size(); i++) {
        if (player->getBoard()[i]->getHealthPoints() <= 0) {
            auto minionId = player->getBoard()[i]->getId();
            auto minionCardKey = player->getBoard()[i]->getCardKey();
            update(player->getMinionFromBoardById(minionId), TriggerType::deathrattle, player);
            player->unsubscribeMinion(player->getMinionFromBoardById(minionId));
            player->getMinionFromBoardById(minionId)->unregisterObserver(player);
            player->removeMinionFromBoardById(minionId);
            //player->getMinionFromGraveyardById(minionId) = MinionBuilder::getMinion(minionCardKey);
        }
    }
}



