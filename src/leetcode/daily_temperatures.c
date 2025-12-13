#include "mylib/stack.h"
#include "leetcode.h"

int* daily_temperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    int* res = malloc(sizeof(int) * temperaturesSize);
    stack_t* stack = stack_create(sizeof(int), temperaturesSize);
    int i, prev_i;
    for (i = 0; i < temperaturesSize; i++) {
        while (!stack_is_empty(stack)) {
            stack_peek(stack, &prev_i);
            if (temperatures[prev_i] >= temperatures[i]) {
                break;
            }
            res[prev_i] = i - prev_i;
            stack_pop(stack);
        }
        res[i] = 0;
        stack_push(stack, &i);
    }
    stack_destroy(stack);
    *returnSize = temperaturesSize;
    return res;
}