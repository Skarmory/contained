#include "rbt.h"

#include <stdio.h>
#include <string.h>

#define RED true
#define BLACK false

#define _parent(node)      ((node)->parent)
#define _grandparent(node) (_parent((node)) ? (node)->parent->parent : NULL)
#define _uncle(node)       (_grandparent((node)) ? (_grandparent((node))->left != _parent((node)) ? _grandparent((node))->left : _grandparent((node))->right) : NULL)

/*
 * Holds data for printing an rbnode
 */
typedef struct _rb_print_node
{
    rb_node* node;
    size_t   level;
    size_t   padding;
} rb_print_node;

static void   _rb_tree_rotate_left  (rb_node* node);
static void   _rb_tree_rotate_right (rb_node* node);
static void   _rb_tree_repair       (rb_node* node);
static void   _rb_tree_insert       (rb_node* root, rb_node* new, comp_func comp);
static void   _rb_tree_free         (rb_node* node);
static size_t _rb_tree_subtree_size (rb_node* n);

static inline void _rb_node__init(rb_node* node, void* value, size_t type_size)
{
    *node = (rb_node) { 0 };
    node->colour = RED;
    node->value  = malloc(type_size);
    memcpy(node->value, value, type_size);
}

/* ---------- Functions ---------- */

void rb_tree_init(rb_tree* tree, size_t type_size, comp_func comp)
{
    tree->root      = NULL;
    tree->count     = 0;
    tree->type_size = type_size;
    tree->func      = comp;
}

static void _rb_tree_free(rb_node* node)
{
    if(node->left)  _rb_tree_free(node->left);
    if(node->right) _rb_tree_free(node->right);

    free(node->value);
    free(node);
}

void rb_tree_uninit(rb_tree* tree)
{
    if(tree->root)
        _rb_tree_free(tree->root);
}

static rb_node* _rb_tree_find(rb_node* node, void* value, comp_func func)
{
    if(!node) return NULL;

    int res = func(value, node->value);
    if(res < 0)
    {
        return _rb_tree_find(node->left, value, func);
    }
    else if(res > 0)
    {
        return _rb_tree_find(node->right, value, func);
    }

    return node;
}

void* rb_tree_find(rb_tree* tree, void* value)
{
    rb_node* found = _rb_tree_find(tree->root, value, tree->func);

    return found ? found->value : NULL;
}

static void _rb_tree_rotate_left(rb_node* node)
{
    /*
     * Perform a left rotation. Switches around the left subtree of given node's right child node with the given node.
     * e.g. After 5 is added, left rotation is required for balance:
     *
     *          2                               2
     *      1       3           ==>     1               4
     *                  4                           3       5
     *                      5
     */

    rb_node* new = node->right;
    rb_node* parent = _parent(node);

    node->right = new->left;
    new->left = node;
    node->parent = new;

    if(node->right)
    {
        node->right->parent = node;
    }

    if(parent)
    {
        if(node == parent->left)
            parent->left = new;
        else
            parent->right = new;
    }

    new->parent = parent;
}

static void _rb_tree_rotate_right(rb_node* node)
{
    /*
     * Perform a right rotation. Switches around the right subtree of given node's left child node with the given node. 
     * e.g. After 4 is added, a right rotation is required for balance:
     *
     *                  7                           7
     *              6       8   ==>         5               8
     *          5                       4       6
     *      4
     */

    rb_node* new = node->left;
    rb_node* parent = _parent(node);

    node->left = new->right;
    new->right = node;
    node->parent = new;

    if(node->left)
    {
        node->left->parent = node;
    }

    if(parent)
    {
        if(node == parent->left)
            parent->left = new;
        else
            parent->right = new;
    }

    new->parent = parent;
}

static void _rb_tree_repair(rb_node* node)
{
    if(!node->parent)
    {
        node->colour = BLACK;
        return;
    }

    if(node->parent->colour == BLACK)
    {
        return;
    }

    if(_uncle(node) && _uncle(node)->colour == RED)
    {
        _parent(node)->colour      = BLACK;
        _uncle(node)->colour       = BLACK;
        _grandparent(node)->colour = RED;

        _rb_tree_repair(_grandparent(node));
        return;
    }

    rb_node* p = _parent(node);
    rb_node* g = _grandparent(node);

    if(node == p->right && p == g->left)
    {
        _rb_tree_rotate_left(p);
        node = node->left;
    }
    else if(node == p->left && p == g->right)
    {
        _rb_tree_rotate_right(p);
        node = node->right;
    }

    if(node == p->left)
    {
        _rb_tree_rotate_right(g);
    }
    else if(node == p->right)
    {
        _rb_tree_rotate_left(g);
    }

    if(g) g->colour = RED;
    p->colour = BLACK;
}

static void _rb_tree_insert(rb_node* node, rb_node* new, comp_func comp)
{
    if(!node) goto set_parent_lbl;

    if(comp(new->value, node->value) < 0)
    {
        // Value of new is < node
        if(node->left)
        {
            _rb_tree_insert(node->left, new, comp);
            return;
        }

        node->left = new;
    }
    else
    {
        // Value of new >= node
        if(node->right)
        {
            _rb_tree_insert(node->right, new, comp);
            return;
        }

        node->right = new;
    }

set_parent_lbl:;
    new->parent = node;
}

void rb_tree_insert(rb_tree* tree, void* value)
{
    rb_node* new = (rb_node*) malloc(sizeof(rb_node));
    _rb_node__init(new, value, tree->type_size);

    _rb_tree_insert(tree->root, new, tree->func);
    _rb_tree_repair(new);

    ++tree->count;

    tree->root = new;
    while(_parent(tree->root))
    {
        tree->root = _parent(tree->root);
    }
}

/*
static rb_node* _rb_tree_find_largest(rb_node* node)
{
    if(!node->left && !node->right)
        return node;

    return _rb_tree_find_largest(node->right);
}
*/

/*
void _rb_tree_remove_repair(rb_node* node)
{
}
*/

/*
void rb_tree_remove(rb_tree* tree, void* value)
{
    rb_node* found = _rb_tree_find(tree->root, value, tree->func);

    if(!found) return;


}
*/

static size_t _rb_tree_subtree_size(rb_node* n)
{
    if(!n) return 0;

    return (1 + _rb_tree_subtree_size(n->left) + _rb_tree_subtree_size(n->right));
}

void rb_tree_print(rb_tree* tree)
{
    size_t queue_end = 0;
    size_t queue_current = 0;
    rb_print_node queue[64];

    size_t level;
    size_t parent_padding;
    rb_node* tmp;
    queue[queue_end++] = (rb_print_node){ .node = tree->root, .level = 0, .padding = _rb_tree_subtree_size(tree->root->left) + 1 };

    // Enqueue all nodes
    do
    {
        level          = queue[queue_current].level;
        tmp            = queue[queue_current].node;
        parent_padding = queue[queue_current].padding;

        if(tmp->left)
            queue[queue_end++] = (rb_print_node){ .node = tmp->left,  .level = level+1, .padding = (parent_padding - _rb_tree_subtree_size(tmp->left->right)) - 1 };

        if(tmp->right)
            queue[queue_end++] = (rb_print_node){ .node = tmp->right, .level = level+1, .padding = (parent_padding + _rb_tree_subtree_size(tmp->right->left)) + 1 };

        queue_current++;
    }
    while(queue_current < queue_end);

    queue_current = 0;
    level = queue[queue_current].level;
    size_t prev_padding = 0;
    while(queue_current < queue_end)
    {
        if(level != queue[queue_current].level)
        {
            prev_padding = 0;
            printf("\n");
        }

        level = queue[queue_current].level;

        for(size_t i = 0; i < (queue[queue_current].padding - prev_padding - 1); ++i)
            printf(" ");
        printf("%c", *(queue[queue_current].node->colour ? "R" : "B"));

        prev_padding = queue[queue_current].padding;

        ++queue_current;
    }
}
