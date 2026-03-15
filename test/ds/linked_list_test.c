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


void test_append_multiple_nodes_in_sequence(void) {
    linked_list_t *list = linked_list_create(1);

    // Append multiple nodes
    for (int i = 2; i <= 5; i++) {
        linked_list_t *new_node = linked_list_append(list, i);
        TEST_ASSERT_NOT_NULL(new_node);
    }

    // Verify the entire list structure
    linked_list_t *current = list;
    for (int i = 1; i <= 5; i++) {
        TEST_ASSERT_NOT_NULL(current);
        TEST_ASSERT_EQUAL_INT(i, current->data);
        current = current->next;
    }
    TEST_ASSERT_NULL(current);
}

void test_append_returns_new_node(void) {
    linked_list_t *list = linked_list_create(1);
    linked_list_t *new_node = linked_list_append(list, 2);

    // Verify append returns the new node, not the head
    TEST_ASSERT_NOT_NULL(new_node);
    TEST_ASSERT_EQUAL_INT(2, new_node->data);
    TEST_ASSERT_NULL(new_node->next);
    TEST_ASSERT_NOT_EQUAL(list, new_node);
}

void test_append_large_number_of_nodes(void) {
    linked_list_t *list = linked_list_create(0);

    // Append a large number of nodes
    for (int i = 1; i <= 100; i++) {
        linked_list_t *new_node = linked_list_append(list, i);
        TEST_ASSERT_NOT_NULL(new_node);
        TEST_ASSERT_EQUAL_INT(i, new_node->data);
    }

    // Verify list integrity by counting nodes
    int count = 0;
    linked_list_t *current = list;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    TEST_ASSERT_EQUAL_INT(101, count);
}

void test_append_maintains_list_integrity(void) {
    linked_list_t *list = linked_list_create(10);
    linked_list_t *second = linked_list_append(list, 20);
    linked_list_t *third = linked_list_append(list, 30);

    // Verify all nodes are properly linked
    TEST_ASSERT_EQUAL_PTR(second, list->next);
    TEST_ASSERT_EQUAL_PTR(third, list->next->next);
    TEST_ASSERT_EQUAL_PTR(third, second->next);
    TEST_ASSERT_NULL(third->next);
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

void test_delete_head_node_from_list(void) {
    linked_list_t *node_1 = linked_list_create(1);
    linked_list_append(node_1, 2);
    linked_list_append(node_1, 3);

    linked_list_t *new_head = linked_list_delete(node_1, node_1);
    TEST_ASSERT_NOT_NULL(new_head);
    TEST_ASSERT_EQUAL_INT(2, new_head->data);
    TEST_ASSERT_NOT_NULL(new_head->next);
    TEST_ASSERT_EQUAL_INT(3, new_head->next->data);
}

void test_delete_middle_node_from_list(void) {
    linked_list_t *node_1 = linked_list_create(1);
    linked_list_t *node_2 = linked_list_append(node_1, 2);
    linked_list_t *node_3 = linked_list_append(node_1, 3);

    linked_list_t *result = linked_list_delete(node_1, node_2);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(1, result->data);
    TEST_ASSERT_NOT_NULL(result->next);
    TEST_ASSERT_EQUAL_INT(3, result->next->data);
    TEST_ASSERT_NULL(result->next->next);
}

void test_delete_non_existent_node(void) {
    linked_list_t *node_1 = linked_list_create(1);
    linked_list_append(node_1, 2);

    // Create a node that's not in the list
    linked_list_t *orphan_node = linked_list_create(99);

    linked_list_t *result = linked_list_delete(node_1, orphan_node);
    // Should return the original list unchanged
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(1, result->data);
    TEST_ASSERT_NOT_NULL(result->next);
    TEST_ASSERT_EQUAL_INT(2, result->next->data);

    linked_list_destroy(orphan_node);
}

void test_delete_last_node_from_long_list(void) {
    linked_list_t *node_1 = linked_list_create(1);
    linked_list_append(node_1, 2);
    linked_list_append(node_1, 3);
    linked_list_t *node_4 = linked_list_append(node_1, 4);

    linked_list_t *result = linked_list_delete(node_1, node_4);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(1, result->data);

    // Traverse to verify list integrity
    linked_list_t *current = result;
    int expected_values[] = {1, 2, 3};
    for (int i = 0; i < 3; i++) {
        TEST_ASSERT_NOT_NULL(current);
        TEST_ASSERT_EQUAL_INT(expected_values[i], current->data);
        current = current->next;
    }
    TEST_ASSERT_NULL(current);
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

void test_find_non_existent_element(void) {
    linked_list_t *list = linked_list_create(1);
    linked_list_append(list, 2);
    linked_list_append(list, 3);

    const linked_list_t *found = linked_list_find(list, 99);
    TEST_ASSERT_NULL(found);
}

void test_find_first_element(void) {
    linked_list_t *list = linked_list_create(10);
    linked_list_append(list, 20);
    linked_list_append(list, 30);

    const linked_list_t *found = linked_list_find(list, 10);
    TEST_ASSERT_NOT_NULL(found);
    TEST_ASSERT_EQUAL_INT(10, found->data);
    TEST_ASSERT_EQUAL_PTR(list, found);
}

void test_find_last_element_in_long_list(void) {
    linked_list_t *list = linked_list_create(1);
    for (int i = 2; i <= 10; i++) {
        linked_list_append(list, i);
    }

    const linked_list_t *found = linked_list_find(list, 10);
    TEST_ASSERT_NOT_NULL(found);
    TEST_ASSERT_EQUAL_INT(10, found->data);
    TEST_ASSERT_NULL(found->next);
}

void test_find_middle_element(void) {
    linked_list_t *list = linked_list_create(5);
    linked_list_append(list, 10);
    linked_list_append(list, 15);
    linked_list_append(list, 20);
    linked_list_append(list, 25);

    const linked_list_t *found = linked_list_find(list, 15);
    TEST_ASSERT_NOT_NULL(found);
    TEST_ASSERT_EQUAL_INT(15, found->data);
    TEST_ASSERT_NOT_NULL(found->next);
    TEST_ASSERT_EQUAL_INT(20, found->next->data);
}


void test_destroy_empty_linked_list(void) {
    linked_list_destroy(NULL);
}

void test_destroy_single_node_linked_list(void) {
    linked_list_t *list = linked_list_create(1);
    TEST_ASSERT_NOT_NULL(list);
    linked_list_destroy(list);
}

void test_destroy_multi_node_linked_list(void) {
    linked_list_t *list = linked_list_create(1);
    linked_list_append(list, 2);
    linked_list_append(list, 3);
    linked_list_append(list, 4);
    linked_list_destroy(list);
}

int main(void) {
    UNITY_BEGIN();

    // Create tests
    RUN_TEST(test_create_single_item_linked_list);

    // Append tests
    RUN_TEST(test_append_to_empty_linked_list);
    RUN_TEST(test_append_to_linked_list);
    RUN_TEST(test_append_multiple_nodes_in_sequence);
    RUN_TEST(test_append_returns_new_node);
    RUN_TEST(test_append_large_number_of_nodes);
    RUN_TEST(test_append_maintains_list_integrity);

    // Delete tests
    RUN_TEST(test_delete_from_empty_linked_list);
    RUN_TEST(test_delete_from_linked_list);
    RUN_TEST(test_delete_from_single_item_linked_list);
    RUN_TEST(test_delete_head_node_from_list);
    RUN_TEST(test_delete_middle_node_from_list);
    RUN_TEST(test_delete_non_existent_node);
    RUN_TEST(test_delete_last_node_from_long_list);

    // Find tests
    RUN_TEST(test_find_in_empty_linked_list);
    RUN_TEST(test_find_in_linked_list);
    RUN_TEST(test_find_non_existent_element);
    RUN_TEST(test_find_first_element);
    RUN_TEST(test_find_last_element_in_long_list);
    RUN_TEST(test_find_middle_element);

    // Memory management tests
    RUN_TEST(test_destroy_empty_linked_list);
    RUN_TEST(test_destroy_single_node_linked_list);
    RUN_TEST(test_destroy_multi_node_linked_list);

    return UNITY_END();
}
