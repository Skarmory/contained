#include "test/testing.h"
#include "test/array_test.h"
#include "test/algo_test.h"
#include "test/darray_test.h"
#include "test/rbt_test.h"
#include "test/hashtable_test.h"

#include <stdio.h>

TestingData __testing_global;

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    //array_test_run_all();
    //algo_test_run_all();
    //darray_test_run_all();
    //rbt_test_run_all();
    //
    hashtable_test_run_all();

    TEST_SUMMARY;

    return 0;
}
