#include "array_test.h"

#include <stdbool.h>
#include <stdio.h>
#include "array.h"
#include "testing.h"

struct TestStruct
{
    char _char;
    int  _int;
};

void array_test_init(void)
{
    printf("Test Cases: array_test_init\n");
    {
        TEST_CONTEXT(array(int, 100) arr);
        TEST_CONTEXT(array_init(&arr));

        TEST_EQ(sizeof(arr.data), sizeof(int) * 100);
        TEST_EQ(arr.count, 0);
        TEST_EQ(arr.capacity, 100);
    }
    {
        array(struct TestStruct, 100) arr;
        TEST_CONTEXT(array_init(&arr));

        TEST_EQ(sizeof(arr.data), sizeof(struct TestStruct) * 100);
        TEST_EQ(arr.count, 0);
        TEST_EQ(arr.capacity, 100);
    }
    printf("\n");
}

void array_test_get(void)
{
    array(int, 100) arr1;
    array_init(&arr1);

    printf("Test Cases: array_test_at\n");
    {

        TEST_CONTEXT(array_fill(&arr1, 0));

        TEST_CONTEXT(
            arr1.data[77] = 7777;
            arr1.data[21] = 1111;
            arr1.data[99] = 1234;
        );

        TEST_EQ(array_get(&arr1, 77), 7777);
        TEST_EQ(array_get(&arr1, 21), 1111);
        TEST_EQ(array_get(&arr1, 99), 1234);
    }
    printf("\n");
}

void array_test_front(void)
{
    array(int, 100) arr1;
    array_init(&arr1);

    printf("Test Cases: array_test_front\n");
    {
        TEST_CONTEXT(
            for(size_t i = 0; i < arr1.capacity; ++i)
            {
                array_push(&arr1, 0);
            }
        );

        TEST_CONTEXT(
            arr1.data[0] = 7;
            arr1.data[1] = 8;
            arr1.data[3] = 9;
        );

        TEST_EQ(array_front(&arr1), 7);
    }
    printf("\n");
}

void array_test_back(void)
{
    array(int, 100) arr1;
    array_init(&arr1);

    for(uint32_t i = 0; i < arr1.capacity; ++i)
    {
        array_push(&arr1, i+7);
    }

    printf("Test Cases: array_test_back\n");
    {
        TEST_EQ(array_back(&arr1), 106);

        array_pop(&arr1);

        TEST_EQ(array_back(&arr1), 105);

        array_pop(&arr1);

        TEST_EQ(array_back(&arr1), 104);
    }
    printf("\n");
}

void array_test_set(void)
{
    array(int, 100) arr;
    array_init(&arr);

    printf("Test Cases: array_test_set\n");
    {
        TEST_CONTEXT(array_set(&arr, 10, 77));
        TEST_EQ(arr.data[10], 77);
    }
    printf("\n");
}

void array_test_push(void)
{
    array(int, 100) arr1;
    array_init(&arr1);

    array(struct TestStruct, 100) arr2;
    array_init(&arr2);

    printf("Test Cases: array_test_push\n");
    {
        array_push(&arr1, 3);
        TEST_EQ(arr1.data[0], 3);

        array_push(&arr1, 777);
        TEST_EQ(arr1.data[1], 777);

        array_push(&arr1, -9999);
        TEST_EQ(arr1.data[2], -9999);

        TEST_EQ(arr1.count, 3);
        TEST_EQ(arr1.capacity, 100);
    }
    {
        array_push(&arr2, ((struct TestStruct){ 'a', 0 }));
        TEST_EQ(arr2.data[0]._char, 'a');
        TEST_EQ(arr2.data[0]._int, 0);

        array_push(&arr2, ((struct TestStruct){ 'b', 1 }));
        TEST_EQ(arr2.data[1]._char, 'b');
        TEST_EQ(arr2.data[1]._int, 1);

        array_push(&arr2, ((struct TestStruct){ 'c', 2 }));
        TEST_EQ(arr2.data[2]._char, 'c');
        TEST_EQ(arr2.data[2]._int, 2);

        TEST_EQ(arr2.count, 3);
        TEST_EQ(arr2.capacity, 100);
    }
    printf("\n");
}

void array_test_pop(void)
{
    array(int, 100) arr1;
    array_init(&arr1);

    array(struct TestStruct, 100) arr2;
    array_init(&arr2);

    arr1.data[0] = 7;
    arr1.data[1] = 6;
    arr1.data[2] = 5;
    arr1.count = 3;

    arr2.data[0] = (struct TestStruct){ 'a', 99 };
    arr2.data[1] = (struct TestStruct){ 'b', 88 };
    arr2.data[2] = (struct TestStruct){ 'c', 77 };
    arr2.count = 3;

    printf("Test Cases: array_test_pop\n");
    {
        TEST_EQ(arr1.count, 3);
        TEST_EQ(arr1.data[arr1.count - 1], 5);

        array_pop(&arr1);
        TEST_EQ(arr1.count, 2);
        TEST_EQ(arr1.data[arr1.count - 1], 6);

        array_pop(&arr1);
        TEST_EQ(arr1.count, 1);
        TEST_EQ(arr1.data[arr1.count - 1], 7);

        array_pop(&arr1);
        TEST_EQ(arr1.count, 0);
    }
    {
        TEST_EQ(arr2.count, 3);
        TEST_EQ(arr2.data[arr2.count-1]._char, 'c');
        TEST_EQ(arr2.data[arr2.count-1]._int, 77);

        array_pop(&arr2);
        TEST_EQ(arr2.count, 2);
        TEST_EQ(arr2.data[arr2.count-1]._char, 'b');
        TEST_EQ(arr2.data[arr2.count-1]._int, 88);

        array_pop(&arr2);
        TEST_EQ(arr2.count, 1);
        TEST_EQ(arr2.data[arr2.count-1]._char, 'a');
        TEST_EQ(arr2.data[arr2.count-1]._int, 99);

        array_pop(&arr2);
        TEST_EQ(arr2.count, 0);
    }
    printf("\n");
}

void array_test_fill(void)
{
    array(int, 1000) arr1;
    array_init(&arr1);

    printf("Test Cases: array_test_fill\n");
    {
        array_fill(&arr1, 7);
        TEST_EQ(array_get(&arr1, 0), 7);
        TEST_EQ(array_get(&arr1, 500), 7);
        TEST_EQ(array_get(&arr1, 999), 7);

        array_fill(&arr1, 1234);
        TEST_EQ(array_get(&arr1, 0), 1234);
        TEST_EQ(array_get(&arr1, 500), 1234);
        TEST_EQ(array_get(&arr1, 999), 1234);
    }
    printf("\n");
}

void array_test_empty(void)
{
    array(int, 100) arr1;
    array_init(&arr1);

    printf("Test Cases: array_test_empty\n");
    {
        TEST_EQ(array_empty(&arr1), true);

        array_push(&arr1, 1);

        TEST_EQ(array_empty(&arr1), false);
    }
    printf("\n");
}

void array_test_run_all(void)
{
    array_test_init();
    array_test_get();
    array_test_front();
    array_test_back();
    array_test_set();
    array_test_push();
    array_test_pop();
    array_test_empty();
}
