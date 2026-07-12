#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdio.h>
#include <stdlib.h>

#define ASSERT(condition, message)        \
do                                        \
{                                         \
    if (!(condition))                     \
    {                                     \
        printf("FAIL: %s\n", message);    \
        exit(EXIT_FAILURE);               \
    }                                     \
} while (0)

#endif
