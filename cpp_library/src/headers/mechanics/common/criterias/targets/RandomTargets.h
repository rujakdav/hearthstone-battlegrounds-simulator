#pragma once

/**
 * @brief The RandomTargets class
 * This class is used to determine if a target is random or not
 */
class RandomTargets {
private:
    bool random = false;
    int howManyRandomTargets = 0;

public:
    bool isRandom() const;

    int getHowManyRandomTargets() const;

protected:
    RandomTargets(bool isRandom, int howManyRandomTargets);

    void setRandom(bool random);

    void setHowManyRandomTargets(int howManyRandomTargets);
};
