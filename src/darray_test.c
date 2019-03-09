#include "darray_test.h"

#include <stddef.h>
#include <stdio.h>

#include "darray.h"
#include "testing.h"

void darray_test_init(void)
{
    printf("Test Cases: darray_test_init\n");
    {
        darray darr_int;
        TEST_CONTEXT(darray_init(&darr_int, sizeof(int)));

        TEST_EQ(darr_int.count, 0);
        TEST_EQ(darr_int.capacity, 1);
        TEST_EQ(darr_int.type_size, sizeof(int));

        darray_uninit(&darr_int);
    }
    printf("\n");
}

void darray_test_uninit(void)
{
    printf("Test Cases: darray_test_uninit\n");
    {
        darray darr_int;
        TEST_CONTEXT(darray_init(&darr_int, sizeof(int)));
        TEST_CONTEXT(darray_uninit(&darr_int));

        TEST_EQ(darr_int.count, 0);
        TEST_EQ(darr_int.capacity, 0);
        TEST_EQ(darr_int.type_size, 0);
    }
    printf("\n");
}

void darray_test_get(void)
{
    printf("Test Cases: darray_test_get\n");
    {
        darray darr_int;
        darray_init(&darr_int, sizeof(int));

        int value;


        TEST_CONTEXT(value = 7);
        TEST_CONTEXT(darray_push_back(&darr_int, &value));

        TEST_CONTEXT(value = 99; darray_push_back(&darr_int, &value));

        TEST_EQ(darray_get(&darr_int, int, 0), 7);
        TEST_EQ(darray_get(&darr_int, int, 1), 99);

        darray_uninit(&darr_int);
    }
    printf("\n");
}

void darray_test_front(void)
{
    printf("Test Cases: darray_test_front\n");
    {
        darray darr_int;
        darray_init(&darr_int, sizeof(int));

        int value;

        TEST_CONTEXT(
            value = 7;
            darray_push_back(&darr_int, &value);
        );

        TEST_CONTEXT(
            value = 99;
            darray_push_back(&darr_int, &value);
        );

        TEST_EQ(darray_front(&darr_int, int), 7);

        darray_uninit(&darr_int);
    }
    printf("\n");
}

void darray_test_back(void)
{
    printf("Test Cases: darray_test_back\n");
    {
        darray darr_int;
        darray_init(&darr_int, sizeof(int));

        int value;

        TEST_CONTEXT(
            value = 7;
            darray_push_back(&darr_int, &value);
        );

        TEST_CONTEXT(
            value = 99;
            darray_push_back(&darr_int, &value);
        );

        TEST_EQ(darray_back(&darr_int, int), 99);

        darray_uninit(&darr_int);
    }
    printf("\n");
}

void darray_test_set(void)
{
    printf("Test Cases: darray_test_set\n");
    {
        darray darr_int;
        darray_init(&darr_int, sizeof(int));

        int value;

        TEST_CONTEXT(
            value = 7;
            darray_push_back(&darr_int, &value);
        );

        TEST_EQ(darray_get(&darr_int, int, 0), 7);

        TEST_CONTEXT(
            value = 99;
            darray_set(&darr_int, 0, &value);
        );

        TEST_EQ(darray_get(&darr_int, int, 0), 99);

        darray_uninit(&darr_int);
    }
    printf("\n");
}

void darray_test_clear(void)
{
    printf("Test Cases: darray_test_clear\n");
    {
        darray darr_int;
        darray_init(&darr_int, sizeof(int));

        TEST_CONTEXT(
            for(int i = 3; i < 10; ++i)
            {
                darray_push_back(&darr_int, &i);
            }
        );

        TEST_EQ(darr_int.count, 7);

        TEST_CONTEXT(darray_clear(&darr_int));

        TEST_EQ(darr_int.count, 0);

        darray_uninit(&darr_int);
    }
    printf("\n");
}

void darray_test_push_back(void)
{
    printf("Test Cases: darray_test_push_back\n");
    {
        darray darr_int;
        darray_init(&darr_int, sizeof(int));

        int* test_ints;
       
        TEST_CONTEXT((test_ints = (int[]){ 9, 7, 5, 3, 1 }));

        TEST_CONTEXT(darray_push_back(&darr_int, &test_ints[0]));
        TEST_EQ(darray_get(&darr_int, int, 0), 9);
        TEST_EQ(darr_int.count, 1);
        TEST_EQ(darr_int.capacity, 1);
        
        TEST_CONTEXT(darray_push_back(&darr_int, &test_ints[1]));
        TEST_EQ(darray_get(&darr_int, int, 1), 7);
        TEST_EQ(darr_int.count, 2);
        TEST_EQ(darr_int.capacity, 2);

        TEST_CONTEXT(darray_push_back(&darr_int, &test_ints[2]));
        TEST_EQ(darray_get(&darr_int, int, 2), 5);
        TEST_EQ(darr_int.count, 3);
        TEST_EQ(darr_int.capacity, 4);

        TEST_CONTEXT(darray_push_back(&darr_int, &test_ints[3]));
        TEST_EQ(darray_get(&darr_int, int, 3), 3);
        TEST_EQ(darr_int.count, 4);
        TEST_EQ(darr_int.capacity, 4);

        TEST_CONTEXT(darray_push_back(&darr_int, &test_ints[4]));
        TEST_EQ(darray_get(&darr_int, int, 4), 1);
        TEST_EQ(darr_int.count, 5);
        TEST_EQ(darr_int.capacity, 8);

        darray_uninit(&darr_int);
    }
    printf("\n");
}

void darray_test_pop_back(void)
{
    printf("Test Cases: darray_test_pop_back\n");
    {
        darray darr_int;
        darray_init(&darr_int, sizeof(int));

        int* test_ints;
        TEST_CONTEXT((test_ints = (int[]){ 1, 2, 3, 4, 5 }));

        TEST_EQ(darr_int.count, 0);

        TEST_CONTEXT(darray_pop_back(&darr_int));
        TEST_EQ(darr_int.count, 0);

        TEST_CONTEXT(
            for(int i = 0; i < 5; ++i)
            {
                darray_push_back(&darr_int, &test_ints[i]);
            }
        );
        TEST_EQ(darr_int.count, 5);

        TEST_CONTEXT(darray_pop_back(&darr_int));
        TEST_EQ(darr_int.count, 4);

        darray_uninit(&darr_int);
    }
    printf("\n");
}

void darray_test_insert(void)
{
    printf("Test Cases: darray_test_insert\n");
    {
        darray darr_int;
        darray_init(&darr_int, sizeof(int));

        int* test_ints;

        TEST_CONTEXT((test_ints = (int[]){ 9, 7, 5, 3, 1 }));

        TEST_CONTEXT(darray_push_back(&darr_int, &test_ints[0]));
        TEST_CONTEXT(darray_push_back(&darr_int, &test_ints[1]));
        TEST_CONTEXT(darray_push_back(&darr_int, &test_ints[3]));
        TEST_CONTEXT(darray_push_back(&darr_int, &test_ints[4]));

        TEST_CONTEXT(darray_insert(&darr_int, &test_ints[2], 2));
        TEST_EQ(darray_get(&darr_int, int, 0), 9);
        TEST_EQ(darray_get(&darr_int, int, 1), 7);
        TEST_EQ(darray_get(&darr_int, int, 2), 5);
        TEST_EQ(darray_get(&darr_int, int, 3), 3);
        TEST_EQ(darray_get(&darr_int, int, 4), 1);
        TEST_EQ(darr_int.count, 5);
        TEST_EQ(darr_int.capacity, 8);

        darray_uninit(&darr_int);
    }
    printf("\n");
}

void darray_test_erase(void)
{
    printf("Test Cases: darray_test_erase\n");
    {
        darray darr_int;
        darray_init(&darr_int, sizeof(int));

        int* test_ints;

        TEST_CONTEXT((test_ints = (int[]){ 9, 7, 5, 3, 1 }));
        TEST_CONTEXT(
            for(int i = 0; i < 5; ++i)
            {
                darray_push_back(&darr_int, &test_ints[i]);
            }
        );

        TEST_CONTEXT(darray_erase(&darr_int, 2));
        TEST_EQ(darray_get(&darr_int, int, 0), 9);
        TEST_EQ(darray_get(&darr_int, int, 1), 7);
        TEST_EQ(darray_get(&darr_int, int, 2), 1);
        TEST_EQ(darray_get(&darr_int, int, 3), 3);

        darray_uninit(&darr_int);
    }
    printf("\n");
}

void darray_test_remove(void)
{
    printf("Test Cases: darray_test_remove\n");
    {
        darray darr_int;
        darray_init(&darr_int, sizeof(int));

        int* test_ints;
        TEST_CONTEXT((test_ints = (int[]){ 9, 7, 5, 3, 1 }));
        TEST_CONTEXT(
            for(int i = 0; i < 5; ++i)
            {
                darray_push_back(&darr_int, &test_ints[i]);
            }
        );

        TEST_CONTEXT(darray_remove(&darr_int, 2));
        TEST_EQ(darray_get(&darr_int, int, 0), 9 );
        TEST_EQ(darray_get(&darr_int, int, 1), 7 );
        TEST_EQ(darray_get(&darr_int, int, 2), 3 );
        TEST_EQ(darray_get(&darr_int, int, 3), 1 );

        darray_uninit(&darr_int);
    }
    printf("\n");
}

void darray_test_empty(void)
{
    printf("Test Cases: darray_test_empty\n");
    {
        darray darr_int;
        darray_init(&darr_int, sizeof(int));

        TEST_EQ(darray_empty(&darr_int), true);

        TEST_CONTEXT(
            for(int i = 0; i < 5; ++i)
            {
                darray_push_back(&darr_int, &i);
            }
        );
        TEST_EQ(darray_empty(&darr_int), false);

        TEST_CONTEXT(darray_clear(&darr_int));
        TEST_EQ(darray_empty(&darr_int), true);

        darray_uninit(&darr_int);
    }
    printf("\n");
}

void darray_test_reserve(void)
{
    printf("Test Cases: darray_test_reserve\n");
    {
        darray darr_int;
        darray_init(&darr_int, sizeof(int));

        TEST_EQ(darr_int.capacity, 1);

        TEST_CONTEXT(darray_reserve(&darr_int, 10));
        TEST_EQ(darr_int.capacity, 10);

        darray_uninit(&darr_int);
    }
    printf("\n");
}

void darray_test_shrink(void)
{
    printf("Test Cases: darray_test_shrink\n");
    {
        darray darr_int;
        darray_init(&darr_int, sizeof(int));

        TEST_EQ(darr_int.capacity, 1);

        TEST_CONTEXT(darray_reserve(&darr_int, 10));
        TEST_EQ(darr_int.capacity, 10);

        TEST_CONTEXT(
            for(int i = 0; i < 5; ++i)
            {
                darray_push_back(&darr_int, &i);
            }
        );
        TEST_EQ(darr_int.count, 5);

        TEST_CONTEXT(darray_shrink(&darr_int));
        TEST_EQ(darr_int.capacity, darr_int.count);

        darray_uninit(&darr_int);
    }
    printf("\n");

}

void darray_test_run_all(void)
{
    darray_test_init();
    darray_test_uninit();

    darray_test_get();
    darray_test_front();
    darray_test_back();

    darray_test_set();
    darray_test_clear();
    darray_test_push_back();
    darray_test_pop_back();
    darray_test_insert();
    darray_test_erase();
    darray_test_remove();

    darray_test_empty();
    darray_test_reserve();
    darray_test_shrink();
}
