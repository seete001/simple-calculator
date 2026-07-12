#include <stdlib.h>
#include <stdio.h>

#include "../include/parser.h"

/*
 * Parses addition and subtraction expressions.
 * This is the highest level of the grammar and combines terms
 * using '+' and '-' operators.
 */
ASTNode *parse_expression(Parser *p)
{
    if (p->has_error)
    {
        return NULL;
    }

    ASTNode *left = parse_term(p);

    if (!left)
    {
        return NULL;
    }

    while (p->lexer.current.type == TOK_PLUS ||
           p->lexer.current.type == TOK_MINUS)
    {
        TokenType op = p->lexer.current.type;

        eat(p, op);

        ASTNode *right = parse_term(p);

        if (!right)
        {
            return NULL;
        }

        ASTNode *node;

        if (op == TOK_PLUS)
        {
            node = new_node(AST_ADD, left, right);
        }
        else
        {
            node = new_node(AST_SUB, left, right);
        }

        if (!node)
        {
            return NULL;
        }
        left = node;
    }

    return left;
}

/*
 * Parses multiplication and division expressions.
 * Terms have higher precedence than addition and subtraction.
 */
ASTNode *parse_term(Parser *p)
{
    if (p->has_error)
    {
        return NULL;
    }

    ASTNode *left = parse_factor(p);

    if (!left)
    {
        return NULL;
    }

    while (p->lexer.current.type == TOK_MUL ||
           p->lexer.current.type == TOK_DIV)
    {
        TokenType op = p->lexer.current.type;

        eat(p, op);

        ASTNode *right = parse_factor(p);

        if (!right)
        {
            return NULL;
        }

        ASTNode *node;

        if (op == TOK_MUL)
        {
            node = new_node(AST_MUL, left, right);
        }
        else
        {
            node = new_node(AST_DIV, left, right);
        }

        if (!node)
        {
            return NULL;
        }

        left = node;
    }

    return left;
}

/*
 * Parses a single factor.
 * A factor can be either:
 *   - a number
 *   - an expression enclosed in parentheses
 */
ASTNode *parse_factor(Parser *p)
{
    if (p->has_error)
    {
        return NULL;
    }

    Token token = p->lexer.current;

    if (token.type == TOK_NUMBER)
    {
        ASTNode *node = new_number(token.value);

        if (!node)
        {
            return NULL;
        }

        eat(p, TOK_NUMBER);

        return node;
    }

    if (token.type == TOK_LPAREN)
    {
        eat(p, TOK_LPAREN);

        ASTNode *node = parse_expression(p);

        if (!node)
        {
            return NULL;
        }

        eat(p, TOK_RPAREN);

        return node;
    }

    parser_error(p, "Expected number or '('");

    return NULL;
}

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

/*
 * This will initialize the parse. it connects the parser to the text we got.
 */
void parser_init(Parser *p, const char *text)
{
    p->lexer.text = text;
    p->lexer.pos = 0;

    p->has_error = 0;
    p->error_message = NULL;

    next_token(&p->lexer);
}

/*
 * The bridge of our logic is the function eat aka consume.
 * which would increment the position of tokens and checks for Syntax Error.
 */
void eat(Parser *p, TokenType expected)
{
    if(p->has_error) 
    {
        return;
    }

    if(p->lexer.current.type == expected)
    {
        next_token(&p->lexer);
    }

    else
    {
        parser_error(p, "Syntax error: Unexpected Token!\n");
    }
}

/*
 * The function acts as a error handler.
 */
void parser_error(Parser *p, const char *message)
{
    if (p->has_error)
    {
        return;
    }

    p->has_error = 1;
    p->error_message = message;
}
