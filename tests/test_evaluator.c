#include "test_utils.h"

#include "../include/evaluator.h"
#include "../include/ast.h"


#include <stdlib.h>

void test_addition(void);
void test_division_by_zero(void);

int main(void)
{
    test_addition();
    test_division_by_zero();
    
    printf("Evaluator tests passed!\n");

    return 0;
}

void test_addition(void)
{
    ASTNode *node = new_node(AST_ADD,
                             new_number(5),
                             new_number(3));

    double result;

    int status = evaluate(node, &result);
    
    ASSERT(status == 0, "Evaluation failed!\n");
    ASSERT(result == 8, "5 + 3 must equal to 8\n"); 

    free_ast(node);
}

void test_division_by_zero(void)
{
    ASTNode *node = new_node(AST_DIV,
                             new_number(5),
                             new_number(0));

    double result;

    int status = evaluate(node, &result);

    ASSERT(status != 0, "division by zero should fail!\n");

    free_ast(node);
}
