#include "../include/evaluator.h"

#include <stdio.h>
#include <stdlib.h>

double evaluate(ASTNode *node)
{
    if (node == NULL)
    {
        fprintf(stderr, "Invalid AST node.\n");
        exit(1);
    }

    switch (node->type)
    {
        case AST_NUMBER:
            return node->value;

        case AST_ADD:
            return evaluate(node->left) + evaluate(node->right);

        case AST_SUB:
            return evaluate(node->left) - evaluate(node->right);

        case AST_MUL:
            return evaluate(node->left) * evaluate(node->right);

        case AST_DIV:
        {
            double rhs = evaluate(node->right);

            if (rhs == 0)
            {
                fprintf(stderr, "Division by zero.\n");
                exit(1);
            }

            return evaluate(node->left) / rhs;
        }

        default:
            fprintf(stderr, "Unknown AST node.\n");
            exit(1);
    }
}
