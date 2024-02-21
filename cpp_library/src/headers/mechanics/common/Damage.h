#pragma once

/**
 * @brief The Damage class
 * This class is used to store data about damage
 */
class Damage {

private:
    int amount; /**< The amount of damage */
    bool poisonous = false; /**< If the damage is poisonous */
public:
    Damage(int amount, bool isPoisonous);

    explicit Damage(int amount);

    int getAmount() const;

    bool isPoisonous() const;

};



