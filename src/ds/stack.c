#include "data_structures.h"

#include <stdlib.h>
#include <string.h>

stack_t *stack_create(const size_t element_size, const int capacity)
{
    stack_t *s = malloc(sizeof(stack_t));
    s->data = malloc(capacity * element_size);
    s->top = -1;
    s->capacity = capacity;
    s->element_size = element_size;
    return s;
}

void stack_destroy(stack_t *s)
{
    if (s) {
        free(s->data);
        free(s);
    }
}

int stack_is_empty(const stack_t *s)
{
    return s->top == -1;
}

int stack_is_full(stack_t *s)
{
    return s->top == s->capacity - 1;
}

int stack_push(stack_t *s, const void *element)
{
    if (stack_is_full(s)) {
        return 0;
    }
    memcpy((char *)s->data + (++s->top * s->element_size), element, s->element_size);
    return 1;
}

int stack_pop(stack_t *s)
{
    if (stack_is_empty(s)) {
        return 0;
    }
    s->top--;
    return 1;
}

int stack_peek(const stack_t *s, void *element)
{
    if (stack_is_empty(s)) {
        return 0;
    }
    memcpy(element, (char *)s->data + (s->top * s->element_size), s->element_size);
    return 1;
}
