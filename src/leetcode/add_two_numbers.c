#include "leetcode.h"

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2) {
    struct ListNode *res, *c;
    res = malloc(sizeof(struct ListNode));
    c = res;
    int rest = 0;
    for (;;) {
        c->val = 0;
        if (l1 != NULL) {
            c->val += l1->val;
            l1 = l1->next;
        }
        if (l2 != NULL) {
            c->val += l2->val;
            l2 = l2->next;
        }
        c->val += rest;

        if (c->val >= 10) {
            rest = c->val / 10;
            c->val = c->val % 10;
        } else {
            rest = 0;
        }
        if (l1 || l2 || rest > 0) {
            c->next = malloc(sizeof(struct ListNode));
            c = c->next;
            c->next = NULL;
        } else {
            c->next = NULL;
            break;
        }
    }
    return res;
}
