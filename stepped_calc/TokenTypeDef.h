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


enum struct ValueType : int
{
    Integer = 0
};


struct Operand
{
    ValueType vt_;
    std::string expr_;
};


using token_t = boost::variant<Operand, Operator>;


inline bool operator == (Operand const& lhs, Operand const& rhs)
{ return lhs.vt_ == rhs.vt_ && lhs.expr_ == rhs.expr_; }

inline bool operator != (Operand const& lhs, Operand const& rhs)
{ return !(lhs == rhs); }


#endif //STEPPEDCALC_TOKENTYPEDEF_H

