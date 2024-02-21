
#include <iostream>
#include <random>
#include <algorithm>
#include "../../headers/repository/MinionPool.h"
#include "repository/MinionRepository.h"

MinionPool::MinionPool() {
    auto repository = MinionRepository();
    //for each tavern tier, we get minion max for that tier and add minions to the pool
    for (int tavernTier = 1; tavernTier <= 6; ++tavernTier) {
        auto const& minionKeys = repository.getTierCardKeys(tavernTier);
        for (const auto &key: minionKeys) {
            addMinions(key, getMaxMinionKeysForTier(tavernTier), tavernTier);
        }
    }

}


void MinionPool::removeMinions(const std::string &cardKey, int count, int tavernTier) {
    if (pool[tavernTier][cardKey] >= count) {
        pool[tavernTier][cardKey] -= count;
    }
}

// Get the count of minions for a specific cardKey and tavernTier
int MinionPool::getMinionCount(const std::string &cardKey, int tavernTier) const {
    return pool.at(tavernTier).at(cardKey);
}

// Print the current state of the pool
void MinionPool::printPool() const {
    std::cout << "Minion Repository:\n";
    for (const auto &tierEntry: pool) {
        for (const auto &entry: tierEntry.second) {
            std::cout << "Tavern Tier: " << tierEntry.first
                      << ", CardKey: " << entry.first
                      << ", Count: " << entry.second << "\n";
        }
    }
}

void MinionPool::addMinions(const std::string &cardKey, int count, int tavernTier) {
    pool[tavernTier][cardKey] += count;
}

void MinionPool::removeMinion(const std::string &cardKey, int tavernTier) {
    removeMinions(cardKey, 1, tavernTier);
}

std::vector<std::string> MinionPool::getAvailableKeysForTier(int tavernTier) const {
    std::vector<std::string> availableKeys;

    auto tierIter = pool.find(tavernTier);
    if (tierIter != pool.end()) {
        for (const auto &entry: tierIter->second) {
            availableKeys.push_back(entry.first);
        }
    }

    return availableKeys;
}

std::vector<std::string> MinionPool::getRandomMinionKeysForTier(int amount, int tavernTier) const {
    std::vector<std::string> randomKeys;

    for (int currentTier = 1; currentTier <= tavernTier; ++currentTier) {
        auto availableKeys = getAvailableKeysForTier(currentTier);
        randomKeys.insert(randomKeys.end(), availableKeys.begin(), availableKeys.end());
    }


    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(randomKeys.begin(), randomKeys.end(), gen);

    std::vector<std::string> returnVector;
    returnVector.reserve(amount);

    for (int i = 0; i < amount; ++i) {
        returnVector.push_back(randomKeys[i % randomKeys.size()]);
    }

    return returnVector;
}

int MinionPool::getMaxMinionKeysForTier(int tavernTier) const {
switch (tavernTier) {
        case 1:
            return tier1MinionsAmount;
        case 2:
            return tier2MinionsAmount;
        case 3:
            return tier3MinionsAmount;
        case 4:
            return tier4MinionsAmount;
        case 5:
            return tier5MinionsAmount;
        case 6:
            return tier6MinionsAmount;
        default:
            throw std::runtime_error("Invalid tavern tier");
    }

}


