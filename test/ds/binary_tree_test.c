#include "data_structures.h"
#include "unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_create_empty_binary_tree(void)
{
    binary_tree_t *tree = binary_tree_create(1);
    TEST_ASSERT_NOT_NULL(tree);
    binary_tree_destroy(tree);
}

void test_search_single_item_binary_tree(void)
{
    binary_tree_t *tree = binary_tree_create(1);
    TEST_ASSERT_NOT_NULL(tree);
    binary_tree_t *result = binary_tree_search(tree, 1);
    binary_tree_destroy(tree);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_create_empty_binary_tree);

    return UNITY_END();
}
