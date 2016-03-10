#include "catch.hpp"

#include "../OperatorPrecedence.h"


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

