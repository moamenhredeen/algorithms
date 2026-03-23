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
    TEST_ASSERT_EQUAL(1, get_item(result));
    binary_tree_destroy(tree);
}

void test_find_minimum_in_single_item_binary_tree(void)
{
    binary_tree_t *tree = binary_tree_create(1);
    TEST_ASSERT_NOT_NULL(tree);
    binary_tree_t *result = binary_tree_find_minimum(tree);
    TEST_ASSERT_EQUAL(1, get_item(result));
    binary_tree_destroy(tree);
}

void test_find_maximum_in_single_item_binary_tree(void)
{
    binary_tree_t *tree = binary_tree_create(1);
    TEST_ASSERT_NOT_NULL(tree);
    binary_tree_t *result = binary_tree_find_maximum(tree);
    TEST_ASSERT_EQUAL(1, get_item(result));
    binary_tree_destroy(tree);
}

typedef struct {
    int items[64];
    int count;
} visit_log_t;

static void collect_item(binary_tree_t *node, void *user_data)
{
    visit_log_t *log = (visit_log_t *)user_data;
    log->items[log->count++] = get_item(node);
}

void test_traverse_single_item_binary_tree(void)
{
    visit_log_t log = {.count = 0};
    binary_tree_t *tree = binary_tree_create(1);
    TEST_ASSERT_NOT_NULL(tree);
    binary_tree_traverse(tree, collect_item, &log);
    TEST_ASSERT_EQUAL(1, log.count);
    TEST_ASSERT_EQUAL(1, log.items[0]);
    binary_tree_destroy(tree);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_create_empty_binary_tree);
    RUN_TEST(test_search_single_item_binary_tree);
    RUN_TEST(test_find_minimum_in_single_item_binary_tree);
    RUN_TEST(test_find_maximum_in_single_item_binary_tree);
    RUN_TEST(test_traverse_single_item_binary_tree);

    return UNITY_END();
}
