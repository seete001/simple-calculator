#include "../include/lexer.h"

#include <stdio.h>

// This function simply skips the spaces.
void skip_spaces(Lexer *lex)
{
    while (lex->text[lex->pos] == ' ')
        lex->pos++;
}

/* The function tries to tokenize the next token.
 * first we skip the spaces using the function above.
 * Then it checks if it is the end of the input or a new line which means the next token.
 * if it wasn't the case we wanna check if it is a number, so we go through it until it is
 * not a digit anymore then we return null.
 * if it wasn't a number or end of input so it must be a single-char token like plus sign(+) 
 * or left-right parantheses.
 * By each step we set the token type and value if it were a number
 */
void next_token(Lexer *lex)
{
    skip_spaces(lex);

    char c = lex->text[lex->pos];

    // End of input
    if (c == '\0' || c == '\n')
    {
        lex->current.type = TOK_END;
        return;
    }

    // NUMBER (int)
    if (c >= '0' && c <= '9')
    {
        double value = 0;

        while (lex->text[lex->pos] >= '0' &&
               lex->text[lex->pos] <= '9')
        {
            value = (value * 10) + 
                    (lex->text[lex->pos] - '0');
            lex->pos++;
        }

        lex->current.type = TOK_NUMBER;
        lex->current.value = value;
        return;
    }

    // Single char Tokens
    switch(c)
    {
        case '+':
            lex->current.type = TOK_PLUS;
            break;
        case '-':
            lex->current.type = TOK_MINUS;
            break;
        case '*':
            lex->current.type = TOK_MUL;
            break;
        case '/':
            lex->current.type = TOK_DIV;
            break;
        case '(':
            lex->current.type = TOK_LPAREN;
            break;
        case ')':
            lex->current.type = TOK_RPAREN;
            break;
        default:
            printf("Unknown char %c", c);
            lex->current.type = TOK_END;
            return;
    }

    lex->pos++;
}
