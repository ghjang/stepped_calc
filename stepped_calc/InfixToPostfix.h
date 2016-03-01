#ifndef STEPPEDCALC_INFIXTOPOSTFIX_H
#define STEPPEDCALC_INFIXTOPOSTFIX_H


#include "TokenTypeDef.h"

#include <vector>


std::vector<token_t> infix_to_postfix(std::string const& expr);


#endif //STEPPEDCALC_INFIXTOPOSTFIX_H

