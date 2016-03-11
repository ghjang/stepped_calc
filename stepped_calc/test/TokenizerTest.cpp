#include "catch.hpp"

#include "../Tokenizer.h"

#include <regex>
#include <iostream>


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

TEST_CASE("invalid constant sequence", "[stepped_calc]")
{
    bool exceptionThrown = false;
    try {
        token_list_t tokens = tokenize("1 2");
    } catch (std::invalid_argument const& e) {
        REQUIRE(0 == strcmp(e.what(), "invalid constant expression"));
        exceptionThrown = true;
    }
    REQUIRE(exceptionThrown);
}

TEST_CASE("unary operator", "[stepped_calc]")
{
    auto const plus = token_t{ UnaryOperator::Plus };
    auto const minus = token_t{ UnaryOperator::Minus };
    auto const one = token_t{ constant_t{ 1 } };
    auto const lhsRoundParen = token_t{ Parenthesis::RoundLeft };
    auto const rhsRoundParen = token_t{ Parenthesis::RoundRight };

    {
        token_list_t tokens = tokenize("+1");
        REQUIRE(tokens.size() == 2);
        REQUIRE((tokens[0] == plus));
        REQUIRE((tokens[1] == one));
    }

    {
        token_list_t tokens = tokenize("-1");
        REQUIRE(tokens.size() == 2);
        REQUIRE((tokens[0] == minus));
        REQUIRE((tokens[1] == one));
    }

    {
        token_list_t tokens = tokenize("++1");
        REQUIRE(tokens.size() == 3);
        REQUIRE((tokens[0] == plus));
        REQUIRE((tokens[1] == plus));
        REQUIRE((tokens[2] == one));
    }

    {
        token_list_t tokens = tokenize("--1");
        REQUIRE(tokens.size() == 3);
        REQUIRE((tokens[0] == minus));
        REQUIRE((tokens[1] == minus));
        REQUIRE((tokens[2] == one));
    }

    {
        token_list_t tokens = tokenize("+-1");
        REQUIRE(tokens.size() == 3);
        REQUIRE((tokens[0] == plus));
        REQUIRE((tokens[1] == minus));
        REQUIRE((tokens[2] == one));
    }

    {
        token_list_t tokens = tokenize("-(-1)");
        REQUIRE(tokens.size() == 5);
        REQUIRE((tokens[0] == minus));
        REQUIRE((tokens[1] == lhsRoundParen));
        REQUIRE((tokens[2] == minus));
        REQUIRE((tokens[3] == one));
        REQUIRE((tokens[4] == rhsRoundParen));
    }
}

