#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "leetcode.h"

struct ListNode *fill(const int *arr, int size) {
    struct ListNode *start = malloc(sizeof(struct ListNode));
    struct ListNode *curr = start;
    for (int i = 0; i < size; i++) {
        curr->val = arr[i];
        curr->next = malloc(sizeof(struct ListNode));
        curr = curr->next;
    }
    return start;
}

void l(const struct ListNode *l, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        if (l->val) {
            printf("%d ", l->val);
            l = l->next;
        }
    }
    printf("]\n");
}

bool match (struct ListNode *list, const int *arr, int size) {
    for (int i = 0; i < size; i++) {
        if (list->val != arr[i]) return false;
        list = list->next;
    }
    return true;
}

int main() {

    struct ListNode *res;
    struct ListNode *l1;
    struct ListNode *l2;

    l1 = fill((int[]){7, 8, 9}, 3);
    l2 = fill((int[]){7, 8, 9}, 3);
    res = addTwoNumbers(l1, l2);
    l(res, 4);
    assert(match(res, (int[]){4, 7, 9, 1}, 4) == true);


    l1 = fill((int[]){2, 4, 3}, 3);
    l2 = fill((int[]){5, 6, 4}, 3);
    res = addTwoNumbers(l1, l2);
    l(res, 3);
    assert(match(res, (int[]){7, 0, 8}, 3) == true);


    l1 = fill((int[]){9,9,9,9,9,9,9}, 7);
    l2 = fill((int[]){9,9,9,9}, 4);
    res = addTwoNumbers(l1, l2);
    l(res, 8);
    assert(match(res, (int[]){8,9,9,9,0,0,0,1}, 8) == true);

    return 0;
}
