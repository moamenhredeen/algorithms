#include "ds/linked_stack.h"
#include "unity.h"

void setUp(void)
{
}
void tearDown(void)
{
}

void test_stack_create(void)
{
    linked_stack_t *s = linked_stack_create();
    TEST_ASSERT_NOT_NULL(s);
    TEST_ASSERT_NULL(s->head);
    TEST_ASSERT_EQUAL_INT(0, s->size);
    linked_stack_destroy(s);
}

void test_stack_push_single(void)
{
    linked_stack_t *s = linked_stack_create();
    linked_stack_push(s, 42);
    TEST_ASSERT_EQUAL_INT(1, s->size);
    linked_stack_destroy(s);
}

void test_stack_push_multiple(void)
{
    linked_stack_t *s = linked_stack_create();
    linked_stack_push(s, 1);
    linked_stack_push(s, 2);
    linked_stack_push(s, 3);
    TEST_ASSERT_EQUAL_INT(3, s->size);
    linked_stack_destroy(s);
}

void test_stack_peek_returns_top(void)
{
    linked_stack_t *s = linked_stack_create();
    linked_stack_push(s, 10);
    linked_stack_push(s, 20);
    TEST_ASSERT_EQUAL_INT(20, linked_stack_peek(s));
    linked_stack_destroy(s);
}

void test_stack_peek_does_not_remove(void)
{
    linked_stack_t *s = linked_stack_create();
    linked_stack_push(s, 5);
    linked_stack_peek(s);
    TEST_ASSERT_EQUAL_INT(1, s->size);
    linked_stack_destroy(s);
}

void test_stack_pop_returns_top(void)
{
    linked_stack_t *s = linked_stack_create();
    linked_stack_push(s, 10);
    linked_stack_push(s, 20);
    TEST_ASSERT_EQUAL_INT(20, linked_stack_pop(s));
    linked_stack_destroy(s);
}

void test_stack_pop_removes_element(void)
{
    linked_stack_t *s = linked_stack_create();
    linked_stack_push(s, 10);
    linked_stack_push(s, 20);
    linked_stack_pop(s);
    TEST_ASSERT_EQUAL_INT(1, s->size);
    linked_stack_destroy(s);
}

void test_stack_pop_all_empties_stack(void)
{
    linked_stack_t *s = linked_stack_create();
    linked_stack_push(s, 1);
    linked_stack_push(s, 2);
    linked_stack_pop(s);
    linked_stack_pop(s);
    TEST_ASSERT_EQUAL_INT(0, s->size);
    TEST_ASSERT_NULL(s->head);
    linked_stack_destroy(s);
}

void test_stack_lifo_order(void)
{
    linked_stack_t *s = linked_stack_create();
    linked_stack_push(s, 1);
    linked_stack_push(s, 2);
    linked_stack_push(s, 3);
    TEST_ASSERT_EQUAL_INT(3, linked_stack_pop(s));
    TEST_ASSERT_EQUAL_INT(2, linked_stack_pop(s));
    TEST_ASSERT_EQUAL_INT(1, linked_stack_pop(s));
    linked_stack_destroy(s);
}

void test_stack_push_after_pop(void)
{
    linked_stack_t *s = linked_stack_create();
    linked_stack_push(s, 1);
    linked_stack_push(s, 2);
    linked_stack_pop(s);
    linked_stack_push(s, 3);
    TEST_ASSERT_EQUAL_INT(2, s->size);
    TEST_ASSERT_EQUAL_INT(3, linked_stack_peek(s));
    linked_stack_destroy(s);
}

void test_stack_push_negative_values(void)
{
    linked_stack_t *s = linked_stack_create();
    linked_stack_push(s, -1);
    linked_stack_push(s, -100);
    TEST_ASSERT_EQUAL_INT(-100, linked_stack_peek(s));
    TEST_ASSERT_EQUAL_INT(-100, linked_stack_pop(s));
    TEST_ASSERT_EQUAL_INT(-1, linked_stack_pop(s));
    linked_stack_destroy(s);
}

void test_stack_push_zero(void)
{
    linked_stack_t *s = linked_stack_create();
    linked_stack_push(s, 0);
    TEST_ASSERT_EQUAL_INT(0, linked_stack_peek(s));
    TEST_ASSERT_EQUAL_INT(1, s->size);
    linked_stack_destroy(s);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_stack_create);
    RUN_TEST(test_stack_push_single);
    RUN_TEST(test_stack_push_multiple);
    RUN_TEST(test_stack_peek_returns_top);
    RUN_TEST(test_stack_peek_does_not_remove);
    RUN_TEST(test_stack_pop_returns_top);
    RUN_TEST(test_stack_pop_removes_element);
    RUN_TEST(test_stack_pop_all_empties_stack);
    RUN_TEST(test_stack_lifo_order);
    RUN_TEST(test_stack_push_after_pop);
    RUN_TEST(test_stack_push_negative_values);
    RUN_TEST(test_stack_push_zero);
    return UNITY_END();
}
