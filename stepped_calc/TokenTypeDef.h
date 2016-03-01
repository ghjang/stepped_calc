#ifndef STEPPEDCALC_TOKENTYPEDEF_H
#define STEPPEDCALC_TOKENTYPEDEF_H


#include <string>
#include <vector>
#include "boost/variant.hpp"


enum struct Operator : int
{
    Addition        = 0,
    Subtraction     = 0,
    Multiplication  = 1,
    Division        = 1
};

enum struct Parenthesis : int
{
    Rount   = 0,
    Curly   = 1,
    Square  = 2,
    Angle   = 3
};


using operand_t = boost::variant<int, double>;

using token_t = boost::variant<Operator, Parenthesis, operand_t>;

using token_list_t = std::vector<token_t>;


#endif //STEPPEDCALC_TOKENTYPEDEF_H

