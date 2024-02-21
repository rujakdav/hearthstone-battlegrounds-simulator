#include <iostream>
#include "../../../headers/mechanics/enchantments/Enchantment.h"

int Enchantment::getHealthIncrease() const {
    return healthIncrease;
}

int Enchantment::getAttackIncrease() const {
    return attackIncrease;
}

Enchantment::Enchantment(const std::string &name, int attackIncrease, int healthIncrease) : IOwned(""), attackIncrease(
        attackIncrease), healthIncrease(
        healthIncrease), name(name) {
    description = std::to_string(attackIncrease) + "/" + std::to_string(healthIncrease) + "\n";
}

const std::string &Enchantment::getName() const {
    return name;
}

void Enchantment::print() const {
    std::cout << "Enchantment: " << name << " - " << description << std::endl;
}

std::unique_ptr<Enchantment> Enchantment::clone() {
    return std::make_unique<Enchantment>(name, attackIncrease, healthIncrease);
}

