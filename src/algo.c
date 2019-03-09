#include "algo.h"

#include <stdint.h>
#include <stdio.h>

#define _stack_make\
    struct _stack_elem stack[64];\
    size_t stack_top = 0

#define _stack_push(c, p)\
    do\
    {\
        stack[stack_top].current = c;\
        stack[stack_top].pivot = p;\
        ++stack_top;\
    }\
    while(0)

#define _stack_empty\
    (stack_top == 0)

#define _stack_top\
    stack[stack_top-1]

#define _stack_pop\
    (--stack_top)

#define swap(a, b, size)\
    do\
    {\
        size_t _size = (size);\
        uint8_t* _a = (a);\
        uint8_t* _b = (b);\
        do\
        {\
            uint8_t tmp = *_a;\
            *_a++ = *_b;\
            *_b++ = tmp;\
        }\
        while(--_size > 0);\
    }\
    while(0)

struct _stack_elem
{
    size_t current;
    size_t pivot;
};

void quicksort(void* data, size_t type_size, size_t count, bool(*compare)(const void*, const void*))
{
    if(count < 2)
        return;

    _stack_make;
    _stack_push(0, (count-1));

    struct _stack_elem e;

    while(!_stack_empty)
    {
        e = _stack_top;
        _stack_pop;

        if((e.pivot - e.current) == 1)
        {
            if(compare(((uint8_t*)data) + (e.current * type_size), ((uint8_t*)data) + (e.pivot * type_size)))
            {
                swap(((uint8_t*)data) + (e.current * type_size), ((uint8_t*)data) + (e.pivot * type_size), type_size);
            }

            continue;
        }

        size_t sta = e.current;
        size_t end = e.pivot;

        // Do work on current elem range
        while(e.current != e.pivot)
        {
            if(compare(((uint8_t*)data) + (e.current * type_size), ((uint8_t*)data) + (e.pivot * type_size)))
            {
                swap(((uint8_t*)data) + ((e.pivot - 1) * type_size), ((uint8_t*)data) + (e.pivot * type_size), type_size);
                swap(((uint8_t*)data) + (e.current * type_size), ((uint8_t*)data) + (e.pivot * type_size), type_size);
                --(e.pivot);
            }
            else
            {
                ++(e.current);
            }
        }

        // Push new ranges
        if((e.pivot - sta) > 1)
        {
            _stack_push(sta, e.pivot-1);
        }

        if((end - e.pivot) > 1)
        {
            _stack_push(e.pivot+1, end);
        }
    }
}
