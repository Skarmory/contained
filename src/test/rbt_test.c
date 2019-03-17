#include "test/rbt_test.h"

#include <stdio.h>

#include "rbt.h"
#include "test/testing.h"

const bool red   = true;
const bool black = false;

// Compare value of two ints. Return true if l < r.
int compare_int(const void* l, const void* r)
{
    int lv = *(int*)l;
    int rv = *(int*)r;

    if(lv < rv)
        return -1;
    else if(lv == rv)
        return 0;
    else
        return 1;
}

void rbt_test_insert(void)
{
    printf("Test case: rbt_test_insert\n");
    {
        rb_tree tree;
        rb_tree_init(&tree, sizeof(int), &compare_int);

        int* nums;
        TEST_CONTEXT((nums = (int[]) { 8, 7, 6, 5, 4, 3, 2, 1 }));

        TEST_CONTEXT(
            for(int i = 0; i < 8; ++i)
            {
                rb_tree_insert(&tree, &nums[i]);
            }
        );

        TEST_EQ(*(int*)tree.root->value, 5);
        TEST_EQ(tree.root->colour, black);
        TEST_EQ(*(int*)tree.root->left->value,  3);
        TEST_EQ(*(int*)tree.root->right->value, 7);
        TEST_EQ(tree.count, 8);

        rb_tree_uninit(&tree);
    }
    printf("\n");
}

void rbt_test_run_all(void)
{
    rbt_test_insert();
}
