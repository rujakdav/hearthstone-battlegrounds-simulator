
#include <iostream>
#include "../../headers/components/ICombative.h"

int ICombative::getAttack() const {
    return attack;
}

int ICombative::getRemainingAttacks() const {
    return remainingAttacks;
}

void ICombative::reduceRemainingAttacks() {
    remainingAttacks--;
}


void ICombative::changeHasAttacked() {
    hasAttacked = !hasAttacked;

}

bool ICombative::isHasAttacked() const {
    return hasAttacked;
}


void ICombative::setRemainingAttacks(int remainingAttacks) {
    ICombative::remainingAttacks = remainingAttacks;
}

ICombative::ICombative(int attack, int remainingAttacks) : attack(attack), remainingAttacks(remainingAttacks),
                                                           maxRemainingAttacks(remainingAttacks) {}

int ICombative::getMaxRemainingAttacks() const {
    return maxRemainingAttacks;
}

