#include "unity.h"
#include "leetcode.h"

void setUp(void) {}
void tearDown(void) {}

void test_length_of_longest_substring(void) {
    TEST_ASSERT_EQUAL_INT(3, lengthOfLongestSubstring("abcabcbb"));
    TEST_ASSERT_EQUAL_INT(1, lengthOfLongestSubstring("bbbbb"));
    TEST_ASSERT_EQUAL_INT(3, lengthOfLongestSubstring("pwwkew"));
    TEST_ASSERT_EQUAL_INT(2, lengthOfLongestSubstring("au"));
    TEST_ASSERT_EQUAL_INT(3, lengthOfLongestSubstring("bwf"));
    TEST_ASSERT_EQUAL_INT(2, lengthOfLongestSubstring("aab"));
    TEST_ASSERT_EQUAL_INT(3, lengthOfLongestSubstring("dvdf"));
}

void test_length_of_longest_substring_long_input(void) {
    TEST_ASSERT_EQUAL_INT(95, lengthOfLongestSubstring(
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ "
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ "
    ));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_length_of_longest_substring);
    RUN_TEST(test_length_of_longest_substring_long_input);
    return UNITY_END();
}
