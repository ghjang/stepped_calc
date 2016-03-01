#include "catch.hpp"

#include "../ExpressionTree.h"


TEST_CASE("make_expression_tree", "[stepped_calc]")
{

}

TEST_CASE("evaluate_expression_tree", "[stepped_calc]")
{
    token_list_t postfixNotationTokens{
            operand_t{ 1 }, operand_t{ 2 }, operand_t{ 3 }, Operator::Multiplication, Operator::Addition // 1+2*3
    };

    operand_t result = evaluate_expression_tree(make_expression_tree(postfixNotationTokens));
    operand_t expectedResult = 7;
    REQUIRE(result == expectedResult);
}

