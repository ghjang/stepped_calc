#ifndef STEPPEDCALC_EXPRESSIONTREE_H
#define STEPPEDCALC_EXPRESSIONTREE_H


#include "TokenTypeDef.h"

#include <memory>


struct ExpressionTree;

using ExpressionTreePtr = std::shared_ptr<ExpressionTree>;


struct ExpressionTree
{
    token_t item_;
    ExpressionTreePtr ptrLeftChild_;
    ExpressionTreePtr ptrRightChild_;
};


ExpressionTreePtr
make_expression_tree(token_list_t const& postfixNotationTokens);

operand_t
evaluate_expression_tree(ExpressionTreePtr ptrTree);


#endif //STEPPEDCALC_EXPRESSIONTREE_H
