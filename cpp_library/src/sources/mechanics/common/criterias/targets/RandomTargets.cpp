#include "mechanics/common/criterias/targets/RandomTargets.h"

RandomTargets::RandomTargets(bool isRandom, int howManyRandomTargets) : random(isRandom),
                                                                        howManyRandomTargets(howManyRandomTargets) {}

bool RandomTargets::isRandom() const {
    return random;
}

int RandomTargets::getHowManyRandomTargets() const {
    return howManyRandomTargets;
}

void RandomTargets::setRandom(bool random) {
    RandomTargets::random = random;
}

void RandomTargets::setHowManyRandomTargets(int howManyRandomTargets) {
    RandomTargets::howManyRandomTargets = howManyRandomTargets;
}
