
#pragma once

#include <random>
#include <algorithm>
#include "enums/mechanics/common/triggerType.h"
#include "mechanics/common/tree/TreeNode.h"
#include "enums/mechanics/effects/EffectTargets.h"

/**
 * @brief The Utils class
 * This class is used to provide utility functions
 */
class Utils {
private:
    void printTreeHelper(const TreeNode *node, int depth) const;
public:
    /**
     * @brief This method is used to get a random number between lower and higher bounds
     * @param lower The lower bound
     * @param higher The higher bound
     * @return The random number
     */
    static int getRandomNumber(int lower, int higher);

    /**
     * @brief This method is used to get a random number from an array
     * @param arr The array
     * @return The random number
     */
    static int getRandomNumberFromArray(const std::vector<int>& arr);

    /**
     * @brief This method is used to get a random element from a vector
     * @tparam T The type of the vector
     * @param inputVector The vector
     * @return The random element
     */
    template<typename T>
    static std::vector<T> GetNElements(const std::vector<T> &inputVector, int n){
        // Check if n is greater than the size of inputVector
        if (n >= inputVector.size()) {
            return inputVector;
        }

        // Shuffle the inputVector
        std::vector<T> shuffledVector = inputVector;
        std::random_device rd;
        std::mt19937 generator(rd());
        std::shuffle(shuffledVector.begin(), shuffledVector.end(), generator);

        // Create a new vector with n elements
        std::vector<T> resultVector(shuffledVector.begin(), shuffledVector.begin() + n);
        return resultVector;
    }

    static std::string getTriggerTypeString(TriggerType type);

    static std::string getMinionTypeString(MinionType minionType);

    static std::string getTriggerTargetsString(EffectTargets target);

    void printTree(TreeNode *node) const;



};
