#include "../../headers/components/ICard.h"

const std::string &ICard::getId() const {
    return id;
}

const std::string &ICard::getName() const {
    return name;
}

Zone ICard::getZone() const {
    return zone;
}

void ICard::setZone(Zone zone) {
    ICard::zone = zone;
}

ICard::ICard(const std::string &id, const std::string &name, const std::string &cardKey, bool collectible,
             Rarity rarity,
             Zone zone) : id(id),
                          name(name), cardKey(cardKey),
                          collectible(
                                  collectible),
                          rarity(rarity),
                          zone(zone) {}

const std::string &ICard::getCardKey() const {
    return cardKey;
}

ICard::ICard(const ICard &other) : id(other.id), name(other.name), cardKey(other.cardKey),
                                   collectible(other.collectible), rarity(other.rarity), zone(other.zone) {

}

ICard &ICard::operator=(const ICard &other) {
    if (this != &other) {
        id = other.id;
        name = other.name;
        cardKey = other.cardKey;
        collectible = other.collectible;
        rarity = other.rarity;
        zone = other.zone;
        // Add any additional assignment logic if needed
    }
    return *this;
}
