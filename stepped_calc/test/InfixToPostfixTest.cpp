#include "catch.hpp"

#include "../InfixToPostfix.h"


TEST_CASE("operator precedence", "[stepped_calc]")
{
    static_assert(Operator::Addition == Operator::Addition, "");
    static_assert(Operator::Addition == Operator::Subtraction, "");

    static_assert(Operator::Multiplication == Operator::Multiplication, "");
    static_assert(Operator::Multiplication == Operator::Division, "");

    static_assert(Operator::Addition < Operator::Multiplication, "");
    static_assert(Operator::Addition < Operator::Division, "");
}

TEST_CASE("infix notation to postfix notation", "[stepped_calc]")
{
    auto n = infix_to_postfix("1+2*3");
    REQUIRE(n.size() == 5);

    bool cr1 = (n[0] == token_t{ operand_t{ 1 } });
    bool cr2 = (n[1] == token_t{ operand_t{ 2 } });
    bool cr3 = (n[2] == token_t{ operand_t{ 3 } });
    bool cr4 = (n[3] == token_t{ Operator::Multiplication });
    bool cr5 = (n[4] == token_t{ Operator::Addition });
    REQUIRE(cr1);
    REQUIRE(cr2);
    REQUIRE(cr3);
    REQUIRE(cr4);
    REQUIRE(cr5);
}

