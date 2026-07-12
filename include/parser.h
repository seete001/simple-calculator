#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

typedef struct
{
    Lexer lexer;

    int has_error;
    const char *error_message;
} Parser;

void parser_init(Parser *p, const char *text);

void eat(Parser *p, TokenType expected);

void parser_error(Parser *p, const char *message);

ASTNode *parse_factor(Parser *p);

ASTNode *parse_term(Parser *p);

ASTNode *parse_expression(Parser *p);

#endif
