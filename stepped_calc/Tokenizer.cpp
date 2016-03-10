#include "Tokenizer.h"

#include <regex>
#include <stack>


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

    struct IsLeftParenthesisToken : boost::static_visitor<bool>
    {
        template <typename T>
        bool operator () (T) const
        {
            return false;
        }

        bool operator () (Parenthesis paren) const
        {
            switch (paren) {
                case Parenthesis::RoundLeft:
                case Parenthesis::CurlyLeft:
                case Parenthesis::SquareLeft:
                case Parenthesis::AngleLeft:
                    return true;

                default:
                    break;
            }
            return false;
        }
    };

    bool
    is_unary_operator_char(char c)
    {
        switch (c) {
            case '+':
            case '-':
                return true;

            default:
                return false;
        }
    }

    bool
    is_binary_operator_char(char c)
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
    is_parenthesis_char(char c)
    {
        switch (c) {
            case '(':
            case ')':
            case '{':
            case '}':
            case '[':
            case ']':
            case '<':
            case '>':
                return true;

            default:
                return false;
        }
    }

    bool
    is_left_parenthesis_char(char c)
    {
        switch (c) {
            case '(':
            case '{':
            case '[':
            case '<':
                return true;

            default:
                return false;
        }
    }

    bool
    is_matching_parenthesis(char const leftParen, char const rightParen)
    {
        if ((leftParen == '(' && rightParen == ')')
                || (leftParen == '{' && rightParen == '}')
                || (leftParen == '[' && rightParen == ']')
                || (leftParen == '<' && rightParen == '>')) {
            return true;
        }
        return false;
    }

    Parenthesis
    to_nonterminal_parenthesis_token(char c)
    {
        switch (c) {
            case '(': return Parenthesis::RoundLeft;
            case ')': return Parenthesis::RoundRight;
            case '{': return Parenthesis::CurlyLeft;
            case '}': return Parenthesis::CurlyRight;
            case '[': return Parenthesis::SquareLeft;
            case ']': return Parenthesis::SquareRight;
            case '<': return Parenthesis::AngleLeft;
            case '>': return Parenthesis::AngleRight;

            default:
                break;
        }
        throw std::invalid_argument("invalid parenthesis char");
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

    UnaryOperator
    to_nonterminal_unary_operator_token(char c)
    {
        switch (c) {
            case '+': return UnaryOperator::Plus;
            case '-': return UnaryOperator::Minus;

            default:
                break;
        }
        throw std::invalid_argument("invalid unary operator char.");
    }

    BinaryOperator
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
        throw std::invalid_argument("invalid binary operator char.");
    }

    token_t
    to_nonterminal_token(char c)
    {
        if (is_parenthesis_char(c)) {
            return to_nonterminal_parenthesis_token(c);
        }
        if (is_unary_operator_char(c)) {
            return to_nonterminal_unary_operator_token(c);
        }
        throw std::invalid_argument("invalid first char");
    }

    token_t
    to_nonterminal_token(token_t const& prevToken, char c)
    {
        if (is_parenthesis_char(c)) {
            return to_nonterminal_parenthesis_token(c);
        }
        if (boost::apply_visitor(IsLeftParenthesisToken(), prevToken)) {
            return to_nonterminal_unary_operator_token(c);
        }
        if (BinaryOperator const * pOp = boost::get<BinaryOperator>(&prevToken)) {
            return to_nonterminal_unary_operator_token(c);
        }
        return to_nonterminal_binary_operator_token(c);
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

    std::stack<char> parenthesisStack;

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
            if (is_parenthesis_char(*exprPos)) {
                if (is_left_parenthesis_char(*exprPos)) {
                    parenthesisStack.push(*exprPos);
                } else {
                    if (!is_matching_parenthesis(parenthesisStack.top(), *exprPos)) {
                        throw std::invalid_argument("no matching parenthesis");
                    }
                    parenthesisStack.pop();
                }
            }
            if (tokens.empty()) { // if first token,
                tokens.push_back(to_nonterminal_token(*exprPos));
            } else {
                tokens.push_back(to_nonterminal_token(tokens.back(), *exprPos));
            }
            ++exprPos;
        } else {
            if (!tokens.empty() && boost::apply_visitor(IsTerminalConstant(), tokens.back())) {
                throw std::invalid_argument("invalid constant expression");
            }
            tokens.push_back(to_terminal_constant(strToken));
        }
    }

    if (!parenthesisStack.empty()) {
        throw std::invalid_argument("no matching parenthesis");
    }

    return tokens;
}

