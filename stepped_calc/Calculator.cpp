#include "Calculator.h"

#include "Tokenizer.h"
#include "InfixToPostfix.h"
#include "ExpressionTree.h"

constant_t calculate(std::string const& expr)
{
    auto tokens = tokenize(expr);
    auto postfixNotationTokens = infix_to_postfix(tokens);
    auto expressionTree = make_expression_tree(postfixNotationTokens);
    return evaluate(expressionTree);
}

