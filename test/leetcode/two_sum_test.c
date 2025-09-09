#include <stdio.h>

#include "leetcode.h"

int main() {
    int nums[] = {2, 7, 11, 15};
    int returnSize[] = {0};
    int *res = twoSum(nums, 4, 9, returnSize);
    int expected[] = {0, 1};
    int i;
    for (i = 0; i < 2; i++) {
        if (res[i] != expected[i]) {
            return -1;
        }
    }
    return 0;
}
