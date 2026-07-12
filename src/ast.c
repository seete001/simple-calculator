#include "../include/ast.h"

#include <stdlib.h>
#include <stdio.h>


/*
 *The function is creating a AST number node.
 */
ASTNode *new_number(double value)
{
    ASTNode *node = malloc(sizeof(ASTNode));

    if(!node)
    {
        return NULL;
    }

    node->type = AST_NUMBER;
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

/*
 *The function creates AST char node like ( or + and etc.
 */
ASTNode *new_node(ASTType type,
                  ASTNode *left,
                  ASTNode *right)
{
    ASTNode *node = malloc(sizeof(ASTNode));

    if(!node)
    {
        return NULL;
    }

    node->type = type;
    node->value = 0;
    node->left = left;
    node->right = right;

    return node;
}

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
