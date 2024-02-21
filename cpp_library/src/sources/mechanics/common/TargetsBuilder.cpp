
#include "mechanics/common/TargetsBuilder.h"
#include "utils/Utils.h"

TargetsBuilder::TargetsBuilder(EffectTargetCriteria &targetsModel) : targetsModel(targetsModel) {}

template<typename T>
std::vector<T *> TargetsBuilder::castMinions(const std::vector<Minion *> &minions) {
    {
        std::vector<T *> castedVector;
        castedVector.reserve(minions.size());

        for (auto &minion: minions) {
            T *castedObject = static_cast<T *>(minion);
            castedVector.push_back(castedObject);
        }

        return castedVector;
    }
}


template<typename T>
std::vector<T *> TargetsBuilder::castPlayers(const std::vector<Player *> &players) {
    {
        std::vector<T *> castedVector;
        castedVector.reserve(players.size());

        for (auto &player: players) {
            T *castedObject = static_cast<T *>(player);
            castedVector.push_back(castedObject);
        }

        return castedVector;
    }
}


std::vector<IDestructible *>
TargetsBuilder::getIDestructible(Minion *minion, PhaseController *phaseController) {

    if (this->targetsModel.getTriggerTargets() == EffectTargets::enemyMinions) {
        return castMinions<IDestructible>(getEnemyMinions(minion, phaseController->getFriendlyPlayer(minion),
                                                          phaseController->getEnemyPlayer(minion)));
    } else if (this->targetsModel.getTriggerTargets() == EffectTargets::friendlyMinions) {
        return castMinions<IDestructible>(getFriendlyMinions(minion, phaseController->getFriendlyPlayer(minion),
                                                             phaseController->getEnemyPlayer(minion)));
    } else if (this->targetsModel.getTriggerTargets() == EffectTargets::otherFriendlyMinions) {
        return castMinions<IDestructible>(getOtherFriendlyMinions(minion, phaseController->getFriendlyPlayer(minion)));
    } else if (this->targetsModel.getTriggerTargets() == EffectTargets::allMinions) {
        std::vector<IDestructible *> returnVector;
        auto friendlyMinions = getFriendlyMinions(minion, phaseController->getFriendlyPlayer(minion),
                                                  phaseController->getEnemyPlayer(minion));
        auto enemyMinions = getEnemyMinions(minion, phaseController->getFriendlyPlayer(minion),
                                            phaseController->getEnemyPlayer(minion));
        returnVector.insert(returnVector.end(), friendlyMinions.begin(), friendlyMinions.end());
        returnVector.insert(returnVector.end(), enemyMinions.begin(), enemyMinions.end());
        return returnVector;
    } else if (this->targetsModel.getTriggerTargets() == EffectTargets::self) {
        return castMinions<IDestructible>(getSelfMinion(minion, phaseController->getFriendlyPlayer(minion),
                                                        phaseController->getEnemyPlayer(minion)));
    } else if (this->targetsModel.getTriggerTargets() == EffectTargets::friendlyPlayer) {
        return castPlayers<IDestructible>(getFriendlyPlayer(minion, phaseController->getFriendlyPlayer(minion)));
    } else if (this->targetsModel.getTriggerTargets() == EffectTargets::enemyPlayer) {
        return castPlayers<IDestructible>(getEnemyPlayer(minion, phaseController->getEnemyPlayer(minion)));
    } else if (this->targetsModel.getTriggerTargets() == EffectTargets::allPlayers) {
        return castPlayers<IDestructible>(getAllPlayers(minion, phaseController->getFriendlyPlayer(minion),
                                                        phaseController->getEnemyPlayer(minion)));
    } else
        throw std::invalid_argument("Invalid IDestructible target: " + Utils::getTriggerTargetsString(
                this->targetsModel.getTriggerTargets()));

}

std::vector<IArmored *> TargetsBuilder::getIArmored(Minion *minion, PhaseController *phaseController) {
    std::vector<IArmored *> returnVector;
    if (this->targetsModel.getTriggerTargets() == EffectTargets::friendlyPlayer) {
        return castPlayers<IArmored>(getFriendlyPlayer(minion, phaseController->getFriendlyPlayer(minion)));
    } else if (this->targetsModel.getTriggerTargets() == EffectTargets::enemyPlayer) {
        return castPlayers<IArmored>(getEnemyPlayer(minion, phaseController->getEnemyPlayer(minion)));
    } else if (this->targetsModel.getTriggerTargets() == EffectTargets::allPlayers) {
        return castPlayers<IArmored>(getAllPlayers(minion, phaseController->getFriendlyPlayer(minion),
                                                   phaseController->getEnemyPlayer(minion)));
    }
    throw std::invalid_argument("Invalid IArmored target: " + Utils::getTriggerTargetsString(
            this->targetsModel.getTriggerTargets()));
}


std::vector<Minion *> TargetsBuilder::getEnemyMinions(Minion *minion, Player *friendlyPlayer, Player *enemyPlayer) {
    if (enemyPlayer == nullptr)
        return {};
    return getMinions(minion, enemyPlayer);
}

std::vector<Minion *>
TargetsBuilder::getFriendlyMinions(Minion *minion, Player *friendlyPlayer, Player *enemyPlayer) {
    return getMinions(minion, friendlyPlayer);
}

std::vector<Minion *> TargetsBuilder::getMinions(Minion *minion, Player *player) {
    std::vector<Minion *> returnVector;
    for (auto &i: player->getBoard()) {
        Minion *minionToAdd = i;
        if (this->targetsModel.applyFilter(*i)) {
            returnVector.push_back(minionToAdd);
        }
    }
    if (this->targetsModel.isRandom())
        returnVector = Utils::GetNElements(returnVector, this->targetsModel.getHowManyRandomTargets());
    return returnVector;
}

std::vector<Minion *>
TargetsBuilder::getOtherFriendlyMinions(Minion *minion, Player *friendlyPlayer) {
    std::vector<Minion *> returnVector;
    for (auto &i: friendlyPlayer->getBoard()) {
        Minion *minionToAdd = i;
        if (this->targetsModel.applyFilter(*i) && minionToAdd != minion) {
            returnVector.push_back(minionToAdd);
        }
    }
    if (this->targetsModel.isRandom())
        returnVector = Utils::GetNElements(returnVector, this->targetsModel.getHowManyRandomTargets());
    return returnVector;
}

std::vector<Player *> TargetsBuilder::getFriendlyPlayer(Minion *minion, Player *friendlyPlayer) {
    return getPlayer(minion, friendlyPlayer);
}

std::vector<Player *> TargetsBuilder::getEnemyPlayer(Minion *minion, Player *enemyPlayer) {
    return getPlayer(minion, enemyPlayer);
}

std::vector<Player *> TargetsBuilder::getAllPlayers(Minion *minion, Player *friendlyPlayer, Player *enemyPlayer) {
    std::vector<Player *> returnVector;
    if (this->targetsModel.applyFilter(*friendlyPlayer))
        returnVector.push_back(friendlyPlayer);
    if (enemyPlayer != nullptr && this->targetsModel.applyFilter(*enemyPlayer)) {
        returnVector.push_back(enemyPlayer);
    }


    return returnVector;
}


std::vector<Player *> TargetsBuilder::getPlayer(Minion *minion, Player *player) {
    if (this->targetsModel.applyFilter(*player))
        return {player};
    return {};
}


std::vector<Player *> TargetsBuilder::getPlayers(Minion *minion, PhaseController *phaseController) {
    std::vector<Player *> returnVector;
    if (this->targetsModel.getTriggerTargets() == EffectTargets::enemyPlayer) {
        return getEnemyPlayer(minion, phaseController->getEnemyPlayer(minion));
    } else if (this->targetsModel.getTriggerTargets() == EffectTargets::friendlyPlayer) {
        return getFriendlyPlayer(minion, phaseController->getFriendlyPlayer(minion));
    } else if (this->targetsModel.getTriggerTargets() == EffectTargets::allPlayers) {
        return getAllPlayers(minion, phaseController->getFriendlyPlayer(minion),
                             phaseController->getEnemyPlayer(minion));
    } else
        throw std::invalid_argument("Invalid player target: " + Utils::getTriggerTargetsString(
                this->targetsModel.getTriggerTargets()));
}

std::vector<Minion *> TargetsBuilder::getSelfMinion(Minion *minion, Player *friendlyPlayer, Player *enemyPlayer) {
    return {minion};
}

std::vector<Minion *> TargetsBuilder::getMinions(Minion *minion, PhaseController *phaseController) {

    if (this->targetsModel.getTriggerTargets() == EffectTargets::enemyMinions) {
        return getEnemyMinions(minion, phaseController->getFriendlyPlayer(minion),
                               phaseController->getEnemyPlayer(minion));
    } else if (this->targetsModel.getTriggerTargets() == EffectTargets::friendlyMinions) {
        return getFriendlyMinions(minion, phaseController->getFriendlyPlayer(minion),
                                  phaseController->getEnemyPlayer(minion));
    } else if (this->targetsModel.getTriggerTargets() == EffectTargets::otherFriendlyMinions) {
        return getOtherFriendlyMinions(minion, phaseController->getFriendlyPlayer(minion));
    } else if (this->targetsModel.getTriggerTargets() == EffectTargets::allMinions) {
        std::vector<Minion *> returnVector;
        std::vector<Minion *> friendlyMinions = getFriendlyMinions(minion, phaseController->getFriendlyPlayer(minion),
                                                                   phaseController->getEnemyPlayer(minion));
        std::vector<Minion *> enemyMinions = getEnemyMinions(minion, phaseController->getFriendlyPlayer(minion),
                                                             phaseController->getEnemyPlayer(minion));
        returnVector.insert(returnVector.end(), friendlyMinions.begin(), friendlyMinions.end());
        returnVector.insert(returnVector.end(), enemyMinions.begin(), enemyMinions.end());
        return returnVector;
    } else if (this->targetsModel.getTriggerTargets() == EffectTargets::self) {
        return getSelfMinion(minion, phaseController->getFriendlyPlayer(minion),
                             phaseController->getEnemyPlayer(minion));
    } else
        throw std::invalid_argument("Invalid minion target: " + Utils::getTriggerTargetsString(
                this->targetsModel.getTriggerTargets()));
}




