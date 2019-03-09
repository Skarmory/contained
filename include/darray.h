#ifndef DARRAY_H
#define DARRAY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

// A dynamic array
typedef struct _darray
{
    size_t count; 
    size_t capacity;
    size_t type_size;
    void*  data;
} darray;

/* ---------- Creational ----------*/

// Initialises a darray
void darray_init(darray* obj, size_t type_size);

// Uninitialises a darray
void darray_uninit(darray* obj);

/* ---------- Accessors ---------- */

// Get the element at the given index
#define darray_get(obj, type, index) ((type)*((uint8_t*)(obj)->data + ((index) * (obj)->type_size)))

// Get the element at the front (index 0)
#define darray_front(obj, type) (darray_get(obj, type,  0))

// Get the element at the back (index count-1)
#define darray_back(obj, type) (darray_get(obj, type, (obj)->count-1))

/* ---------- Mutators ---------- */

// Set the element at the given index
#define darray_set(obj, index, value) (memcpy((uint8_t*)(obj)->data + ((index) * (obj)->type_size), (value), (obj)->type_size))

// Resets the count to 0
#define darray_clear(obj) ((obj)->count = 0)

// Adds an element to the end
void darray_push_back(darray* obj, void* data);

// Remove element from end
#define darray_pop_back(obj)\
    do\
    {\
        if((obj)->count > 0)\
            --(obj)->count;\
    }\
    while(0)


// Adds an element at a given index
void darray_insert(darray* obj, void* data, size_t index);

// Erases an element at a given index, without maintaining element ordering
void darray_erase(darray* obj, size_t index);

// Removes an element at a given index, maintaining element ordering
void darray_remove(darray* obj, size_t index);

/* ---------- Capacity ---------- */

// Return true if count is 0
#define darray_empty(obj) ((obj)->count == 0)

// Pre-allocate enough memory to fit given number of elements in
void darray_reserve(darray* obj, size_t capacity);

// Reallocate memory so the capacity is equal to the element count
void darray_shrink(darray* obj);

#endif
