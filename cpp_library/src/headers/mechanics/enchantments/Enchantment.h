#pragma once


#include <string>
#include <memory>
#include "../common/IOwned.h"

class Enchantment : public IOwned {
private:
    int attackIncrease;
    int healthIncrease;
    std::string name;
    std::string description;
public:
    const std::string &getName() const;

    int getHealthIncrease() const;

    int getAttackIncrease() const;

    Enchantment(const std::string &name, int attackIncrease, int healthIncrease);

    void print() const;

    std::unique_ptr<Enchantment> clone();
};



