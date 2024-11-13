#include "hash_table.h"

#include "darray.h"

#include <assert.h>

/* ----- Internal ----- */

struct _hashtable
{
    darray key_table;
    darray value_table;
    uint32_t lut_key_idx;
};

// Look up table of some pre-computed prime number for key table size
const size_t _primes_lut[] = 
{
    7, 43, 89, 139, 311, 619, 1181, 2243, 4513, 9041, 18047,
    36007, 64063, 120011, 240007, 480013, 960017, 1920001
};

#define get16bits(x) (*((const uint16_t*)(x)))
const size_t _prime_lut_max = 19;
const float  _key_to_value_ratio = 1.3f;

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

static uint32_t _linear_probe(hashtable* table, uint32_t key)
{
    return (key + 1) % table->key_table.capacity;
}

static bool _is_collision(hashtable* table, uint32_t key)
{
    return darray_get(&table->key_table, int32_t, key) != -1;
}

static void _grow_hash_table(hashtable* table)
{
    ++table->lut_key_idx;
    assert(table->lut_key_idx < _prime_lut_max);

    darray_hard_clear(&table->key_table, -1);
    darray_reserve(&table->key_table, _primes_lut[table->lut_key_idx]);

    // Rehash all and create new key table
    for(size_t idx = 0; idx < table->value_table.count; ++idx)
    {
        uint8_t data = darray_get(&table->value_table, uint8_t, idx);
        uint32_t h = _hash((uint8_t*)&data, table->value_table.type_size);
        uint32_t new_index = h % table->key_table.capacity;
        darray_set(&table->key_table, new_index, &idx);
    }
} 

static void _check_and_grow(hashtable* table)
{
    if(((float)(table->value_table.count) * _key_to_value_ratio) > (float)table->key_table.count)
    {
        _grow_hash_table(table);
    }
}

/* ----- Creational ----- */

void hashtable_init(hashtable* table, size_t type_size)
{
    darray_init(&table->key_table, sizeof(uint32_t));
    darray_init(&table->value_table, type_size);
    table->lut_key_idx = 0;
    
    darray_hard_clear(&table->key_table, -1);
    darray_reserve(&table->key_table, _primes_lut[table->lut_key_idx]);
    ++table->lut_key_idx;
}

void hashtable_uninit(hashtable* table)
{
    darray_uninit(&table->value_table);
    darray_uninit(&table->key_table);
}

/* ----- Accessors ----- */

void* hashtable_get(hashtable* table, void* key)
{
    (void)table;
    (void)key;
    return NULL;
}

/* ----- Mutators ----- */

void hashtable_insert(hashtable* table, void* key, void* data)
{
    uint32_t idx = table->value_table.count;
    darray_push_back(&table->value_table, data);

    _check_and_grow(table);
    uint32_t h = _hash((uint8_t*)key, table->value_table.type_size);
    uint32_t k = h % table->key_table.capacity;

    while(_is_collision(table, k))
    {
        k = _linear_probe(table, k);
    }

    darray_set(&table->key_table, k, &idx);
}
