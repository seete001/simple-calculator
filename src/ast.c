#include "../include/ast.h"

#include <stdlib.h>
#include <stdio.h>

void print_ast(ASTNode *node, int depth)
{
    if (node == NULL)
        return;

    for (int i = 0; i < depth; i++)
        printf("    ");

    switch(node->type)
    {
        case AST_NUMBER:
            printf("NUMBER: %.2f\n", node->value);
            break;

        case AST_ADD:
            printf("ADD\n");
            break;
        
        case AST_SUB:
            printf("SUB\n");
            break;
        
        case AST_MUL:
            printf("MUL\n");
            break;
        
        case AST_DIV:
            printf("DIV\n");
            break;
        default:
            printf("Unknown\n");
            break;
    
    }
    print_ast(node->left, depth + 1);
    print_ast(node->right, depth + 1);
}

void free_ast(ASTNode *node)
{
    if(!node)
    {
        return;
    }

    free_ast(node->left);
    free_ast(node->right);

    free(node);
}
