#pragma once

#include <iostream>
#include "enums/minion/minionType.h"
#include "enums/card/rarity.h"
#include "enums/card/zone.h"
#include "../components//IDestructible.h"
#include "../components/ICombative.h"
#include "../components/ICard.h"
#include "../messaging/observer//MinionSubject.h"
#include "../mechanics/enchantments/Enchantment.h"
#include "../mechanics/auras/Aura.h"
#include "../mechanics/battlecries/IBattlecry.h"
#include "../mechanics/effects/IEffect.h"
#include "../mechanics/common/Damage.h"
#include "enums/minion/versions.h"
#include <string>
#include <vector>
#include <memory>


class Minion : public ICard, public IDestructible, public ICombative, public MinionSubject {

private:
    MinionType type; /**< The type of the minion */
    int tavernTier;   /**< The tavern tier of the minion */
    std::string ownerId; /**< The id of the owner(player) of the minion */
    int sellCost = 3; /**< The sell cost of the minion */
    Version version = Version::normal; /**< The version of the minion */

    std::vector<PlayerObserver *> observers; /**< The observers of the minion */
    bool divineShield = false; /**< Indicates if the minion has divine shield */
    bool taunt = false; /**< Indicates if the minion has taunt */
    bool poisonous = false; /**< Indicates if the minion is poisonous */

    std::vector<std::unique_ptr<IEffect>> effects; /**< The effects of the minion */
    std::vector<Aura> auras; /**< The auras of the minion */
    std::vector<std::unique_ptr<IBattlecry>> battlecries; /**< The battlecries of the minion */
    std::vector<std::unique_ptr<Enchantment>> enchantments; /**< The enchantments of the minion */
public:

    void setSellCost(int sellCost);

    int getSellCost() const;


    int getTavernTier() const;

    const std::vector<std::unique_ptr<IBattlecry>> &getBattlecries() const;

    std::vector<std::unique_ptr<IBattlecry>> &getBattlecries();

    bool isPoisonous() const;

    void setPoisonous(bool poisonous);

    void addBattlecry(std::unique_ptr<IBattlecry> &battlecry);

    const std::vector<Aura> &getAuras() const;

    bool hasTaunt() const;

    void addAura(Aura auraToAdd);


    const std::vector<std::unique_ptr<Enchantment>> &getEnchantments() const;

    std::vector<std::unique_ptr<Enchantment>> &getEnchantments();


    const std::vector<std::unique_ptr<IEffect>> &getEffects() const;

    std::vector<std::unique_ptr<IEffect>> &getEffects();

    void addTaunt();

    const std::string &getOwnerId() const;

    void addEnchantment(std::unique_ptr<Enchantment> enchantment);


    /**
     * @Brief Gets the total attack increase from enchantments
     * @return
     */
    int getTotalAttackIncrease() const;

    /**
     * @Brief Gets the total health increase from enchantments
     * @return
     */
    int getTotalHealthIncrease() const;

    void registerObserver(PlayerObserver *observer) override;

    void unregisterObserver(PlayerObserver *observer) override;

    void notifyObservers(TriggerType triggerType) override;

    ~Minion() = default;

    Minion(const Minion &other);

    MinionType getType() const;

    void heal(int amount) override;

    void setOwnerId(const std::string &ownerId);

    Minion(const std::string &name, const std::string &cardKey, int attack, int health, MinionType type,
           int tavernTier, bool collectible, Rarity rarity);

    void addEffect(std::unique_ptr<IEffect> effect);

    void print() const;

    void takeDamage(Damage &damage) override;

    void addDivineShield();

    void removeEnchantmentAtIndex(int index);

    int getAttack() const override;

    int getHealthPoints() const override;

    int getMaxHealthPoints() const override;

    Minion &operator=(const Minion &other);

};