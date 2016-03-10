#include "InfixToPostfix.h"

#include <stack>
#include "OperatorPrecedence.h"


token_list_t
infix_to_postfix(token_list_t const& tokens)
{
    token_list_t tl;

    std::stack<token_t> opStack;

    for (auto & t : tokens) {
        if (boost::apply_visitor(IsOperatorToken(), t)) {
            while (!opStack.empty()
                        && boost::apply_visitor(CompareOperatorPrecedence(), t, opStack.top()) >= 0) {
                tl.push_back(opStack.top());
                opStack.pop();
            }
            opStack.push(t);
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

