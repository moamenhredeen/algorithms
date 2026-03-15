#ifndef DS_LINKED_STACK_H
#define DS_LINKED_STACK_H

#include <stddef.h>

typedef struct LinkedStackNode {
    struct LinkedStackNode *next;
    int data;
} linked_stack_node_t;

typedef struct LinkedStack {
    struct LinkedStackNode *head;
    size_t size;
} linked_stack_t;


linked_stack_t *linked_stack_create(void);
void linked_stack_destroy(linked_stack_t *s);
void linked_stack_push(linked_stack_t *s, const int element);
int linked_stack_pop(linked_stack_t *s);
int linked_stack_peek(const linked_stack_t *s);

#endif // DS_LINKED_STACK_H
