#ifndef RBT_H
#define RBT_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef int(*comp_func)(const void*, const void*);

typedef struct _rb_node
{
    struct _rb_node* parent;
    struct _rb_node* left;
    struct _rb_node* right;
    void*            value;
    bool             colour;
} rb_node; 

typedef struct _rb_tree
{
    rb_node*  root;
    size_t    count;
    size_t    type_size;
    comp_func func;
} rb_tree;

/*
 * Create a new rb_tree
 */
void rb_tree_init(rb_tree* tree, size_t type_size, comp_func comp);

/*
 * Delete an rb_tree
 */
void rb_tree_uninit(rb_tree* tree);

/*
 * Find a value in the tree
 */
void* rb_tree_find(rb_tree*, void* value);

/*
 * Insert a value into the tree
 */
void rb_tree_insert(rb_tree* tree, void* value);

/*
 * Removes a value from the tree
 */
//void rb_tree_remove(rb_tree* tree, void* value);

/*
 * Print an ascii representation of the tree to terminal
 */
void rb_tree_print(rb_tree* tree);

#endif
