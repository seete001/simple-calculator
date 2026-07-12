#include "../include/calculator.h"

#include <stdio.h>
#include <string.h>

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
    
    double result;       

        while(fgets(buffer, BUFFER_SIZE, stdin))
        {
            if(calculate(buffer, &result) == 0)
            {
                printf("Result = %.2f\n>",result);
            }
        }

    return 0;
}
