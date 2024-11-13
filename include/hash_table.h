#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>

struct _hashtable;
typedef struct _hashtable hashtable;

/* ----- Creational ----- */

// Initialises a hashtable
void hashtable_init(hashtable* table, size_t type_size);

// Uninitialises a hashtable
void hashtable_uninit(hashtable* table);

/* ----- Accessors ----- */

void* hashtable_get(hashtable* table, void* key);

/* ----- Mutators ----- */

void hashtable_insert(hashtable* table, void* key, void* data);

#endif
