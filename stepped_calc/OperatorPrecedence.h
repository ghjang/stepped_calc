#ifndef STEPPEDCALC_OPERATORPRECEDENCE_H
#define STEPPEDCALC_OPERATORPRECEDENCE_H


#include <cstdlib>

#include "TokenTypeDef.h"


struct IsOperatorToken : boost::static_visitor<bool>
{
    template <typename T>
    bool operator () (T) const
    {
        return false;
    }

    bool operator () (UnaryOperator) const
    {
        return true;
    }

    bool operator () (BinaryOperator) const
    {
        return true;
    }
};


struct CompareOperatorPrecedence : boost::static_visitor<int>
{
    template <typename T, typename U>
    bool operator () (T, U) const
    {
        throw std::logic_error("invalid operator comparison was attempted.");
    }

    int operator () (UnaryOperator, UnaryOperator) const
    {
        return 0;
    }

    int operator () (UnaryOperator, BinaryOperator) const
    {
        return -1;
    }

    int operator () (BinaryOperator, UnaryOperator) const
    {
        return 1;
    }

    int operator () (BinaryOperator lhs, BinaryOperator rhs) const
    {
        int diff = static_cast<int>(lhs) - static_cast<int>(rhs);
        if (std::abs(diff) < 500) {
            return 0;
        } else if (lhs > rhs) {
            return -1;
        }
        return 1;
    }
};


#endif //STEPPEDCALC_OPERATORPRECEDENCE_H

