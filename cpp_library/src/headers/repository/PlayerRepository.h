#pragma once


#include <string>
#include <vector>

/**
 * @brief The PlayerRepository class
 * This class is used to store the player card keys
 */
class PlayerRepository {

private:
    std::vector<std::string> playerCardKeys = {"Rag", "LK", "Jaina", "Anduin", "Garrosh", "Thrall", "Uther", "Valeera"};

public:
    /**
     * @brief This method is used to get the player card keys
     * @return
     */
    const std::vector<std::string> &getPlayerCardKeys() const;

};



