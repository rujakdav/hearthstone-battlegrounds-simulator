#include <stdexcept>
#include "../../../headers/mechanics/common/Damage.h"

Damage::Damage(int amount, bool isPoisonous) : amount(amount), poisonous(isPoisonous) {
    if (amount < 0)
        throw std::runtime_error("Amount must be positive");
}

Damage::Damage(int amount) : amount(amount) {}

int Damage::getAmount() const {
    return amount;
}

bool Damage::isPoisonous() const {
    return poisonous;
}
