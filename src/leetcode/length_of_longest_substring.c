#include <stdio.h>
#include <stdbool.h>

#include "leetcode.h"
#include "uthash.h"

typedef struct {
    char key;
    int index;
    UT_hash_handle hh;
} item_t;

item_t *seen_items = NULL;

void add_item(char c, int index) {
    item_t *old_item;
    HASH_FIND(hh, seen_items, &c, sizeof(char), old_item);

    item_t *item = malloc(sizeof(item_t));
    item->key = c;
    item->index = index;

    if (old_item) {
        HASH_REPLACE(hh, seen_items, key, sizeof(char), item, old_item);
    } else {
        HASH_ADD(hh, seen_items, key, sizeof(char), item);
    }
}

int exists(char c) {
    item_t *item;
    HASH_FIND(hh, seen_items, &c, sizeof(char), item);
    if (item) return item->index;
    return -1;
}

int lengthOfLongestSubstring(char *s) {
    if (s[0] == '\0') return 0;
    if (s[1] == '\0') return 1;

    int max = 0;
    int seen_index = -1;
    int start = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        seen_index = exists(s[i]);
        if (seen_index >= start) {
            start = seen_index + 1;
        }
        add_item(s[i], i);
        max = (i - start + 1) > max ? (i - start + 1) : max;
    }

    HASH_CLEAR(hh, seen_items);
    return max;
}


/*

// a much better solution by https://laurentsv.com/

int max(int a, int b) {
    return a>b?a:b;
}

int lengthOfLongestSubstring(char* s) {
    char* seen[256] = {0};
    unsigned char c;
    char* start = s;
    int res = 0;

    for (; *s; ++s) {
        c = *s;
        if (seen[c] && seen[c] >= start) {
            start = seen[c] + 1;  // Move start just past previous duplicate
        }
        seen[c] = s;
        res = max(res, s - start + 1);
    }

    return res;
}

*/