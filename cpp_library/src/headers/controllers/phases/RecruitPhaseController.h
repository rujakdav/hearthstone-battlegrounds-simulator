#pragma once
#include "enums/mechanics/common/triggerType.h"
#include "entities/Player.h"
#include "PhaseController.h"
#include "messaging/ActionsCenter.h"
#include "views/RecruitPhaseView.h"
#include "controllers/input/UserInputController.h"
#include <mutex>

/**
 * @brief The RecruitPhaseController class
 * This class is used to control the recruit phase
 */
class RecruitPhaseController : public GameObserver, public PhaseController {
public:
    explicit RecruitPhaseController(Player *player, MinionPool *minionPool, int currentTurn);

    Player *getFriendlyPlayer(Minion *minion) override;

    Player *getEnemyPlayer(Minion *minion) override;

    void init() override;

    void update(TriggerType triggerType);

    void update(Minion *minion, TriggerType triggerType, Player *player) override;

    void subscribeMinion(Minion *minion) override;

    void unsubscribeMinion(Minion *minion) override;

    /**
     * @brief Starts the recruit phase
     */
    void beginTurn();

private:

    bool isFrozen = false; /**< Indicates if the minions to purchase are frozen */
    int currentTurn = 1; /**< The current turn */

    Player *player;
    std::mutex minionPoolMutex;
    MinionPool *minionPool;
    std::vector<Minion> minionsToPurchase; /**< The minions to purchase */
    RecruitPhaseView recruitPhaseView = RecruitPhaseView();
    UserInputController userInputController = UserInputController();

    /**
     * @brief Checks and removes dead minions
     */
    void checkForDeadMinions();

    /**
     * @brief Sorts the effects to execute
     * @param effectsToExecute
     */
    void sortEffects(std::vector<std::tuple<Minion *, std::unique_ptr<IEffect>>> &effectsToExecute);

    void refreshMinionsToPurchase();

    void changeFreeze();

    void handleOption(const std::string &option);

    void subscribeMinionEffect(Minion *minion, const std::unique_ptr<IEffect> &auraEffect) override;

    void unsubscribeMinionEffect(Minion *minion, const std::unique_ptr<IEffect> &auraEffect) override;

    void handleBuyMinionOption();

    void handleLevelUpOption();

    void handleRefreshMinionsOption();

    void handleSellMinionOption();

    void handlePlayMinionOption();

    void setBattlecryTargets(Minion& minion, std::unique_ptr<IBattlecry> &battlecryToTrigger);

    void setFriendlyMinionBattlecryTargets(Minion &minion, std::unique_ptr<IBattlecry> &battlecryToTrigger);

    void setSelfBattlecryTargets(Minion &minion, std::unique_ptr<IBattlecry> &battlecryToTrigger);

    void setAllFriendlyMinionsBattlecryTargets(Minion &minion, std::unique_ptr<IBattlecry> &battlecryToTrigger);

    void setFriendlyPlayerBattlecryTargets(Minion &minion, std::unique_ptr<IBattlecry> &battlecryToTrigger);

    void setAnyMinionBattlecryTargets(Minion &minion, std::unique_ptr<IBattlecry> &battlecryToTrigger);

    void setMinionsToPurchaseBattlecryTargets(Minion &minion, std::unique_ptr<IBattlecry> &battlecryToTrigger);

    Minion &getMinionToPurchaseWithId(const std::string &basicString);

    void setAllOtherFriendlyMinionsBattlecryTargets(Minion &minion, std::unique_ptr<IBattlecry> &battlecryToTrigger);

    void handleSwapMinionsOption();
};



