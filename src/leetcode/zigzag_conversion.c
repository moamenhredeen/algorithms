#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "leetcode.h"

char *zigzag_convert(char *s, int numRows)
{
    size_t len = strlen(s);
    char *rows[numRows];
    int sizes[numRows];
    for (int i = 0; i < numRows; i++) {
        rows[i] = malloc(len + 1);
        sizes[i] = 0;
    }

    int row = 0, dir = 1;
    for (size_t i = 0; i < len; i++) {
        rows[row][sizes[row]++] = s[i];
        if (row == 0)
            dir = 1;
        else if (row == numRows - 1)
            dir = -1;
        row += dir;
    }

    char *res = malloc(len + 1);
    int idx = 0;
    for (int i = 0; i < numRows; i++) {
        memcpy(res + idx, rows[i], sizes[i]);
        idx += sizes[i];
        free(rows[i]);
    }
    res[idx] = '\0';
    return res;
}
