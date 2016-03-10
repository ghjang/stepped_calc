#include "Tokenizer.h"

#include <regex>


namespace
{
    struct IsTerminalConstant : boost::static_visitor<bool>
    {
        template <typename T>
        bool operator () (T) const
        {
            return false;
        }

        bool operator () (constant_t const&) const
        {
            return true;
        }
    };

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
    to_nonterminal_binary_operator_token(char c)
    {
        switch (c) {
            case '+': return BinaryOperator::Addition;
            case '-': return BinaryOperator::Subtraction;
            case '*': return BinaryOperator::Multiplication;
            case '/': return BinaryOperator::Division;

            default:
                break;
        }
        throw std::invalid_argument("invalid operator char.");
    }

    constant_t
    to_terminal_constant(std::string const& s)
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
        if (strToken.empty()) { // if not terminal constant
            if (std::isspace(*exprPos)) {
                ++exprPos;
                continue;
            }
            tokens.push_back(to_nonterminal_binary_operator_token(*exprPos));
            ++exprPos;
        } else {
            if (!tokens.empty() && boost::apply_visitor(IsTerminalConstant(), tokens.back())) {
                throw std::invalid_argument("invalid constant expression");
            }
            tokens.push_back(to_terminal_constant(strToken));
        }
    }

    return tokens;
}

