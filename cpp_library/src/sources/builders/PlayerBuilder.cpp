#include "builders/PlayerBuilder.h"

Player *PlayerBuilder::getPlayer(const std::string &cardKey) {
    if (cardKey == "Rag") {
        auto player = new Player("Ragnaros", cardKey);
        return player;
    } else if (cardKey == "LK") {
        auto player = new Player("Lich King", cardKey);
        return player;
    } else if (cardKey == "Jaina") {
        auto player = new Player("Jaina", cardKey);
        return player;
    } else if (cardKey == "Anduin") {
        auto player = new Player("Anduin", cardKey);
        return player;
    } else if (cardKey == "Garrosh") {
        auto player = new Player("Garrosh", cardKey);
        return player;
    } else if (cardKey == "Thrall") {
        auto player = new Player("Thrall", cardKey);
        return player;
    } else if (cardKey == "Uther") {
        auto player = new Player("Uther", cardKey);
        return player;
    } else if (cardKey == "Valeera") {
        auto player = new Player("Valeera", cardKey);
        return player;
    }


    throw std::runtime_error("Invalid player key");
}
