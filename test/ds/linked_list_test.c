//
// Created by moamen on 3/14/26.
//

#include "unity.h"
#include "ds/linked_list.h"


void setUp(void) {
}

void tearDown(void) {
}

void test_create_single_item_linked_list(void) {
    linked_list_t *list = linked_list_create(1);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL_INT(1, list->data);
    TEST_ASSERT_NULL(list->next);
}

void test_append_to_empty_linked_list(void) {
    const linked_list_t *list = linked_list_append(NULL, 1);
    TEST_ASSERT_NULL(list);
}

void test_append_to_linked_list(void) {
    linked_list_t *list = linked_list_create(1);
    linked_list_t *new_list = linked_list_append(list, 2);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL_INT(1, list->data);
    TEST_ASSERT_NOT_NULL(list->next);
    TEST_ASSERT_EQUAL_INT(2, list->next->data);
}

void test_delete_from_empty_linked_list(void) {
    const linked_list_t *delete_result = linked_list_delete(NULL, NULL);
    TEST_ASSERT_NULL(delete_result);
}

void test_delete_from_linked_list(void) {
    linked_list_t *node_1 = linked_list_create(1);
    linked_list_t *node_2 = linked_list_append(node_1, 2);
    linked_list_t *delete_result = linked_list_delete(node_1, node_2);
    TEST_ASSERT_NOT_NULL(delete_result);
    TEST_ASSERT_EQUAL_INT(1, delete_result->data);
    TEST_ASSERT_NULL(delete_result->next);
    TEST_ASSERT_NULL(node_1->next);
}


void test_delete_from_single_item_linked_list(void) {
    linked_list_t *node_1 = linked_list_create(1);
    const linked_list_t *delete_result = linked_list_delete(node_1, node_1);
    TEST_ASSERT_NULL(delete_result);
}

void test_find_in_empty_linked_list(void) {
    const linked_list_t *found = linked_list_find(NULL, 1);
    TEST_ASSERT_NULL(found);
}

void test_find_in_linked_list(void) {
    linked_list_t *node_1 = linked_list_create(1);
    linked_list_t *node_2 = linked_list_append(node_1, 2);
    linked_list_t *node_3 = linked_list_append(node_2, 3);

    const linked_list_t *found = linked_list_find(node_1, 2);
    TEST_ASSERT_NOT_NULL(found);
    TEST_ASSERT_EQUAL_INT(2, found->data);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_create_single_item_linked_list);

    RUN_TEST(test_append_to_empty_linked_list);
    RUN_TEST(test_append_to_linked_list);

    RUN_TEST(test_delete_from_empty_linked_list);
    RUN_TEST(test_delete_from_linked_list);

    RUN_TEST(test_find_in_empty_linked_list);
    RUN_TEST(test_find_in_linked_list);
    return UNITY_END();
}
