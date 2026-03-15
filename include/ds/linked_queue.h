#ifndef DS_LINKED_QUEUE_H
#define DS_LINKED_QUEUE_H

#include <stddef.h>

typedef struct LinkedQueueNode {
    struct LinkedQueueNode *next;
    int data;
} linked_queue_node_t;

typedef struct LinkedQueue {
    struct LinkedQueueNode *head;
    size_t size;
} linked_queue_t;

linked_queue_t *linked_queue_create(void);
void linked_queue_destroy(linked_queue_t *s);
void linked_queue_push(linked_queue_t *s, const int element);
int linked_queue_pop(linked_queue_t *s);
int linked_queue_peek(const linked_queue_t *s);

#endif // DS_LINKED_QUEUE_H
