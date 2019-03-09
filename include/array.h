#ifndef ARRAY_H
#define ARRAY_H

#include <stdint.h>

#define array(T, S)\
    struct\
    {\
        size_t       count;\
        const size_t capacity;\
        T            data[S];\
    }

/* ---------- Creational ---------- */

#define array_init(array)\
    do\
    {\
        (array)->count = 0;\
        *(size_t*)&((array)->capacity) = sizeof((array)->data) / sizeof((array)->data[0]);\
    }\
    while(0)

/* ---------- Accessors ---------- */

#define array_get(array, index) ((array)->data[index])

#define array_front(array) ((array)->data[0])

#define array_back(array) ((array)->data[(array)->count-1])

/* --------- Mutators ---------- */

#define array_set(array, index, elem) ((array)->data[(index)] = (elem))

#define array_push(array, elem)\
    do\
    {\
        array_set((array), (array)->count, (elem));\
        ++(array)->count;\
    } while(0)

#define array_pop(array)\
    do\
    {\
        if((array)->count > 0)\
            --(array)->count;\
    } while(0)

#define array_fill(array, elem)\
    do\
    {\
        for(size_t idx = 0; idx < (array)->capacity; ++idx)\
        {\
           array_push((array), (elem));\
        }\
    }\
    while(0)

/* --------- Capacity ---------- */

#define array_empty(array) ((array)->count == 0)

#endif
