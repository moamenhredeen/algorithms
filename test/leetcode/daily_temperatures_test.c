#include <assert.h>
#include "leetcode.h"


int main(void) {
    int temperatures[] = {89,62,70,58,47,47,46,76,100,70};
    const int temperaturesSize = sizeof(temperatures) / sizeof(temperatures[0]);
    int  returnSize;
    int* res = daily_temperatures(temperatures, temperaturesSize, &returnSize);
    assert(res != NULL);

    for (int i = 0; i < temperaturesSize; i++) {
        const int expected[] = {8,1,5,4,3,2,1,1,0,0};
        assert(res[i] == expected[i]);
    }
    free(res);
}

