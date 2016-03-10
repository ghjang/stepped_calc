#include "catch.hpp"

#include "../OperatorPrecedence.h"


TEST_CASE("unary operator precedence", "[stepped_calc]")
{
    auto const plus = token_t{ UnaryOperator::Plus };
    auto const minus = token_t{ UnaryOperator::Minus };

    REQUIRE(0 == boost::apply_visitor(CompareOperatorPrecedence(), plus, plus));
    REQUIRE(0 == boost::apply_visitor(CompareOperatorPrecedence(), minus, minus));
    REQUIRE(0 == boost::apply_visitor(CompareOperatorPrecedence(), plus, minus));
    REQUIRE(0 == boost::apply_visitor(CompareOperatorPrecedence(), minus, plus));
}

TEST_CASE("binary operator precedence", "[stepped_calc]")
{
    auto const addition = token_t{ BinaryOperator::Addition };
    auto const subtraction = token_t{ BinaryOperator::Subtraction };
    auto const multiplication = token_t{ BinaryOperator::Multiplication };
    auto const division = token_t{ BinaryOperator::Division };

    REQUIRE(0 == boost::apply_visitor(CompareOperatorPrecedence(), addition, addition));
    REQUIRE(0 == boost::apply_visitor(CompareOperatorPrecedence(), addition, subtraction));

    REQUIRE(0 == boost::apply_visitor(CompareOperatorPrecedence(), multiplication, multiplication));
    REQUIRE(0 == boost::apply_visitor(CompareOperatorPrecedence(), multiplication, division));

    REQUIRE(1 == boost::apply_visitor(CompareOperatorPrecedence(), addition, multiplication));
    REQUIRE(1 == boost::apply_visitor(CompareOperatorPrecedence(), addition, division));

    REQUIRE(-1 == boost::apply_visitor(CompareOperatorPrecedence(), multiplication, addition));
    REQUIRE(-1 == boost::apply_visitor(CompareOperatorPrecedence(), division, addition));
}

TEST_CASE("operator precedence", "[stepped_calc]")
{
    auto const plus = token_t{ UnaryOperator::Plus };
    auto const minus = token_t{ UnaryOperator::Minus };

    auto const addition = token_t{ BinaryOperator::Addition };
    auto const multiplication = token_t{ BinaryOperator::Multiplication };

    REQUIRE(-1 == boost::apply_visitor(CompareOperatorPrecedence(), plus, addition));
    REQUIRE(-1 == boost::apply_visitor(CompareOperatorPrecedence(), minus, multiplication));
    REQUIRE(1 == boost::apply_visitor(CompareOperatorPrecedence(), addition, plus));
    REQUIRE(1 == boost::apply_visitor(CompareOperatorPrecedence(), multiplication, minus));
}

