#pragma once

#include <memory>
#include "../enchantments/Enchantment.h"

class IEffect;

/**
 * @brief The Aura class
 * This class is used to represent an aura
 */
class Aura {
private:
    std::unique_ptr<Enchantment> enchantment; /**< The enchantment */
    std::unique_ptr<IEffect> effect; /**< The effect */
    std::string name; /**< The name of the aura */
    std::string description; /**< The description of the aura */
    std::string ownerID; /**< The owner id of the aura */
public:
    const std::string &getOwnerId() const;

public:
    void setOwnerId(const std::string &ownerId);

public:
    const std::unique_ptr<Enchantment> &getEnchantment() const;

    const std::unique_ptr<IEffect> &getEffect() const;

    const std::string &getName() const;


    Aura(std::string name, Enchantment ench);

    Aura(std::string name,std::unique_ptr<IEffect> eff);

    Aura(const Aura& aura);
};