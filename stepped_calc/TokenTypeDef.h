#ifndef STEPPEDCALC_TOKENTYPEDEF_H
#define STEPPEDCALC_TOKENTYPEDEF_H


#include <string>
#include <vector>
#include "boost/variant.hpp"


enum struct BinaryOperator : int
{
    Addition        = 0,
    Subtraction     = 1,

    Multiplication  = 1000,
    Division        = 1001
};

enum struct Parenthesis : int
{
    RoundLeft   = 0,    // (
    RoundRight  = 1,    // )
    CurlyLeft   = 2,    // {
    CurlyRight  = 3,    // }
    SquareLeft  = 4,    // [
    SquareRight = 5,    // ]
    AngleLeft   = 6,    // <
    AngleRight  = 7     // >
};


using constant_t = boost::variant<int, double>;

using token_t = boost::variant<BinaryOperator, Parenthesis, constant_t>;

using token_list_t = std::vector<token_t>;


#endif //STEPPEDCALC_TOKENTYPEDEF_H

