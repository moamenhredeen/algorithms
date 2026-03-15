#include <stdlib.h>

#include "leetcode.h"
#include "unity.h"

void setUp(void)
{
}
void tearDown(void)
{
}

void test_zigzag_convert_3_rows(void)
{
    char *res = zigzag_convert("PAYPALISHIRING", 3);
    TEST_ASSERT_EQUAL_STRING("PAHNAPLSIIGYIR", res);
    free(res);
}

void test_zigzag_convert_4_rows(void)
{
    char *res = zigzag_convert("PAYPALISHIRING", 4);
    TEST_ASSERT_EQUAL_STRING("PINALSIGYAHRPI", res);
    free(res);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_zigzag_convert_3_rows);
    RUN_TEST(test_zigzag_convert_4_rows);
    return UNITY_END();
}
