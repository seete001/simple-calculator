#include "../include/evaluator.h"

#include <stdio.h>

int evaluate(ASTNode *node, double *result)
{
    if (!node)
    {
        fprintf(stderr, "Invalid AST node.\n");
        return 1;
    }

    switch (node->type)
    {
        case AST_NUMBER:
            *result = node->value;
            return 0;


        case AST_ADD:
        {
            double lhs;
            double rhs;

            if (evaluate(node->left, &lhs))
                return 1;

            if (evaluate(node->right, &rhs))
                return 1;

            *result = lhs + rhs;
            return 0;
        }


        case AST_SUB:
        {
            double lhs;
            double rhs;

            if (evaluate(node->left, &lhs))
                return 1;

            if (evaluate(node->right, &rhs))
                return 1;

            *result = lhs - rhs;
            return 0;
        }


        case AST_MUL:
        {
            double lhs;
            double rhs;

            if (evaluate(node->left, &lhs))
                return 1;

            if (evaluate(node->right, &rhs))
                return 1;

            *result = lhs * rhs;
            return 0;
        }


        case AST_DIV:
        {
            double lhs;
            double rhs;

            if (evaluate(node->left, &lhs))
                return 1;

            if (evaluate(node->right, &rhs))
                return 1;

            if (rhs == 0)
            {
                fprintf(stderr, "Division by zero.\n");
                return 1;
            }

            *result = lhs / rhs;
            return 0;
        }


        default:
            fprintf(stderr, "Unknown AST node.\n");
            return 1;
    }
}
