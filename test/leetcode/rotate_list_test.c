#include "leetcode.h"
#include "unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_rotate_right(void)
{
    struct ListNode n5 = {.val = 5, .next = NULL};
    struct ListNode n4 = {.val = 4, .next = &n5};
    struct ListNode n3 = {.val = 3, .next = &n4};
    struct ListNode n2 = {.val = 2, .next = &n3};
    struct ListNode n1 = {.val = 1, .next = &n2};

    struct ListNode *res = rotateRight(&n1, 2);

    TEST_ASSERT_EQUAL_INT(5, res->val);
    TEST_ASSERT_NOT_NULL(res->next);
    res = res->next;
    TEST_ASSERT_EQUAL_INT(4, res->val);
    TEST_ASSERT_NOT_NULL(res->next);
    res = res->next;
    TEST_ASSERT_EQUAL_INT(1, res->val);
    TEST_ASSERT_NOT_NULL(res->next);
    res = res->next;
    TEST_ASSERT_EQUAL_INT(2, res->val);
    TEST_ASSERT_NOT_NULL(res->next);
    res = res->next;
    TEST_ASSERT_EQUAL_INT(3, res->val);
}

int main(void)
{
    UNITY_BEGIN();
    // RUN_TEST(test_rotate_right);
    return UNITY_END();
}
