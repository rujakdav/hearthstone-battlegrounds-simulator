
#pragma once

/**
 * @brief The ICombative class
 * This class is used to represent the combative behavior of entities
 */
class ICombative {
private:
    int attack;
    int maxRemainingAttacks;
    int remainingAttacks;
    bool hasAttacked = false;


protected:
    ICombative(int attack, int remainingAttacks);


    virtual ~ICombative() = default;


public:
    virtual int getAttack() const;

    bool isHasAttacked() const;

    int getMaxRemainingAttacks() const;

    void setRemainingAttacks(int remainingAttacks);

    /**
     * @brief Changes the hasAttacked to opposite
     */
    void changeHasAttacked();

    int getRemainingAttacks() const;

    void reduceRemainingAttacks();


};
