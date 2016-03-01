#ifndef STEPPEDCALC_INFIXTOPOSTFIX_H
#define STEPPEDCALC_INFIXTOPOSTFIX_H


#include "TokenTypeDef.h"

#include <vector>


using token_list_t = std::vector<token_t>;


token_list_t infix_to_postfix(token_list_t const& tokens);


#endif //STEPPEDCALC_INFIXTOPOSTFIX_H

