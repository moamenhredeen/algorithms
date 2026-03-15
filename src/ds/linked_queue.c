#include "ds/linked_queue.h"
#include <stdlib.h>

linked_queue_t *linked_queue_create(void)
{
    linked_queue_t *new_queue = malloc(sizeof(linked_queue_t));
    new_queue->head = NULL;
    new_queue->size = 0;
    return new_queue;
}

void linked_queue_destroy(linked_queue_t *s)
{
    if (s == NULL) {
        return;
    }

    linked_queue_node_t *current = s->head;
    linked_queue_node_t *next = NULL;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(s);
}

void linked_queue_push(linked_queue_t *q, const int element)
{
    if (q == NULL) {
        return;
    }

    linked_queue_node_t *new_node = malloc(sizeof(linked_queue_node_t));
    new_node->data = element;
    new_node->next = q->head;
    q->head = new_node;
    q->size++;
}

int linked_queue_pop(linked_queue_t *q)
{
    if (q == NULL) {
        return 0;
    }

    if (q->head == NULL) {
        return 0;
    }

    if (q->head->next == NULL) {
        int res = q->head->data;
        free(q->head);
        q->head = NULL;
        q->size--;
        return res;
    }

    linked_queue_node_t *prev = q->head;
    linked_queue_node_t *current = q->head->next;

    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    q->size--;
    prev->next = NULL;
    int res = current->data;
    free(current);
    return res;
}

int linked_queue_peek(const linked_queue_t *q)
{
    if (q == NULL) {
        return 0;
    }

    linked_queue_node_t *node = q->head;
    while (node->next != NULL) {
        node = node->next;
    }

    if (node == NULL) {
        return 0;
    }
    return node->data;
}
