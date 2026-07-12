#ifndef AST_H
#define AST_H

typedef enum
{
    AST_NUMBER,
    AST_ADD,
    AST_SUB,
    AST_MUL,
    AST_DIV
} ASTType;


typedef struct ASTNode
{
    ASTType type;

    double value;

    struct ASTNode *left;
    struct ASTNode *right;

} ASTNode;


ASTNode *new_number(double value);

ASTNode *new_node(ASTType type,
                  ASTNode *left,
                  ASTNode *right);

void print_ast(ASTNode *node, int depth);

void free_ast(ASTNode *node);
#endif
