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

void remove_item(char c, int index) {
    item_t *item;
    HASH_FIND(hh, seen_items, &c, sizeof(char), item);
    if (item && item->index == index) {
        HASH_DEL(seen_items, item);
        free(item);
    }
}

int lengthOfLongestSubstring(char *s) {
    if (s[0] == '\0') return 0;
    if (s[1] == '\0') return 1;

    int max = 0;
    int temp = -1;
    int start = 0;
    int deleted = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        temp = exists(s[i]);
        if (temp >= 0) {
            start = temp + 1;
            while (deleted < start) {
                remove_item(s[deleted], deleted);
                deleted++;
            }
        }
        add_item(s[i], i);
        max = (i - start + 1) > max ? (i - start + 1) : max;
    }

    HASH_CLEAR(hh, seen_items);
    return max;
}