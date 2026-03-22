#include "data_structures.h"
#include "unity.h"
#include "unity_internals.h"
#include <stdlib.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_create_empty_queue(void)
{
    linked_queue_t *queue = linked_queue_create();
    TEST_ASSERT_NOT_NULL(queue);
    free(queue);
}

void test_destroy_queue(void)
{
    linked_queue_t *queue = linked_queue_create();
    TEST_ASSERT_NOT_NULL(queue);
    linked_queue_destroy(queue);
}

void test_push_item_to_queue(void)
{
    linked_queue_t *queue = linked_queue_create();
    linked_queue_push(queue, 1);
    TEST_ASSERT_NOT_NULL(queue);
    TEST_ASSERT_EQUAL(1, queue->size);
    TEST_ASSERT_NOT_NULL(queue->head);
    TEST_ASSERT_EQUAL(1, queue->head->data);
    linked_queue_destroy(queue);
}

void test_push_multiple_item_to_queue(void)
{
    linked_queue_t *queue = linked_queue_create();
    linked_queue_push(queue, 1);
    linked_queue_push(queue, 2);
    linked_queue_push(queue, 3);

    TEST_ASSERT_NOT_NULL(queue);
    TEST_ASSERT_EQUAL(3, queue->size);

    TEST_ASSERT_NOT_NULL(queue->head);
    TEST_ASSERT_EQUAL(3, queue->head->data);

    TEST_ASSERT_NOT_NULL(queue->head->next);
    TEST_ASSERT_EQUAL(2, queue->head->next->data);

    TEST_ASSERT_NOT_NULL(queue->head->next->next);
    TEST_ASSERT_EQUAL(1, queue->head->next->next->data);

    linked_queue_destroy(queue);
}

void test_peek_returns_front(void)
{
    linked_queue_t *queue = linked_queue_create();
    linked_queue_push(queue, 10);
    linked_queue_push(queue, 20);
    TEST_ASSERT_EQUAL_INT(10, linked_queue_peek(queue));
    linked_queue_destroy(queue);
}

void test_peek_empty_queue(void)
{
    linked_queue_t *queue = linked_queue_create();
    TEST_ASSERT_EQUAL_INT(0, linked_queue_peek(0));
    linked_queue_destroy(queue);
}

void test_peek_does_not_remove(void)
{
    linked_queue_t *queue = linked_queue_create();
    linked_queue_push(queue, 5);
    linked_queue_peek(queue);
    TEST_ASSERT_EQUAL(1, queue->size);
    linked_queue_destroy(queue);
}

void test_pop_returns_front(void)
{
    linked_queue_t *queue = linked_queue_create();
    linked_queue_push(queue, 10);
    linked_queue_push(queue, 20);
    TEST_ASSERT_EQUAL_INT(10, linked_queue_pop(queue));
    linked_queue_destroy(queue);
}

void test_pop_removes_element(void)
{
    linked_queue_t *queue = linked_queue_create();
    linked_queue_push(queue, 10);
    linked_queue_push(queue, 20);
    linked_queue_pop(queue);
    TEST_ASSERT_EQUAL(1, queue->size);
    linked_queue_destroy(queue);
}

void test_pop_all_empties_queue(void)
{
    linked_queue_t *queue = linked_queue_create();
    linked_queue_push(queue, 1);
    linked_queue_push(queue, 2);
    linked_queue_pop(queue);
    linked_queue_pop(queue);
    TEST_ASSERT_EQUAL(0, queue->size);
    TEST_ASSERT_NULL(queue->head);
    linked_queue_destroy(queue);
}

void test_fifo_order(void)
{
    linked_queue_t *queue = linked_queue_create();
    linked_queue_push(queue, 1);
    linked_queue_push(queue, 2);
    linked_queue_push(queue, 3);
    TEST_ASSERT_EQUAL_INT(1, linked_queue_pop(queue));
    TEST_ASSERT_EQUAL_INT(2, linked_queue_pop(queue));
    TEST_ASSERT_EQUAL_INT(3, linked_queue_pop(queue));
    linked_queue_destroy(queue);
}

void test_push_after_pop(void)
{
    linked_queue_t *queue = linked_queue_create();
    linked_queue_push(queue, 1);
    linked_queue_push(queue, 2);
    linked_queue_pop(queue);
    linked_queue_push(queue, 3);
    TEST_ASSERT_EQUAL(2, queue->size);
    TEST_ASSERT_EQUAL_INT(2, linked_queue_peek(queue));
    linked_queue_destroy(queue);
}

void test_push_negative_values(void)
{
    linked_queue_t *queue = linked_queue_create();
    linked_queue_push(queue, -1);
    linked_queue_push(queue, -100);
    TEST_ASSERT_EQUAL_INT(-1, linked_queue_peek(queue));
    TEST_ASSERT_EQUAL_INT(-1, linked_queue_pop(queue));
    TEST_ASSERT_EQUAL_INT(-100, linked_queue_pop(queue));
    linked_queue_destroy(queue);
}

void test_push_zero(void)
{
    linked_queue_t *queue = linked_queue_create();
    linked_queue_push(queue, 0);
    TEST_ASSERT_EQUAL_INT(0, linked_queue_peek(queue));
    TEST_ASSERT_EQUAL(1, queue->size);
    linked_queue_destroy(queue);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_create_empty_queue);
    RUN_TEST(test_destroy_queue);
    RUN_TEST(test_push_item_to_queue);
    RUN_TEST(test_push_multiple_item_to_queue);
    RUN_TEST(test_peek_returns_front);
    RUN_TEST(test_peek_empty_queue);
    RUN_TEST(test_peek_does_not_remove);
    RUN_TEST(test_pop_returns_front);
    RUN_TEST(test_pop_removes_element);
    RUN_TEST(test_pop_all_empties_queue);
    RUN_TEST(test_fifo_order);
    RUN_TEST(test_push_after_pop);
    RUN_TEST(test_push_negative_values);
    RUN_TEST(test_push_zero);
    return UNITY_END();
}
