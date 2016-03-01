#ifndef STEPPEDCALC_TOKENTYPEDEF_H
#define STEPPEDCALC_TOKENTYPEDEF_H


#include <string>
#include "boost/variant.hpp"


enum struct Operator : int
{
    Addition        = 0,
    Subtraction     = 0,
    Multiplication  = 1,
    Division        = 1
};


using operand_t = boost::variant<int, double>;

using token_t = boost::variant<Operator, operand_t>;


#endif //STEPPEDCALC_TOKENTYPEDEF_H

