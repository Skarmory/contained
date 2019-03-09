#ifndef ALGO_H
#define ALGO_H

#include <stddef.h>
#include <stdbool.h>

void quicksort(void* data, size_t type_size, size_t count, bool(*compare)(const void*, const void*));

#endif
