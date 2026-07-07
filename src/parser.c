#include <stdlib.h>
#include <stdio.h>

#include "../include/parser.h"


ASTNode *parse_expression(Parser *p)
{
    ASTNode *left = parse_term(p);

    while (p->lexer.current.type == TOK_PLUS ||
           p->lexer.current.type == TOK_MINUS)
    {
        TokenType op = p->lexer.current.type;
        
        eat(p, op);

        ASTNode *right = parse_term(p);
        
        if (op == TOK_PLUS)
            left = new_node(AST_ADD, left, right);
        else
            left = new_node(AST_SUB, left, right);
    }

    return left;
}

/*
 *This function is for handling numbers like 5 or (5).
 * */
ASTNode *parse_factor(Parser *p)
{
    Token token = p->lexer.current;

    // NUMBER case
    if (token.type == TOK_NUMBER)
    {
        ASTNode *node = new_number(token.value);
        
        eat(p, TOK_NUMBER);

        return node;
    }

    // Parantheses case
    else if (token.type == TOK_LPAREN)
    {
        eat(p, TOK_LPAREN);

        ASTNode *node = parse_expression(p);
    
        eat(p, TOK_RPAREN);

        return node;
    }

    else
    {
        printf("Unexpected token\n");
        exit(1);
        return NULL;
    }
}

/*
 * The function handles multiplication and division.
 * */
ASTNode *parse_term(Parser *p)
{
    ASTNode *left = parse_factor(p);
    

    while(p->lexer.current.type == TOK_DIV ||
          p->lexer.current.type == TOK_MUL)
    {
        TokenType op = p->lexer.current.type;

        eat(p, op);

        ASTNode *right = parse_factor(p);

        if (op == TOK_MUL)
            left = new_node(AST_MUL, left, right);
        else
            left = new_node(AST_DIV, left, right);
    }

    return left;
}

/*
 *The function is creating a AST number node.
 * */
ASTNode *new_number(double value)
{
    ASTNode *node = malloc(sizeof(ASTNode));

    node->type = AST_NUMBER;
    node->value = value;
    
    node->left = NULL;
    node->right = NULL;

    return node;
}

/*
 *The function creates AST char node like ( or + and etc.
 * */
ASTNode *new_node(ASTType type,
                  ASTNode *left,
                  ASTNode *right)
{
    ASTNode *node = malloc(sizeof(ASTNode));

    node->type = type;
    node->value = 0;

    node->left = left;
    node->right = right;

    return node;
}

/*
 * This will initialize the parse. it connects the parser to the text we got.
 * */
void parser_init(Parser *p, const char *text)
{
    p->lexer.text = text;
    p->lexer.pos = 0;

    next_token(&p->lexer);
}

/*
 * The bridge of our logic is the function eat aka consume.
 * which would increment the position of tokens and checks for Syntax Error.
 * */
void eat(Parser *p, TokenType expected)
{
    if(p->lexer.current.type == expected)
    {
        next_token(&p->lexer);
    }
    else
    {
        printf("Syntax Error!\n");
        exit(1);
    }
}
