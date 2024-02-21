#pragma once

#include <string>

/**
 * @brief The IOwned class
 * This class is used to store data about the owner of a card
 */
class IOwned {
private:
    std::string ownerId;
public:
    const std::string &getOwnerId() const;

    void setOwnerId(const std::string &ownerId);

    explicit IOwned(const std::string &ownerId);

};