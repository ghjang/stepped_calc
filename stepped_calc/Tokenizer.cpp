#include "Tokenizer.h"

#include <regex>


namespace
{
    bool
    is_operator_char(char c)
    {
        switch (c) {
            case '+':
            case '-':
            case '*':
            case '/':
                return true;

            default:
                return false;
        }
    }

    bool
    is_digit_sequence(char prev, char c)
    {
        std::regex expr(R"(\d\.|\.\d|\d{1,2})");
        std::string s;
        if ('\0' != prev) {
            s += prev;
        }
        s += c;
        return std::regex_match(s.begin(), s.end(), expr);
    }

    template <typename Predicate>
    std::string
    take_while(std::string::const_iterator & begin,
               std::string::const_iterator end,
               Predicate && p)
    {
        std::string s;
        for ( ; begin != end && p(*begin); ++begin) {
            s += *begin;
        }
        return s;
    }

    token_t
    to_token(char c)
    {
        switch (c) {
            case '+': return Operator::Addition;
            case '-': return Operator::Subtraction;
            case '*': return Operator::Multiplication;
            case '/': return Operator::Division;

            default:
                break;
        }
        throw std::invalid_argument("invalid operator char.");
    }

    constant_t
    to_constant(std::string const& s)
    {
        if (s.find_first_of('.') != std::string::npos) {
            std::stod(s);
        }
        return std::stoi(s);
    }
} // un-named namespace


token_list_t
tokenize(std::string const& expr)
{
    token_list_t tokens;

    std::string::const_iterator exprPos = expr.begin();
    std::string::const_iterator exprEnd = expr.end();
    std::string strToken;

    while (exprPos != exprEnd) {
        strToken = take_while(
                           exprPos, exprEnd,
                           [prevChar = '\0'](char c) mutable {
                                    bool result = is_digit_sequence(prevChar, c);
                                    prevChar = c;
                                    return result;
                            }
                    );
        if (strToken.empty()) { // if not constant
            tokens.push_back(to_token(*exprPos));
            ++exprPos;
        } else {
            tokens.push_back(to_constant(strToken));
        }
    }

    return tokens;
}

