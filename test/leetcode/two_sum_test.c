#include <stdio.h>

#include "leetcode.h"

int main() {
    int nums[] = {2, 7, 11, 15};
    int returnSize[] = {0};
    int *res = twoSum(nums, 4, 9, returnSize);
    if (res) {
        printf("res = %d", res[0]);
        return 0;
    }
    return -1;
}
