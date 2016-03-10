#include "catch.hpp"

#include "../InfixToPostfix.h"


TEST_CASE("infix notation to postfix notation", "[stepped_calc]")
{
    // "1+2*3"
    token_list_t tokens{
            constant_t{ 1 }, BinaryOperator::Addition, constant_t{ 2 }, BinaryOperator::Multiplication, constant_t{ 3 }
    };

    auto n = infix_to_postfix(tokens);
    REQUIRE(n.size() == 5);

    bool cr1 = (n[0] == token_t{ constant_t{ 1 } });
    bool cr2 = (n[1] == token_t{ constant_t{ 2 } });
    bool cr3 = (n[2] == token_t{ constant_t{ 3 } });
    bool cr4 = (n[3] == token_t{ BinaryOperator::Multiplication });
    bool cr5 = (n[4] == token_t{ BinaryOperator::Addition });
    REQUIRE(cr1);
    REQUIRE(cr2);
    REQUIRE(cr3);
    REQUIRE(cr4);
    REQUIRE(cr5);
}

