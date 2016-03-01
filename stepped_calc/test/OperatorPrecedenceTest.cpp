#include "catch.hpp"

#include "../OperatorPrecedence.h"


TEST_CASE("operator precedence", "[stepped_calc]")
{
    REQUIRE(0 == compare_precedence(Operator::Addition, Operator::Addition));
    REQUIRE(0 == compare_precedence(Operator::Addition, Operator::Subtraction));

    REQUIRE(0 == compare_precedence(Operator::Multiplication, Operator::Multiplication));
    REQUIRE(0 == compare_precedence(Operator::Multiplication, Operator::Division));

    REQUIRE(1 == compare_precedence(Operator::Addition, Operator::Multiplication));
    REQUIRE(1 == compare_precedence(Operator::Addition, Operator::Division));

    REQUIRE(-1 == compare_precedence(Operator::Multiplication, Operator::Addition));
    REQUIRE(-1 == compare_precedence(Operator::Division, Operator::Addition));
}

