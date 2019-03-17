#include "test/algo_test.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "algo.h"
#include "test/testing.h"

#define ARRAY_SIZE 9

bool comp(const void* left, const void* right)
{
    return ( *((uint32_t*)left) > *((uint32_t*)right) );
}

void algo_test_quicksort(void)
{
    printf("Test Cases: quicksort\n");
    {
        uint32_t actual[ARRAY_SIZE] = { 2, 7, 1, 2, 3, 3, 5, 9, 5 };
        uint32_t expect[ARRAY_SIZE] = { 1, 2, 2, 3, 3, 5, 5, 7, 9 };

        quicksort((void*)actual, sizeof(uint32_t), ARRAY_SIZE, &comp); 

        TEST_RANGE_EQ(ARRAY_SIZE, actual, expect);
    }
    {
        uint32_t actual[1] = { 7 };
        uint32_t expect[1] = { 7 };

        quicksort((void*)actual, sizeof(uint32_t), 1, &comp); 

        TEST_RANGE_EQ(1, actual, expect);
    }
    {
        uint32_t actual;
        uint32_t expect;

        quicksort((void*)&actual, sizeof(uint32_t), 0, &comp); 

        TEST_RANGE_EQ(0, &actual, &expect);
    }
    printf("\n");
}

void algo_test_run_all(void)
{
    algo_test_quicksort();
}

