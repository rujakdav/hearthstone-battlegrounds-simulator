#pragma once

#include <string>
#include <vector>
#include <memory>
#include "mechanics/common/criterias/targets/BattlecryTargetCriterias.h"
#include "../common/IOwned.h"

class RecruitPhaseController;

/**
 * @brief The IBattlecry class
 * This class is used to represent a battlecry
 */
class IBattlecry {
private:
    std::string description; /**< The description of the battlecry */
    BattlecryTargetCriteria targetCriteria; /**< The target criteria of the battlecry */
protected:
    bool targetsSet = false; /**< Indicates if the targets have been set */
public:
    IBattlecry(const std::string &description, const BattlecryTargetCriteria &targetCriteria);

    const BattlecryTargetCriteria &getTargetCriteria() const;

    BattlecryTargetCriteria &getTargetCriteria();

    /**
     * @brief Executes the battlecry
     * @param game
     */
    virtual void execute( RecruitPhaseController *game) = 0;

    /**
     * @brief Clones the battlecry
     * @return std::unique_ptr<IBattlecry>
     */
    virtual std::unique_ptr<IBattlecry> clone() = 0;

    /**
     * @brief Sets the minion targets
     * @param targets
     */
    virtual void setTargets(std::vector<Minion *> targets) = 0;

    /**
     * @brief Sets the player targets
     * @param player
     */
    virtual void setTargets(Player *player) = 0;


    virtual ~IBattlecry() = default;

    const std::string &getDescription() const;
};


