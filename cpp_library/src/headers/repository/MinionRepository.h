#pragma once


#include <vector>
#include <string>

/**
 * @brief The MinionRepository class
 * This class is used to store the minion keys
 */
class MinionRepository {
private:
    const std::vector<std::string> tier1CardKeys = {"1ATron", "1Impris", "1Mis"};
    const std::vector<std::string> tier2CardKeys = {"2Gambler", "2Rock", "2Ripcap"};
    const std::vector<std::string> tier3CardKeys = {"3Crackling", "3Ogre", "3Paladin"};
    const std::vector<std::string> tier4CardKeys = {"4Mushroom", "4Canon", "4Cleric"};
    const std::vector<std::string> tier5CardKeys = {"5Defender", "5Pyrom", "5Robot",};
    const std::vector<std::string> tier6CardKeys = {"6Felstomper", "6Blademaster", "6Golem"};

    const std::vector<std::string> &getTier1CardKeys() const;

    const std::vector<std::string> &getTier2CardKeys() const;

    const std::vector<std::string> &getTier3CardKeys() const;

    const std::vector<std::string> &getTier4CardKeys() const;

    const std::vector<std::string> &getTier5CardKeys() const;

    const std::vector<std::string> &getTier6CardKeys() const;

public:

    /**
     * @brief This method is used to get the minion keys for a tier
     * @param tier
     * @return
     */
    const std::vector<std::string> &getTierCardKeys(int tier) const;


};


