#include "darray.h"

#include <stdlib.h>
#include <stdio.h>

/* ---------- Internal ---------- */

#define _die_if_true(expr, msg)\
    do\
    {\
        if((expr))\
        {\
            fprintf(stderr, msg);\
            abort();\
        }\
    }\
    while(0)

#define _grow_and_check_oom(obj) ((obj)->count == (obj)->capacity ? !_grow_memory((obj)) : false)

static bool _grow_memory(darray* obj)
{
    size_t new_cap = obj->capacity << 1;
    void*  new_ptr = realloc(obj->data, obj->type_size * new_cap);
    if(!new_ptr)
        return false;

    obj->capacity = new_cap;
    obj->data = new_ptr;
    return true;
}

static void* _get_data_ptr(darray* obj, size_t index)
{
    return ((uint8_t*)obj->data + (obj->type_size * index));
}

static size_t _size_bytes(darray* obj, size_t index)
{
    return obj->type_size * index;
}

/* ---------- Creational ---------- */

void darray_init(darray* obj, size_t type_size)
{
    obj->count = 0;
    obj->capacity = 1;
    obj->type_size = type_size;
    obj->data = malloc(type_size);
}

void darray_uninit(darray* obj)
{
    obj->count = 0;
    obj->capacity = 0;
    obj->type_size = 0;
    free(obj->data);
}

/* ---------- Mutators ---------- */

void darray_push_back(darray* obj, void* data)
{
    _die_if_true(_grow_and_check_oom(obj), "darray_push_back(): realloc failed\n");

    darray_set(obj, obj->count, data);
    ++obj->count;
}

void darray_insert(darray* obj, void* data, size_t index)
{
    _die_if_true(_grow_and_check_oom(obj), "darray_insert(): realloc failed\n");

    memmove(_get_data_ptr(obj, index+1), _get_data_ptr(obj, index), _size_bytes(obj, index));
    darray_set(obj, index, data);
    ++obj->count;
}

void darray_erase(darray* obj, size_t index)
{
    memcpy(_get_data_ptr(obj, index), _get_data_ptr(obj, obj->count-1), obj->type_size);
    --obj->count;
}

void darray_remove(darray* obj, size_t index)
{
    memmove(_get_data_ptr(obj, index), _get_data_ptr(obj, index+1), _size_bytes(obj, (obj->count - index + 1)));
    --obj->count;
}

/* ---------- Capacity ---------- */

void darray_reserve(darray* obj, size_t capacity)
{
    if(obj->capacity >= capacity)
        return;

    _die_if_true(realloc(obj->data, obj->type_size * capacity) == NULL, "darray_shrink(): realloc failed\n");
    
    obj->capacity = capacity;
}

void darray_shrink(darray* obj)
{
    _die_if_true(realloc(obj->data, obj->type_size * obj->count) == NULL, "darray_shrink(): realloc failed\n");

    obj->capacity = obj->count;
}
