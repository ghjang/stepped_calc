#include "catch.hpp"

#include "../Calculator.h"


TEST_CASE("calculate", "[stepped_cals]")
{
    {
        operand_t result = calculate("1+2*3");
        operand_t expectedResult{ 7 };
        REQUIRE(result == expectedResult);
    }

    {
        operand_t result = calculate("1*2+3");
        operand_t expectedResult{ 5 };
        REQUIRE(result == expectedResult);
    }

    {
        operand_t result = calculate("1*2*3");
        operand_t expectedResult{ 6 };
        REQUIRE(result == expectedResult);
    }

    {
        operand_t result = calculate("1*2*3+4-2");
        operand_t expectedResult{ 8 };
        REQUIRE(result == expectedResult);
    }

    {
        operand_t result = calculate("1*2*3+4-2*10");
        operand_t expectedResult{ -10 };
        REQUIRE(result == expectedResult);
    }
}

