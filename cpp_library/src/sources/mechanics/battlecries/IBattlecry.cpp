#include "../../../headers/mechanics/battlecries/IBattlecry.h"

const std::string &IBattlecry::getDescription() const {
    return description;
}

IBattlecry::IBattlecry(const std::string &description, const BattlecryTargetCriteria &targetCriteria) :
        description(
                description),
        targetCriteria(
                targetCriteria) {

}

const BattlecryTargetCriteria &IBattlecry::getTargetCriteria() const {
    return targetCriteria;
}

BattlecryTargetCriteria &IBattlecry::getTargetCriteria() {
    return targetCriteria;
}

