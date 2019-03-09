#include "testing.h"
#include "array_test.h"
#include "algo_test.h"
#include "darray_test.h"

#include <stdio.h>

TestingData __testing_global;

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    array_test_run_all();
    algo_test_run_all();
    darray_test_run_all();

    TEST_SUMMARY;

    return 0;
}
