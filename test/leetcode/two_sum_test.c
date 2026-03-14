#include "unity.h"
#include "leetcode.h"

void setUp(void) {}
void tearDown(void) {}

void test_two_sum_basic(void) {
    int returnSize[] = {0};
    const int nums[] = {2, 7, 11, 15};
    const int *res = twoSum(nums, 4, 9, returnSize);

    TEST_ASSERT_EQUAL_INT(2, returnSize[0]);

    int expected[] = {0, 1};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, res, 2);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_two_sum_basic);
    return UNITY_END();
}
