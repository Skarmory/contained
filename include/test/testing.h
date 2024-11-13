#ifndef TESTING_H
#define TESTING_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct __TestingData
{
    size_t tests_passed;    
    size_t tests_failed;
} TestingData;

extern TestingData __testing_global;

#define TEST_RANGE_EQ(count, actual, expect)\
    do\
    {\
        bool __test_success = true;\
        for(int __test_counter = 0; __test_counter < count; ++__test_counter)\
        {\
            if((actual)[__test_counter] != (expect)[__test_counter])\
            {\
                __test_success = false;\
                break;\
            }\
        }\
        printf("\t\tTEST_RANGE_EQ\t(%s == %s) ", #actual, #expect);\
        printf("%s\n", __test_success ? "SUCCESS" : "FAILURE");\
    }\
    while(0)

#define TEST_EQ(actual, expect)\
    do\
    {\
        printf("\t\tTEST_EQ (%s, %s) ", #actual, #expect);\
        bool res = actual == expect;\
        if(res)\
            ++__testing_global.tests_passed;\
        else\
            ++__testing_global.tests_failed;\
        printf("%s\n", (res) ? "SUCCESS" : "FAILURE");\
    }\
    while(0)

#define TEST_NEQ(actual, expect)\
    do\
    {\
            printf("\t\tTEST_NEQ (%s, %s) ", #actual, #expect);\
            bool res = actual != expect;\
            if(res)\
                ++__testing_global.tests_passed;\
            else\
                ++__testing_global.tests_failed;\
            printf("%s\n", (res) ? "SUCCESS" : "FAILURE");\
    }\
    while(0)

#define TEST_EVAL_INT_TYPE(actual, expect)\
    do\
    {\
        printf("\t\tEVAL: %s: %d =? %s: %d\n", #actual, actual, #expect, expect);\
    }\
    while(0)

#define TEST_CONTEXT(op)\
    printf("\t\tEXEC: %s\n", #op);\
    op;

#define TEST_CASE(name)\
    do\
    {\
        printf("\tCASE: %s\n", name);\
    }\
    while(0)

#define TEST_SUMMARY\
    do\
    {\
        printf("Test Summary:\n");\
        printf("\tPassed: %zu\n", __testing_global.tests_passed);\
        printf("\tFailed: %zu\n", __testing_global.tests_failed);\
    }\
    while(0)

#endif
