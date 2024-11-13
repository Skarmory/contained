#include "test/hashtable_test.h"

#include <stddef.h>
#include <stdio.h>

#include "hash_table.h"
#include "test/testing.h"

#define get16bits(x) (*((const uint16_t*)(x)))

static uint32_t _hash(uint8_t* data, int len)
{
    uint32_t hash = len;
    uint32_t tmp;
    int rem;

    if(len <= 0 || data == NULL)
    {
        return 0;
    }

    rem = len & 3;
    len >>= 2;

    for(; len > 0; --len)
    {
        hash += get16bits(data);
        tmp   = (get16bits(data + 2) << 11) ^ hash;
        hash  = (hash << 16) ^ tmp;
        data += 2 * sizeof(uint16_t);
        hash += hash >> 11;
    }

    switch(rem)
    {
        case 3:
        {
            hash += get16bits(data);
            hash ^= hash << 16;
            hash ^= ((signed char)data[sizeof(uint16_t)]) << 18;
            hash += hash >> 11;
            break;
        }
        case 2:
        {
            hash += get16bits(data);
            hash ^= hash << 11;
            hash += hash >> 17;
            break;
        }
        case 1:
        {
            hash += (signed char)*data;
            hash ^= hash << 10;
            hash += hash >> 1;
            break;
        }
    }

    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;

    return hash;
} 

void hashtable_test_hash(void)
{
    printf("Test Cases: hashtable_test_hash\n ");
    {
        uint32_t len;
        uint32_t test_1;
        uint32_t hash_1;
        uint32_t test_2;
        uint32_t hash_2;

        TEST_CASE("Test hashes equal");
        TEST_CONTEXT(len = 7);
        TEST_CONTEXT(test_1 = 7);
        TEST_CONTEXT(test_2 = 7);

        TEST_CONTEXT(hash_1 = _hash((uint8_t*)&test_1, sizeof(test_1)));
        TEST_CONTEXT(hash_2 = _hash((uint8_t*)&test_2, sizeof(test_2)));

        TEST_EQ(hash_1, hash_2);
        TEST_EVAL_INT_TYPE(hash_1, hash_2);

        TEST_CASE("Test hashes not equal");
        TEST_CONTEXT(test_1 = 3);
        TEST_CONTEXT(test_2 = 77);

        TEST_CONTEXT(hash_1 = _hash((uint8_t*)&test_1, sizeof(test_1)));
        TEST_CONTEXT(hash_2 = _hash((uint8_t*)&test_2, sizeof(test_2)));

        TEST_NEQ(hash_1, hash_2);
        TEST_EVAL_INT_TYPE(hash_1, hash_2);
    }
    printf("\n");
}

void hashtable_test_run_all(void)
{
    hashtable_test_hash();
}
