
#include "../../headers/entities/Player.h"
#include "../../headers/utils/IDGenerator.h"
#include <algorithm>

void Player::setBoard(std::vector<Minion *> minions) {
    //we make deep copy of minions
    for (auto &minion: minions) {
        auto minionPtr = new Minion(*minion);
        board.push_back(minionPtr);
    }
}

void Player::print() const {

    std::cout << "************" << std::endl;
    std::cout << "Player " << this->name << " " << this->getHealthPoints() << " health, " << getArmor() << " armor"
              << std::endl;
    for (const auto &i: this->board) {
        i->print();
        std::cout << std::endl;
    }
    std::cout << "************" << std::endl;

}


Player::Player(const std::string &name, const std::string &cardKey) : IDestructible(30, 30), IArmored(5), name(name),
                                                                      cardKey(cardKey) {
    board.reserve(maxMinionsOnBoard);
    hand.reserve(maxMinionsInHand);
}


void Player::removeMinionFromBoardByIndex(int minionToRemoveIndex) {
    for (int auraIndex = 0; auraIndex < board[minionToRemoveIndex]->getAuras().size(); auraIndex++) {
        for (auto &boardMinion: board) {
            if (boardMinion->getId() != board[minionToRemoveIndex]->getId()) {
                for (int effectIndex = 0; effectIndex < boardMinion->getEffects().size(); effectIndex++) {
                    if (boardMinion->getEffects()[effectIndex]->getOwnerId() ==
                        board[minionToRemoveIndex]->getAuras()[auraIndex].getOwnerId()) {
                        boardMinion->getEffects().erase(
                                boardMinion->getEffects().begin() + effectIndex);
                        unsubscribeMinionEffect(boardMinion,
                                                board[minionToRemoveIndex]->getAuras()[auraIndex].getEffect());


                    }
                }
                for (int enchantmentIndex = 0;
                     enchantmentIndex < boardMinion->getEnchantments().size(); enchantmentIndex++) {
                    if (boardMinion->getEnchantments()[enchantmentIndex]->getOwnerId() ==
                        board[minionToRemoveIndex]->getAuras()[auraIndex].getOwnerId()) {

                        boardMinion->removeEnchantmentAtIndex(enchantmentIndex);
                    }
                }

            }
        }
    }
    board[minionToRemoveIndex]->setZone(Zone::graveyard);
    /*for (auto &i: observers) {
        i->unsubscribeMinion(&board[minionToRemoveIndex]);
    }*/
    //graveyard.push_back(board[minionToRemoveIndex]);
    auto it = board.begin() + minionToRemoveIndex;

    board.erase(it);

}


void Player::takeDamage(Damage &damage) {
    if (getArmor() == 0)
        IDestructible::takeDamage(damage.getAmount());
    else {
        if (damage.getAmount() == getArmor()) {
            setArmor(0);
        } else if (damage.getAmount() < getArmor()) {
            setArmor(getArmor() - damage.getAmount());
        } else {
            int oldArmor = getArmor();
            setArmor(0);
            IDestructible::takeDamage(damage.getAmount() - oldArmor);
        }
    }

}

void Player::update(Minion *minion, TriggerType triggerType) {
    notifyObservers(minion, triggerType);
}

void Player::registerObserver(GameObserver *observer) {
    observers.push_back(observer);

}

void Player::unregisterObserver(GameObserver *observer) {
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

void Player::notifyObservers(Minion *minion, TriggerType triggerType) {
    for (auto &observer: observers) {
        observer->update(minion, triggerType, this);
    }
}

const std::string &Player::getName() const {
    return name;
}


const std::string &Player::getId() const {
    return id;
}

void Player::auraUpdate(const Minion *minionWithAura) {
    for (const auto &aura: minionWithAura->getAuras()) {
        for (auto &minionOnBoard: board) {
            if (minionOnBoard->getId() != minionWithAura->getId()) {
                if (aura.getEnchantment() != nullptr) {
                    minionOnBoard->addEnchantment(aura.getEnchantment()->clone());
                }
                if (aura.getEffect() != nullptr) {
                    minionOnBoard->addEffect(aura.getEffect()->clone());
                    subscribeMinionEffect(minionOnBoard, aura.getEffect());
                }
            }

        }

    }

}

int Player::getIndexOfMinionById(std::string minionId) {
    for (int i = 0; i < board.size(); i++) {
        if (board[i]->getId() == minionId) {
            return i;
        }
    }
    return -1;

}

void Player::addMinionToBoard(Minion minion) {
    if (board.size() >= maxMinionsOnBoard)
        return;

    minion.setOwnerId(this->id);
    minion.setZone(Zone::play);

    //we allocate new minion object pointer
    auto minionPtr = new Minion(minion);

    board.push_back(minionPtr);

    getMinionFromBoardById(minion.getId())->registerObserver(this);
    subscribeMinion(getMinionFromBoardById(minion.getId()));
    //first we update other minions with aura of minionToAdd
    if (!minion.getAuras().empty())
        auraUpdate(getMinionFromBoardById(minion.getId()));
    //then we update minionToAdd with auras of other minions
    for (auto const &boardMinion: board) {
        if (boardMinion->getId() != minion.getId())
            for (const auto &aura: boardMinion->getAuras()) {
                for (int minionsOnBoardIndex = 0; minionsOnBoardIndex < board.size(); minionsOnBoardIndex++) {
                    if (aura.getEnchantment() != nullptr) {
                        getMinionFromBoardById(minion.getId())->addEnchantment(aura.getEnchantment()->clone());
                    }
                    if (aura.getEffect() != nullptr) {
                        getMinionFromBoardById(minion.getId())->addEffect(aura.getEffect()->clone());
                        subscribeMinionEffect(getMinionFromBoardById(minion.getId()), aura.getEffect());
                    }
                }
            }
    }
}


std::vector<Minion *> &Player::getBoard() {
    return board;
}


void Player::addGold(int amount) {
    if (amount < 0)
        throw std::invalid_argument("Amount of currentGold to add must be positive");
    if (this->currentGold + amount > 100)
        this->currentGold = 100;
    else
        this->currentGold += amount;

}

void Player::spendGold(int amount) {
    if (amount < 0)
        throw std::invalid_argument("Amount of currentGold to spend must be positive");
    this->currentGold -= amount;
}

bool Player::canAfford(int amount) {
    if (amount < 0)
        throw std::invalid_argument("Amount of currentGold to spend must be positive");
    return this->currentGold >= amount;
}

int Player::getTavernTier() const {
    return tavernTier;
}

const int Player::getMaxMinionsOnBoard() const {
    return maxMinionsOnBoard;
}

void Player::levelUp() {
    if (tavernTier < 6) {
        tavernTier++;
        levelUpCost = 5;
    }

}

int Player::calculateDamageToDeal() {
    int damageToDeal = 0;
    for (auto &minion: board) {
        damageToDeal += minion->getTavernTier();
    }
    return damageToDeal;
}

Player::Player(const Player &other) : IDestructible(other.getHealthPoints(),
                                                    other.getMaxHealthPoints()), IArmored(other.getArmor()),
                                      cardKey(other.cardKey),
                                      name(other.name), id(other.id), tavernTier(other.tavernTier),
                                      currentGold(other.currentGold) {
    board.clear();
    board.reserve(maxMinionsOnBoard);
    std::copy(other.board.begin(), other.board.end(), std::back_inserter(board));

    // Deep copy of graveyard
    graveyard.clear();
    std::copy(other.graveyard.begin(), other.graveyard.end(), std::back_inserter(graveyard));

    // observers are not copied
    observers = {};

}

int Player::getMaxMinionsForTier() {
    if (tavernTier == 1)
        return 3;
    else if (tavernTier == 2)
        return 4;
    else if (tavernTier == 3)
        return 5;
    else if (tavernTier == 4)
        return 6;
    else if (tavernTier == 5)
        return 6;
    else if (tavernTier == 6)
        return 6;
    else
        throw std::invalid_argument("Invalid tavern tier");
}

int Player::getCurrentGold() const {
    return currentGold;
}

int Player::getMaxGold() const {
    return startOfTurnGold;
}

void Player::increaseStartOfTurnGold() {
    if (startOfTurnGold < 10)
        startOfTurnGold++;
}

void Player::setCurrentGold(int currentGold) {
    Player::currentGold = currentGold;
}

int Player::getStartOfTurnGold() const {
    return startOfTurnGold;
}

const std::vector<Minion> &Player::getHand() const {
    return hand;
}

std::vector<Minion> &Player::getHand() {
    return hand;
}

void Player::addMinionToHand(Minion minion) {
    if (hand.size() >= maxMinionsInHand)
        return;
    minion.setOwnerId(this->id);
    minion.setZone(Zone::hand);
    hand.push_back(minion);
}

int Player::getLevelUpCost() const {
    return levelUpCost;
}

int Player::getRefreshCost() const {
    return refreshCost;
}

void Player::decreaseLevelUpCost() {
    if (levelUpCost > 0)
        levelUpCost--;

}

Minion *Player::getMinionFromGraveyardById(std::string id) {
    for (auto &minion: graveyard) {
        if (minion->getId() == id)
            return minion;
    }
    throw std::invalid_argument("Minion with id " + id + " not found");
}


void Player::removeMinionFromHand(const Minion &minion) {

    auto removeIterator = std::remove_if(hand.begin(), hand.end(),
                                         [&minion](const Minion &handMinion) {
                                             return handMinion.getId() == minion.getId();
                                         });

    // Erase the removed elements from the vector
    hand.erase(removeIterator, hand.end());

}

int Player::getBuyCost() const {
    return buyCost;
}


Minion *Player::getMinionFromBoardById(std::string id) {
    for (auto &minion: board) {
        if (minion->getId() == id)
            return minion;
    }
    throw std::invalid_argument("Minion with id " + id + " not found");
}


void Player::removeMinionFromBoardById(std::string minionId) {
    removeMinionFromBoardByIndex(getIndexOfMinionById(minionId));

}

const int Player::getMaxMinionsInHand() const {
    return maxMinionsInHand;
}

void Player::subscribeMinion(Minion *minion) {
    for (auto &i: observers) {
        i->subscribeMinion(minion);
    }
}

void Player::unsubscribeMinion(Minion *minion) {
    for (auto &i: observers) {
        i->unsubscribeMinion(minion);
    }
}

void Player::subscribeMinionEffect(Minion *minion, const std::unique_ptr<IEffect> &auraEffect) {
    for (auto &i: observers) {
        i->subscribeMinionEffect(minion, auraEffect);
    }
}

void Player::unsubscribeMinionEffect(Minion *minion, const std::unique_ptr<IEffect> &auraEffect) {
    for (auto &i: observers) {
        i->unsubscribeMinionEffect(minion, auraEffect);
    }
}

Player::~Player() {
    for (auto &minion: board) {
        delete minion;
    }
    for (auto &minion: graveyard) {
        delete minion;
    }

}

