#include <stdlib.h>
#include "leetcode.h"

typedef struct {
    int value;
    int index;
} Pair;

int comparePairs(const void *a, const void *b) {
    return ((Pair*)a)->value - ((Pair*)b)->value;
}

int* twoSum(const int* nums, const int numsSize, const int target, int* returnSize) {
    int *res = malloc(sizeof(int) * 2);
    Pair* pairs = malloc(sizeof(Pair) * numsSize);
    for (int i = 0; i < numsSize; i++) {
        pairs[i].value = nums[i];
        pairs[i].index = i;
    }

    returnSize[0] = 2;
    qsort(pairs, numsSize, sizeof(Pair), comparePairs);
    int left = 0;
    int right = numsSize - 1;
    while (left < right) {
        const int sum = pairs[left].value + pairs[right].value;
        if (sum == target) {
            res[0] = pairs[left].index;
            res[1] = pairs[right].index;
            free(pairs);
            return res;
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }

    free(pairs);
    return NULL;
}
