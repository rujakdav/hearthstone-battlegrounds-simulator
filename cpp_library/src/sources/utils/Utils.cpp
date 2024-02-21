

#include <ctime>
#include <chrono>
#include <iostream>
#include "../../headers/utils/Utils.h"
#include "../../headers/mechanics/effects/IEffect.h"


int Utils::getRandomNumber(int lower, int higher) {
    if (lower == 0 && higher == 0)
        return 0;
    std::random_device engine;
    std::uniform_int_distribution<int> distrib(0, 1);
    return distrib(engine);
}

int Utils::getRandomNumberFromArray(const std::vector<int> &arr) {
    // Seed the random number generator using a time-based seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine engine(seed);

    // Generate a random index within the range of the array=
    int index = getRandomNumber(0, arr.size() - 1);

    // Return the element at the randomly generated index
    //std::cout << "RETURN:" << arr[index] << std::endl;
    return arr[index];
}

std::string Utils::getTriggerTypeString(TriggerType type) {
    switch (type) {
        case TriggerType::none:
            return "none";
        case TriggerType::startOfCombat:
            return "startOfCombat";
        case TriggerType::onAttack:
            return "onAttack";
        case TriggerType::afterAttacked:
            return "afterAttacked";
        case TriggerType::afterSummon:
            return "afterSummon";
        case TriggerType::afterTakeDamage:
            return "afterTakeDamage";
        case TriggerType::deathrattle:
            return "deathrattle";
        case TriggerType::afterDivineShieldLoss:
            return "afterDivineShieldLoss";
        case TriggerType::onHeal:
            return "onHeal";
        case TriggerType::afterAttackIncrease:
            return "afterAttackIncrease";
        default:
            return "Unknown TriggerType";
    }
}


void Utils::printTree(TreeNode *node) const {
    if (node == nullptr)
        return;
    printTreeHelper(node, 0);
}

void Utils::printTreeHelper(const TreeNode *node, int depth) const {
    const int indent = 4; // Adjust the indentation based on your preference

    if (std::holds_alternative<TriggerType>(node->data)) {
        // Print TriggerType
        std::cout << std::string(depth * indent, ' ') << "TriggerType: "
                  << getTriggerTypeString(std::get<TriggerType>(node->data)) << std::endl;
    } else {
        auto effect = std::get<0>(std::get<std::tuple<std::unique_ptr<IEffect>,
                Minion *, PhaseController *>>(node->data))->clone();
        auto minion = std::get<1>(std::get<std::tuple<std::unique_ptr<IEffect>,
                Minion *, PhaseController *>>(node->data));
        std::cout << std::string(depth * indent, ' ') << "Effect: " << effect->getDescription()
                  << ", Minion: " << minion->getName() << std::endl;
    }

    // Recursively print children
    for (const auto &child: node->getChildren()) {
        printTreeHelper(child, depth + 1);
    }
}


std::string Utils::getMinionTypeString(MinionType minionType) {
    switch (minionType) {
        case MinionType::beast:
            return "Beast";
        case MinionType::demon:
            return "Demon";
        case MinionType::dragon:
            return "Dragon";
        case MinionType::elemental:
            return "Elemental";
        case MinionType::mech:
            return "Mech";
        case MinionType::murloc:
            return "Murloc";
        case MinionType::naga:
            return "Naga";
        case MinionType::pirate:
            return "Pirate";
        case MinionType::quilboar:
            return "Quilboar";
        case MinionType::totem:
            return "Totem";
        case MinionType::undead:
            return "Undead";
        case MinionType::all:
            return "All";
        case MinionType::general:
            return "General";
        default:
            return "Unknown";
    }
}

std::string Utils::getTriggerTargetsString(EffectTargets target) {
    switch (target) {
        case EffectTargets::self:
            return "self";
        case EffectTargets::enemyMinions:
            return "enemyMinions";
        case EffectTargets::friendlyMinions:
            return "friendlyMinions";
        case EffectTargets::otherFriendlyMinions:
            return "otherFriendlyMinions";
        case EffectTargets::allMinions:
            return "allMinions";
        case EffectTargets::friendlyPlayer:
            return "friendlyPlayer";
        case EffectTargets::enemyPlayer:
            return "enemyPlayer";
        case EffectTargets::allPlayers:
            return "allPlayers";
        case EffectTargets::none:
            return "none";
        default:
            return "Unknown EffectTargets";
    }
}
