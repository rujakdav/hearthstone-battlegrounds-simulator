#include "../../../headers/mechanics/common/IOwned.h"

IOwned::IOwned(const std::string &ownerId) : ownerId(ownerId) {}

const std::string &IOwned::getOwnerId() const {
    return ownerId;
}

void IOwned::setOwnerId(const std::string &ownerId) {
    IOwned::ownerId = ownerId;
}
