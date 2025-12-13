#include <assert.h>

#include "stack.h"

int main(void) {

    stack_t* s = stack_create(sizeof(int), 10);
    int i;

    i = 2;
    stack_push(s, &i);
    i = 4;
    stack_push(s, &i);

    stack_peek(s, &i);
    assert(i == 4);

    assert(stack_is_empty(s) == 0);

    stack_pop(s);
    stack_peek(s, &i);
    assert(i == 2);

    stack_pop(s);
    assert(stack_is_empty(s) == 1);

    stack_destroy(s);
    return 0;
}
