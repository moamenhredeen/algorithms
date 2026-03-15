#include "algorithms.h"
#include "unity.h"

void setUp(void)
{
}
void tearDown(void)
{
}

void test_insertion_sort_basic(void)
{
    int arr[] = {5, 2, 8, 1, 9};
    int expected[] = {1, 2, 5, 8, 9};
    insertion_sort(arr, 5);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 5);
}

void test_insertion_sort_already_sorted(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    insertion_sort(arr, 5);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 5);
}

void test_insertion_sort_single_element(void)
{
    int arr[] = {42};
    int expected[] = {42};
    insertion_sort(arr, 1);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 1);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_insertion_sort_basic);
    RUN_TEST(test_insertion_sort_already_sorted);
    RUN_TEST(test_insertion_sort_single_element);
    return UNITY_END();
}
