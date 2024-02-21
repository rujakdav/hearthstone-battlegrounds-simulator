#include "../../headers/entities/Minion.h"
#include "../../headers/mechanics/effects/IEffect.h"
#include "../../headers/utils/IDGenerator.h"
#include "../../headers/utils/Utils.h"
#include <algorithm>

void Minion::print() const {
    std::cout << Utils::getMinionTypeString(this->getType()) <<
              " - " << this->getName() <<
              " - " << this->getAttack() << " / " << this->getHealthPoints() <<
              " - tavern tier:" << this->getTavernTier() << std::endl;
}


void Minion::setOwnerId(const std::string &ownerId) {
    Minion::ownerId = ownerId;
}


MinionType Minion::getType() const {
    return type;
}


void Minion::unregisterObserver(PlayerObserver *observer) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == observer) {
            observers.erase(it);
            return;
        }
    }


}

void Minion::notifyObservers(TriggerType triggerType) {
    if (getZone() != Zone::play) {
        return;
    }
    for (auto &observer: observers) {
        observer->update(this,
                         triggerType);
    }
}

void Minion::addDivineShield() {
    divineShield = true;
}

const std::string &Minion::getOwnerId() const {
    return ownerId;
}


int Minion::getTotalAttackIncrease() const {
    int totalAttackIncrease = 0;
    for (const auto &enchantment: enchantments) {
        totalAttackIncrease += enchantment->getAttackIncrease();
    }

    return totalAttackIncrease;
}

int Minion::getTotalHealthIncrease() const {
    int totalHealthIncrease = 0;
    for (const auto &enchantment: enchantments) {
        totalHealthIncrease += enchantment->getHealthIncrease();
    }
    return totalHealthIncrease;
}

int Minion::getAttack() const {
    return ICombative::getAttack() + getTotalAttackIncrease();
}

int Minion::getHealthPoints() const {
    return IDestructible::getHealthPoints() /*+ getTotalHealthIncrease()*/;
}

void Minion::addEnchantment(std::unique_ptr<Enchantment> enchantment) {
    if (enchantment->getAttackIncrease() > 0)
        notifyObservers(TriggerType::afterAttackIncrease);
    enchantments.push_back(std::move(enchantment));
    setMaxHealthPoints(getMaxHealthPoints() + enchantments.back()->getHealthIncrease());
    setHealthPoints(getHealthPoints() + enchantments.back()->getHealthIncrease());
}

bool Minion::hasTaunt() const {
    return taunt;
}


int Minion::getMaxHealthPoints() const {
    return IDestructible::getMaxHealthPoints() /*+ getTotalHealthIncrease()*/;
}

Minion::Minion(const std::string &name, const std::string &cardKey, int attack, int health, MinionType type,
               int tavernTier,
               bool collectible, Rarity rarity) : ICard(IDGenerator::getInstance().generateID(), name, cardKey,
                                                        collectible, rarity, Zone::invalid),
                                                  IDestructible(health, health), ICombative(attack, 1), type(type),
                                                  tavernTier(tavernTier) {
}

void Minion::addEffect(std::unique_ptr<IEffect> effect) {
    effects.push_back(effect->clone());
}

Minion &Minion::operator=(const Minion &other) {
    if (this == &other) {
        return *this;  // Self-assignment, no need to copy
    }

    this->IDestructible::operator=(other);
    this->ICombative::operator=(other);
    this->ICard::operator=(other);
    this->IDestructible::operator=(other);


    // Copy the primitive member variables
    this->type = other.type;
    this->tavernTier = other.tavernTier;
    this->ownerId = other.ownerId;
    this->divineShield = other.divineShield;
    this->taunt = other.taunt;


    this->auras.clear();
    for (auto &aura: other.auras) {
        this->auras.push_back(aura);
    }

    this->enchantments.clear();
    for (const auto &enchantment: other.enchantments) {
        auto newEnchantment = std::make_unique<Enchantment>(
                enchantment->getName(), enchantment->getAttackIncrease(), enchantment->getHealthIncrease());
        enchantments.push_back(std::move(newEnchantment));
    }

    this->effects.clear();
    for (const auto &effect: other.effects) {
        this->effects.push_back(effect->clone());
    }

    this->observers.clear();
    for (const auto &observer: other.observers) {
        this->observers.push_back(observer);
    }

    battlecries.clear();
    for (const auto &battlecry: other.battlecries) {
        this->battlecries.push_back(battlecry->clone());
    }

    return *this;
}

void Minion::registerObserver(PlayerObserver *observer) {

    observers.push_back(observer);

}

Minion::Minion(const Minion &other)

        : ICard(other), IDestructible(other), ICombative(other), MinionSubject(other),
          type(other.type), tavernTier(other.tavernTier), ownerId(other.ownerId),
          observers(other.observers), divineShield(other.divineShield),
          taunt(other.taunt) {
    for (const auto &enchantment: other.enchantments) {
        enchantments.push_back(enchantment->clone());
    }

    for (auto &aura: other.auras) {
        auras.push_back(aura);
    }

    for (const auto &effect: other.effects) {
        this->effects.push_back(effect->clone());
    }

    for (const auto &battlecry: other.battlecries) {
        this->battlecries.push_back(battlecry->clone());
    }

}

const std::vector<std::unique_ptr<IEffect>> &Minion::getEffects() const {
    return effects;
}

std::vector<std::unique_ptr<IEffect>> &Minion::getEffects() {
    return effects;
}

const std::vector<Aura> &Minion::getAuras() const {
    return auras;
}


void Minion::addTaunt() {
    taunt = true;

}

const std::vector<std::unique_ptr<Enchantment>> &Minion::getEnchantments() const {
    return enchantments;
}

std::vector<std::unique_ptr<Enchantment>> &Minion::getEnchantments() {
    return enchantments;
}

int Minion::getTavernTier() const {
    return tavernTier;
}

const std::vector<std::unique_ptr<IBattlecry>> &Minion::getBattlecries() const {
    return battlecries;
}

std::vector<std::unique_ptr<IBattlecry>> &Minion::getBattlecries() {
    return battlecries;
}

void Minion::addBattlecry(std::unique_ptr<IBattlecry> &battlecry) {
    battlecries.push_back(std::move(battlecry));

}

void Minion::takeDamage(Damage &damage) {

    if (getZone() != Zone::play)
        return;

    if (divineShield) {
        divineShield = false;
        notifyObservers(TriggerType::afterDivineShieldLoss);
        return;
    }
    if (damage.isPoisonous()) {
        setHealthPoints(0);
        notifyObservers(TriggerType::afterTakeDamage);
        return;
    }
    IDestructible::takeDamage(damage.getAmount());
    notifyObservers(TriggerType::afterTakeDamage);


}

void Minion::heal(int amount) {
    notifyObservers(TriggerType::onHeal);
    IDestructible::heal(amount);
}

void Minion::addAura(Aura auraToAdd) {
    auraToAdd.setOwnerId(getId());

    auras.push_back(auraToAdd);
}

int Minion::getSellCost() const {
    return sellCost;
}

void Minion::setSellCost(int sellCost) {
    Minion::sellCost = sellCost;
}

bool Minion::isPoisonous() const {
    return poisonous;
}

void Minion::setPoisonous(bool poisonous) {
    Minion::poisonous = poisonous;
}

void Minion::removeEnchantmentAtIndex(int index) {

    if (getHealthPoints() - enchantments[index]->getHealthIncrease() == 0)
        setHealthPoints(1);
    else
        setHealthPoints(getHealthPoints() - enchantments[index]->getHealthIncrease());
    setMaxHealthPoints(getMaxHealthPoints() - enchantments[index]->getHealthIncrease());
    enchantments.erase(enchantments.begin() + index);
}


