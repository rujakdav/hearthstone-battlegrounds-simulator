
#include <stdexcept>
#include "../../headers/components/IArmored.h"

int IArmored::getArmor() const {
    return armor;
}

IArmored::IArmored(int armor) : armor(armor) {
    if (armor < 0) {
        throw std::invalid_argument("Armor cannot be negative");
    }
}

void IArmored::setArmor(int armorToSet) {
    IArmored::armor = armorToSet;
}
