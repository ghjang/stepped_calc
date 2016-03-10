#include "catch.hpp"

#include "../Tokenizer.h"

#include <regex>


TEST_CASE("regex_match, digit sequence", "[stepped_calc]")
{
    {
        std::string s = "10";
        std::regex expr(R"(\d\d)");
        REQUIRE(std::regex_match(s.begin(), s.end(), expr));
    }

    {
        std::string s = "10";
        std::regex expr(R"(\d{1,2}|\d\.|\.\d)");
        REQUIRE(std::regex_match(s.begin(), s.end(), expr));
    }

    {
        std::string s = "1.";
        std::regex expr(R"(\d\.)");
        REQUIRE(std::regex_match(s.begin(), s.end(), expr));
    }

    {
        // NOTE: this seems to be a bug of clang??

        std::string s = "1.";

        std::regex expr(R"(\d{1,2}|\d\.|\.\d)");
        REQUIRE(!std::regex_match(s.begin(), s.end(), expr));

        std::regex expr1(R"(\d\.|\.\d)");
        REQUIRE(std::regex_match(s.begin(), s.end(), expr1));

        std::regex expr2(R"(\.\d|\d\.)");
        REQUIRE(std::regex_match(s.begin(), s.end(), expr2));

        std::regex expr3(R"(\d\.|\.\d|\d{1,2})");
        REQUIRE(std::regex_match(s.begin(), s.end(), expr3));

        s = "10";
        REQUIRE(std::regex_match(s.begin(), s.end(), expr3));

        s = ".1";
        REQUIRE(std::regex_match(s.begin(), s.end(), expr3));
    }

    {
        std::string s = ".1";
        std::regex expr(R"(\d{1,2}|\d\.|\.\d)");
        REQUIRE(std::regex_match(s.begin(), s.end(), expr));
    }
}

TEST_CASE("tokenize", "[stepped_calc]")
{
    token_list_t tokens = tokenize("1+2*3");
    REQUIRE(tokens.size() == 5);

    bool cr1 = (tokens[0] == token_t{ constant_t{ 1 } });
    bool cr5 = (tokens[1] == token_t{ BinaryOperator::Addition });
    bool cr2 = (tokens[2] == token_t{ constant_t{ 2 } });
    bool cr4 = (tokens[3] == token_t{ BinaryOperator::Multiplication });
    bool cr3 = (tokens[4] == token_t{ constant_t{ 3 } });
    REQUIRE(cr1);
    REQUIRE(cr2);
    REQUIRE(cr3);
    REQUIRE(cr4);
    REQUIRE(cr5);
}

