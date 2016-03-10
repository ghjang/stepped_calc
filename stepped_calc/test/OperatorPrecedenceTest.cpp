#include "catch.hpp"

#include "../OperatorPrecedence.h"


TEST_CASE("binary operator precedence", "[stepped_calc]")
{
    REQUIRE(0 == compare_precedence(BinaryOperator::Addition, BinaryOperator::Addition));
    REQUIRE(0 == compare_precedence(BinaryOperator::Addition, BinaryOperator::Subtraction));

    REQUIRE(0 == compare_precedence(BinaryOperator::Multiplication, BinaryOperator::Multiplication));
    REQUIRE(0 == compare_precedence(BinaryOperator::Multiplication, BinaryOperator::Division));

    REQUIRE(1 == compare_precedence(BinaryOperator::Addition, BinaryOperator::Multiplication));
    REQUIRE(1 == compare_precedence(BinaryOperator::Addition, BinaryOperator::Division));

    REQUIRE(-1 == compare_precedence(BinaryOperator::Multiplication, BinaryOperator::Addition));
    REQUIRE(-1 == compare_precedence(BinaryOperator::Division, BinaryOperator::Addition));
}

