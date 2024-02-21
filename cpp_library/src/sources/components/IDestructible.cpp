#include "../../headers/components/IDestructible.h"

int IDestructible::getHealthPoints() const {
    return healthPoints;
}

void IDestructible::setHealthPoints(int healthPoints) {
    IDestructible::healthPoints = healthPoints;
}

int IDestructible::getMaxHealthPoints() const {
    return maxHealthPoints;
}

void IDestructible::setMaxHealthPoints(int maxHealthPoints) {
    IDestructible::maxHealthPoints = maxHealthPoints;
}

IDestructible::IDestructible(int healthPoints, int maxHealthPoints) : healthPoints(healthPoints),
                                                                      maxHealthPoints(maxHealthPoints) {}

void IDestructible::takeDamage(int amount) {
    setHealthPoints(getHealthPoints() - amount);
}

void IDestructible::heal(int amount) {
    if (getHealthPoints() + amount > getMaxHealthPoints())
        setHealthPoints(getMaxHealthPoints());
    else
        setHealthPoints(getHealthPoints() + amount
        );
}
