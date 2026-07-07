#include "../include/ast.h"
#include "../include/parser.h"
#include "../include/evaluator.h"

#include <stdio.h>

#define BUFFER_SIZE 256



/*
 *  Expression := Term (('+' | '-') Term)*
 *
 *  Term       := Factor (('*' | '/') Factor)*
 *
 *  Factor     := NUMBER
 *             | '(' Expression ')'
 */

int main(void)
{
    char buffer[BUFFER_SIZE];

    fgets(buffer, BUFFER_SIZE, stdin);
    
    
    Parser parser;

    parser_init(&parser, buffer);


    ASTNode *root = parse_expression(&parser);

    print_ast(root, 0);

    double result = evaluate(root);

    printf("Result = %.2f\n", result);

    return 0;
}
