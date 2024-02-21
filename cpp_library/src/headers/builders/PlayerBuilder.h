#pragma once

#include "entities/Player.h"
/**
 * @brief The PlayerBuilder class
 * This class is used to build a player with the given card key
 */
class PlayerBuilder {
public:
    /**
     * @brief Returns a player with the given card key
     * @param cardKey
     * @return Player*
     */
    static Player* getPlayer(const std::string &cardKey);
};


