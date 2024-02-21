#pragma once

#include <string>
#include "entities/Minion.h"

/**
 * @brief The MinionBuilder class
 * This class is used to build a minion with the given card key
 */
class MinionBuilder {
public:


    /**
     * @brief Returns a minion with the given card key
     * @param filterMinion
     * @return Minion
     */
     static Minion getMinion(const std::string &filterMinion);
};
