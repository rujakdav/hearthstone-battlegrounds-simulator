
#pragma once


#include <string>
#include "enums/card/rarity.h"
#include "enums/card/zone.h"

/**
 * @brief The ICard class
 * This class is used to represent a card
 */
class ICard {

private:
    std::string id;
    std::string name;
    std::string cardKey;
    bool collectible;
    Rarity rarity;
    Zone zone;


protected:
    ICard(const std::string &id, const std::string &name, const std::string &cardKey, bool collectible, Rarity rarity,
          Zone zone);

public:
    virtual ~ICard() = default;

    const std::string &getCardKey() const;

    ICard(const ICard &other);

    ICard &operator=(const ICard &other);

    const std::string &getId() const;

    const std::string &getName() const;

    Zone getZone() const;

    void setZone(Zone zone);

};
