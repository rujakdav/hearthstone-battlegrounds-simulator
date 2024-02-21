#include <utility>
#include "../../../headers/mechanics/auras/Aura.h"
#include "../../../headers/mechanics/effects/IEffect.h"


Aura::Aura(std::string name, Enchantment ench) : enchantment(ench.clone()),
                                                 effect(nullptr),
                                                 name(std::move(name)) {
    enchantment->setOwnerId(ownerID);
}

Aura::Aura(std::string name, std::unique_ptr<IEffect> eff) : enchantment(nullptr),
                                                             effect(eff->clone()),
                                                             name(std::move(name)) {
    effect->setOwnerId(ownerID);
}

const std::string &Aura::getName() const {
    return name;
}

const std::unique_ptr<Enchantment> &Aura::getEnchantment() const {
    return enchantment;
}

const std::unique_ptr<IEffect> &Aura::getEffect() const {
    return effect;
}

Aura::Aura(const Aura &aura) {
    this->name = aura.name;
    this->ownerID = aura.ownerID;
    if (aura.enchantment)
        this->enchantment = aura.enchantment->clone();
    if (aura.effect)
        this->effect = aura.effect->clone();

}

void Aura::setOwnerId(const std::string &ownerId) {
    ownerID = ownerId;
    if (enchantment)
        enchantment->setOwnerId(ownerId);
    if (effect)
        effect->setOwnerId(ownerId);
}

const std::string &Aura::getOwnerId() const {
    return ownerID;
}






