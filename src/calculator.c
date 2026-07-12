#include "../include/parser.h"
#include "../include/calculator.h"
#include "../include/evaluator.h"

#include <stdlib.h>

int calculate(const char *expression, double *result)
{
    Parser parser;

    parser_init(&parser, expression);

    ASTNode *root = parse_expression(&parser);

    if (parser.has_error || root == NULL)
    {
        free_ast(root);
        return 1;
    }

    int stats = evaluate(root, result);

    free_ast(root);

    return stats ;
}
