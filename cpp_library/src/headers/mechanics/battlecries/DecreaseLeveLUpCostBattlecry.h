

#include "IBattlecry.h"

/**
 * @brief The DecreaseLeveLUpCostBattlecry class
 * This class is used to represent a battlecry that decreases the level up cost of a player
 */
class DecreaseLeveLUpCostBattlecry: public IBattlecry {
private:
    int amount;
    Player *player;
public:
    DecreaseLeveLUpCostBattlecry(const std::string &description, const BattlecryTargetCriteria &targetCriteria,
                                 int amount);

    void execute(RecruitPhaseController *game) override;

    void setTargets(std::vector<Minion *> targets) override;

    void setTargets(Player *player) override;

    std::unique_ptr<IBattlecry> clone() override;


};


