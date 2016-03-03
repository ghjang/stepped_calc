#include "catch.hpp"

#include "../Calculator.h"


TEST_CASE("calculate", "[stepped_cals]")
{
    {
        constant_t result = calculate("1+2*3");
        constant_t expectedResult{ 7 };
        REQUIRE(result == expectedResult);
    }

    {
        constant_t result = calculate("1*2+3");
        constant_t expectedResult{ 5 };
        REQUIRE(result == expectedResult);
    }

    {
        constant_t result = calculate("1*2*3");
        constant_t expectedResult{ 6 };
        REQUIRE(result == expectedResult);
    }

    {
        constant_t result = calculate("1*2*3+4-2");
        constant_t expectedResult{ 8 };
        REQUIRE(result == expectedResult);
    }

    {
        constant_t result = calculate("1*2*3+4-2*10");
        constant_t expectedResult{ -10 };
        REQUIRE(result == expectedResult);
    }

    {
        constant_t result = calculate("1*2*345+4-2*10");
        constant_t expectedResult{ 674 };
        REQUIRE(result == expectedResult);
    }
}

