#include <stdlib.h>

#include "ds/linked_stack.h"

linked_stack_t *linked_stack_create(void){
    linked_stack_t *s = malloc(sizeof(linked_stack_t));
    s->head = NULL;
    s->size = 0;
    return s;
}

void linked_stack_destroy(linked_stack_t *s) {
    linked_stack_node_t *current = s->head;
    linked_stack_node_t *next = NULL;
    free(s);
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void linked_stack_push(linked_stack_t *s, const int element){
    linked_stack_node_t *new_node = malloc(sizeof(linked_stack_node_t));
    new_node->data = element;
    new_node->next = s->head;
    s->head = new_node;
    s->size++;
}

int linked_stack_pop(linked_stack_t *s) {
    if (s->head == NULL) {
        return 0;
    }
    linked_stack_node_t *node = s->head;
    if (node->next == NULL) {
        s->head = NULL;
    } else {
        s->head = node->next;
    }
    s->size--;
    int data = node->data;
    free(node);
    return data;
}

int linked_stack_peek(const linked_stack_t *s){
    if (s->head == NULL) {
        return 0;
    }
    return s->head->data;
}
