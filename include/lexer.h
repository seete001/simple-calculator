#ifndef LEXER_H
#define LEXER_H

typedef enum
{
    TOK_NUMBER,
    TOK_PLUS,
    TOK_MINUS,
    TOK_MUL,
    TOK_DIV,
    TOK_LPAREN,
    TOK_RPAREN,
    TOK_END
} TokenType;

typedef struct
{
    TokenType type;
    double value;
} Token;

typedef struct
{
    const char *text;
    int pos;
    Token current;
} Lexer;

void next_token(Lexer *lex);

#endif
