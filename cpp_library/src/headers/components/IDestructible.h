
#pragma once


#include "mechanics/common/Damage.h"

/**
 * @brief The IDestructible class
 * This class is used to represent an entity that can take damage
 */
class IDestructible {


private:
    int healthPoints;
    int maxHealthPoints;
protected:
    IDestructible(int healthPoints, int maxHealthPoints);

public:


    virtual int getHealthPoints() const;

    void setHealthPoints(int healthPoints);

    virtual int getMaxHealthPoints() const;

    void setMaxHealthPoints(int maxHealthPoints);

    /**
     * @brief Takes damage from the given damage
     * @param damage
     */
    virtual void takeDamage(Damage &damage) = 0;


    /**
     * @brief Takes damage from the given amount
     * @param amount
     */
    void takeDamage(int amount);

    /**
     * @brief Heals the entity with the given amount
     * @param amount
     */
    virtual void heal(int amount);


};
