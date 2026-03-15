#include "stack.h"
#include "unity.h"

void setUp(void)
{
}
void tearDown(void)
{
}

void test_stack_peek(void)
{
    stack_t *s = stack_create(sizeof(int), 10);
    int i = 2;
    stack_push(s, &i);
    i = 4;
    stack_push(s, &i);

    stack_peek(s, &i);
    TEST_ASSERT_EQUAL_INT(4, i);

    stack_destroy(s);
}

void test_stack_not_empty_after_push(void)
{
    stack_t *s = stack_create(sizeof(int), 10);
    int i = 2;
    stack_push(s, &i);

    TEST_ASSERT_EQUAL_INT(0, stack_is_empty(s));

    stack_destroy(s);
}

void test_stack_pop(void)
{
    stack_t *s = stack_create(sizeof(int), 10);
    int i = 2;
    stack_push(s, &i);
    i = 4;
    stack_push(s, &i);

    stack_pop(s);
    stack_peek(s, &i);
    TEST_ASSERT_EQUAL_INT(2, i);

    stack_destroy(s);
}

void test_stack_empty_after_pop_all(void)
{
    stack_t *s = stack_create(sizeof(int), 10);
    int i = 2;
    stack_push(s, &i);
    i = 4;
    stack_push(s, &i);

    stack_pop(s);
    stack_pop(s);
    TEST_ASSERT_EQUAL_INT(1, stack_is_empty(s));

    stack_destroy(s);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_stack_peek);
    RUN_TEST(test_stack_not_empty_after_push);
    RUN_TEST(test_stack_pop);
    RUN_TEST(test_stack_empty_after_pop_all);
    return UNITY_END();
}
