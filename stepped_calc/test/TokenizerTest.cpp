#include "catch.hpp"

#include "../Tokenizer.h"


TEST_CASE("tokenize", "[stepped_calc]")
{
    token_list_t tokens = tokenize("1+2*3");
    REQUIRE(tokens.size() == 5);

    bool cr1 = (tokens[0] == token_t{ operand_t{ 1 } });
    bool cr5 = (tokens[1] == token_t{ Operator::Addition });
    bool cr2 = (tokens[2] == token_t{ operand_t{ 2 } });
    bool cr4 = (tokens[3] == token_t{ Operator::Multiplication });
    bool cr3 = (tokens[4] == token_t{ operand_t{ 3 } });
    REQUIRE(cr1);
    REQUIRE(cr2);
    REQUIRE(cr3);
    REQUIRE(cr4);
    REQUIRE(cr5);
}

