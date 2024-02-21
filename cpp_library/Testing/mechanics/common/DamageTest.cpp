#include "catch2/catch_test_macros.hpp"
#include "mechanics/common/Damage.h"

TEST_CASE("Damage initialization with positive amount and non-poisonous, [Damage]") {
REQUIRE_NOTHROW(Damage(10, false));
Damage damage(10, false);
REQUIRE(damage.getAmount() == 10);
REQUIRE_FALSE(damage.isPoisonous());
}

TEST_CASE("Damage initialization with positive amount and poisonous, [Damage]") {
REQUIRE_NOTHROW(Damage(15, true));
Damage damage(15, true);
REQUIRE(damage.getAmount() == 15);
REQUIRE(damage.isPoisonous());
}

TEST_CASE("Damage initialization with zero amount, [Damage]") {
REQUIRE_NOTHROW(Damage(0, false));
Damage damage(0, false);
REQUIRE(damage.getAmount() == 0);
REQUIRE_FALSE(damage.isPoisonous());
}

TEST_CASE("Damage initialization with negative amount throws exception, [Damage]") {
REQUIRE_THROWS_AS(Damage(-5, false), std::runtime_error);
}

TEST_CASE("Get amount from Damage object, [Damage]") {
Damage damage(25, false);
REQUIRE(damage.getAmount() == 25);
}

TEST_CASE("Check if damage is poisonous, [Damage]") {
Damage nonPoisonousDamage(10, false);
Damage poisonousDamage(20, true);

REQUIRE_FALSE(nonPoisonousDamage.isPoisonous());
REQUIRE(poisonousDamage.isPoisonous());
}
