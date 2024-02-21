#include <stdexcept>
#include "repository/MinionRepository.h"

const std::vector<std::string> &MinionRepository::getTier1CardKeys() const {
    return tier1CardKeys;
}

const std::vector<std::string> &MinionRepository::getTier2CardKeys() const {
    return tier2CardKeys;
}

const std::vector<std::string> &MinionRepository::getTier3CardKeys() const {
    return tier3CardKeys;
}

const std::vector<std::string> &MinionRepository::getTier4CardKeys() const {
    return tier4CardKeys;
}

const std::vector<std::string> &MinionRepository::getTier5CardKeys() const {
    return tier5CardKeys;
}

const std::vector<std::string> &MinionRepository::getTier6CardKeys() const {
    return tier6CardKeys;
}

const std::vector<std::string> &MinionRepository::getTierCardKeys(int tier) const {
    switch (tier) {
        case 1:
            return tier1CardKeys;
        case 2:
            return tier2CardKeys;
        case 3:
            return tier3CardKeys;
        case 4:
            return tier4CardKeys;
        case 5:
            return tier5CardKeys;
        case 6:
            return tier6CardKeys;
        default:
            throw std::runtime_error("Invalid tier");
    }
}
