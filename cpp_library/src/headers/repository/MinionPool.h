#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>

/**
 * @brief The MinionPool class
 * This class is used to store the minions that are available for purchase
 */
class MinionPool {
private:
    const static int tier1MinionsAmount = 16*3;
    const static int tier2MinionsAmount = 15*3;
    const static int tier3MinionsAmount = 13*3;
    const static int tier4MinionsAmount = 11*3;
    const static int tier5MinionsAmount = 9*3;
    const static int tier6MinionsAmount = 7*3;

    std::unordered_map<int, std::unordered_map<std::string, int>> pool; /**< The pool of minions */

    void removeMinions(const std::string &cardKey, int count, int tavernTier); /**< This method is used to remove minions from the pool */


    int getMaxMinionKeysForTier(int tavernTier) const; /**< This method is used to get the maximum amount of minion keys for a tier */


public:

    /**
     * @brief This method is used to get a random minion key for a tier
     * @param tavernTier
     * @return
     */
    std::vector<std::string> getRandomMinionKeysForTier(int amount, int tavernTier) const;

    MinionPool();


    /**
     * @brief This method is used to add minions to the pool
     * @param cardKey
     * @param count
     * @param tavernTier
     */
    void addMinions(const std::string &cardKey, int count, int tavernTier);


    /**
     * @brief This method is used to get the amount of minions in the pool
     * @param cardKey
     * @param tavernTier
     * @return
     */
    int getMinionCount(const std::string &cardKey, int tavernTier) const;


    /**
     * @brief This method is used to get the available keys for a tier
     * @param tavernTier
     * @return
     */
    std::vector<std::string> getAvailableKeysForTier(int tavernTier) const;

    void printPool() const;

    /**
     * @brief This method is used to remove a minion from the pool
     * @param cardKey
     * @param tavernTier
     */
    void removeMinion(const std::string &cardKey, int tavernTier);
};
