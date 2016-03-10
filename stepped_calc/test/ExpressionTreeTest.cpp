#include "catch.hpp"

#include "../ExpressionTree.h"


TEST_CASE("make_expression_tree", "[stepped_calc]")
{

}

TEST_CASE("evaluate", "[stepped_calc]")
{
    // 1+2*3
    token_list_t postfixNotationTokens{
            constant_t{ 1 }, constant_t{ 2 }, constant_t{ 3 }, BinaryOperator::Multiplication, BinaryOperator::Addition
    };

    constant_t result = evaluate(make_expression_tree(postfixNotationTokens));
    constant_t expectedResult = 7;
    REQUIRE(result == expectedResult);
}

