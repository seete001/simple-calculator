#include "../include/ast.h"

#include <stdio.h>

void print_ast(ASTNode *node, int depth)
{
    if (node == NULL)
        return;

    for (int i = 0; i < depth; i++)
        printf(" ");

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
    
    }
    print_ast(node->left, depth + 1);
    print_ast(node->right, depth + 1);
}
