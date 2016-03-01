#include "OperatorPrecedence.h"

#include <cstdlib>


int compare_precedence(Operator lhs, Operator rhs)
{
    int diff = static_cast<int>(lhs) - static_cast<int>(rhs);
    if (std::abs(diff) < 500) {
        return 0;
    } else if (lhs > rhs) {
        return -1;
    }
    return 1;
}

