#include "leetcode.h"
#include <assert.h>
#include <string.h>

int main(void) {
	struct ListNode n5 = { .val = 5, .next = NULL};
	struct ListNode n4 = { .val = 4, .next = &n5 };
	struct ListNode n3 = { .val = 3, .next = &n4 };
	struct ListNode n2 = { .val = 2, .next = &n3 };
	struct ListNode n1 = { .val = 1, .next = &n2 };
	struct ListNode* res = rotateRight(&n1, 2);
	assert(res->val == 5);
	assert(res->next != NULL);
	res = res->next;
	assert(res->val == 4);
	assert(res->next != NULL);
	res = res->next;
	assert(res->val == 1);
	assert(res->next != NULL);
	res = res->next;
	assert(res->val == 2);
	assert(res->next != NULL);
	res = res->next;
	assert(res->val == 3);
	return 0;
}
