#include "unity.h"
#include <stdbool.h>
#include <stdlib.h>

#include "leetcode.h"

static struct ListNode *fill(const int *arr, int size)
{
    struct ListNode *start = malloc(sizeof(struct ListNode));
    struct ListNode *curr = start;
    for (int i = 0; i < size; i++) {
        curr->val = arr[i];
        if (i < size - 1) {
            curr->next = malloc(sizeof(struct ListNode));
            curr = curr->next;
        } else {
            curr->next = NULL;
        }
    }
    return start;
}

static void free_list(struct ListNode *list)
{
    while (list) {
        struct ListNode *tmp = list;
        list = list->next;
        free(tmp);
    }
}

static bool match(struct ListNode *list, const int *arr, int size)
{
    for (int i = 0; i < size; i++) {
        if (list->val != arr[i])
            return false;
        list = list->next;
    }
    return true;
}

void setUp(void)
{
}
void tearDown(void)
{
}

void test_add_two_numbers_equal_length(void)
{
    struct ListNode *l1 = fill((int[]){7, 8, 9}, 3);
    struct ListNode *l2 = fill((int[]){7, 8, 9}, 3);
    struct ListNode *res = addTwoNumbers(l1, l2);
    TEST_ASSERT_TRUE(match(res, (int[]){4, 7, 9, 1}, 4));
    free_list(l1);
    free_list(l2);
    free_list(res);
}

void test_add_two_numbers_basic(void)
{
    struct ListNode *l1 = fill((int[]){2, 4, 3}, 3);
    struct ListNode *l2 = fill((int[]){5, 6, 4}, 3);
    struct ListNode *res = addTwoNumbers(l1, l2);
    TEST_ASSERT_TRUE(match(res, (int[]){7, 0, 8}, 3));
    free_list(l1);
    free_list(l2);
    free_list(res);
}

void test_add_two_numbers_different_length(void)
{
    struct ListNode *l1 = fill((int[]){9, 9, 9, 9, 9, 9, 9}, 7);
    struct ListNode *l2 = fill((int[]){9, 9, 9, 9}, 4);
    struct ListNode *res = addTwoNumbers(l1, l2);
    TEST_ASSERT_TRUE(match(res, (int[]){8, 9, 9, 9, 0, 0, 0, 1}, 8));
    free_list(l1);
    free_list(l2);
    free_list(res);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_add_two_numbers_equal_length);
    RUN_TEST(test_add_two_numbers_basic);
    RUN_TEST(test_add_two_numbers_different_length);
    return UNITY_END();
}
