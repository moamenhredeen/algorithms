#include <assert.h>

#include "leetcode.h"

int main(void) {
    int returnSize[] = {0};
    const int nums[] = {2, 7, 11, 15};
    const int *res = twoSum(nums, 4, 9, returnSize);
    assert(returnSize[0] == 2);
    for (int i = 0; i < 2; i++) {
        const int expected[] = {0, 1};
        assert(res[i] == expected[i]);
    }
    return 0;
}
