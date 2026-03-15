#include "leetcode.h"
#include "unity.h"

void setUp(void)
{
}
void tearDown(void)
{
}

void test_daily_temperatures(void)
{
    int temperatures[] = {89, 62, 70, 58, 47, 47, 46, 76, 100, 70};
    const int size = sizeof(temperatures) / sizeof(temperatures[0]);
    int returnSize;
    int *res = daily_temperatures(temperatures, size, &returnSize);

    TEST_ASSERT_NOT_NULL(res);

    int expected[] = {8, 1, 5, 4, 3, 2, 1, 1, 0, 0};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, res, size);

    free(res);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_daily_temperatures);
    return UNITY_END();
}
