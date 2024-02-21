
#pragma once


#include <vector>
#include "enums/mechanics/effects/EffectTargets.h"
#include "entities/Player.h"
#include "mechanics/common/criterias/targets/EffectTargetCriteria.h"
#include "controllers/phases/PhaseController.h"

/**
 * @brief The TargetsBuilder class
 * This class is used to build targets for effects
 */
class TargetsBuilder {
private:
    EffectTargetCriteria& targetsModel; /**< The criteria for the effect targets */
    template <typename T>
    std::vector<T*> castMinions(const std::vector<Minion*>& minions);
    template <typename T>
    std::vector<T*> castPlayers(const std::vector<Player*>& players);
    std::vector<Minion*> getEnemyMinions(Minion *minion, Player *friendlyPlayer, Player *enemyPlayer);
    std::vector<Minion*> getFriendlyMinions(Minion *minion, Player *friendlyPlayer, Player *enemyPlayer);
    std::vector<Minion*> getOtherFriendlyMinions(Minion *minion, Player *friendlyPlayer);
    std::vector<Minion*> getSelfMinion(Minion *minion, Player *friendlyPlayer, Player *enemyPlayer);
    std::vector<Player*> getFriendlyPlayer(Minion *minion, Player *friendlyPlayer);
    std::vector<Player*> getEnemyPlayer(Minion *minion, Player *enemyPlayer);
    std::vector<Player*> getPlayer(Minion *minion, Player *player);
    std::vector<Player*> getAllPlayers(Minion *minion,Player *friendlyPlayer, Player *enemyPlayer);
    std::vector<Minion*> getMinions(Minion *minion, Player *player);

public:
    TargetsBuilder(EffectTargetCriteria& targetsModel);

    /**
     * @brief This method returns instances of IDestructible targets
     * @param minion
     * @param phaseController
     * @return
     *
     */

    std::vector<IDestructible *> getIDestructible(Minion *minion, PhaseController *phaseController);
    /**
     * @brief This method returns instances of IArmored targets
     * @param minion
     * @param phaseController
     * @return
     */

    std::vector<IArmored *> getIArmored(Minion *minion, PhaseController *phaseController);
    /**
     * @brief This method returns instances of IHealable targets
     * @param minion
     * @param phaseController
     * @return
     */

    std::vector<Minion *> getMinions(Minion *minion, PhaseController *phaseController);
    /**
     * @brief This method returns instances of Player targets
     * @param minion
     * @param phaseController
     * @return
     */
    std::vector<Player *> getPlayers(Minion *minion, PhaseController *phaseController);

};
