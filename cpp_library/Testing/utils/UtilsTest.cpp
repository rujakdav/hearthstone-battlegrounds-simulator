#include <catch2/catch_all.hpp>
#include "utils/Utils.h"


TEST_CASE("getRandomNumber, [Utils]") {
// Check if the random number is within the specified range
    int result = Utils::getRandomNumber(0, 1);
    REQUIRE((result == 0 || result == 1));
}

TEST_CASE("getRandomNumberFromArray, [Utils]") {
// Check if the random number from array is within the range of array indices
    std::vector<int> testArray = {10, 20, 30, 40, 50};
    int result = Utils::getRandomNumberFromArray(testArray);
    REQUIRE((result == 10 || result == 20 || result == 30 || result == 40 || result == 50));
}


