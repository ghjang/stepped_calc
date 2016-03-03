#include "ExpressionTree.h"

#include <stack>


namespace
{
    class DoBinaryOperation : boost::static_visitor<constant_t>
    {
    public:
        DoBinaryOperation(Operator op)
                : operator_(op)
        { }

        template <typename T1, typename T2>
        constant_t operator () (T1 & lhs, T2 & rhs) const
        {
            switch (operator_) {
                case Operator::Addition:
                    return lhs + rhs;
                case Operator::Subtraction:
                    return lhs - rhs;
                case Operator::Multiplication:
                    return lhs * rhs;
                case Operator::Division:
                    return lhs / rhs;

                default:
                    break;
            }
            throw std::invalid_argument("invalid operator value.");
        }

    private:
        Operator operator_;
    };

    constant_t
    evaluate_impl(ExpressionTreePtr ptrTree)
    {
        if (!(ptrTree->ptrLeftChild_) && !(ptrTree->ptrRightChild_)) {
            if (constant_t * pConstant = boost::get<constant_t>(&(ptrTree->item_))) {
                return *pConstant;
            }
            // NOTE: if it reaches here, something went wrong.
        }

        Operator * pOperator = boost::get<Operator>(&(ptrTree->item_));
        if (!pOperator) {
            // NOTE: if it reaches here, something went wrong.
        }

        constant_t lhsOperand = evaluate_impl(ptrTree->ptrLeftChild_);
        constant_t rhsOperand = evaluate_impl(ptrTree->ptrRightChild_);

        return boost::apply_visitor(DoBinaryOperation(*pOperator), lhsOperand, rhsOperand);
    }
} // un-named namespace


ExpressionTreePtr
make_expression_tree(token_list_t const& postfixNotationTokens)
{
    std::stack<ExpressionTreePtr> etStack;

    for (auto const& t : postfixNotationTokens) {
        if (constant_t const * pConstant = boost::get<constant_t>(&t)) {
            ExpressionTreePtr ptrTerminal = std::make_shared<ExpressionTree>(*pConstant);
            etStack.push(ptrTerminal);
        } else if (Operator const * pOperator = boost::get<Operator>(&t)) {
            ExpressionTreePtr ptrNonTerminal = std::make_shared<ExpressionTree>(*pOperator);
            ptrNonTerminal->ptrRightChild_ = etStack.top();
            etStack.pop();
            ptrNonTerminal->ptrLeftChild_ = etStack.top();
            etStack.pop();
            etStack.push(ptrNonTerminal);
        }
    }

    return etStack.top();
}

constant_t
evaluate(ExpressionTreePtr ptrTree)
{
    assert(ptrTree);
    if (!ptrTree) {
        throw std::invalid_argument("null expression tree was passed.");
    }

    return evaluate_impl(ptrTree);
}

