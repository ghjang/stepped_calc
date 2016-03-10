#include "InfixToPostfix.h"

#include <stack>
#include "OperatorPrecedence.h"


token_list_t
infix_to_postfix(token_list_t const& tokens)
{
    token_list_t tl;

    std::stack<BinaryOperator> opStack;

    for (auto & t : tokens) {
        if (BinaryOperator const * pOp = boost::get<BinaryOperator>(&t)) {
            while (!opStack.empty() && compare_precedence(*pOp, opStack.top()) >= 0) {
                tl.push_back(opStack.top());
                opStack.pop();
            }
            opStack.push(*pOp);
            continue;
        }
        tl.push_back(t);
    }

    while (!opStack.empty()) {
        tl.push_back(opStack.top());
        opStack.pop();
    }

    return tl;
}

