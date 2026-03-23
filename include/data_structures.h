//
// Created by moamen on 3/22/26.
//

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stddef.h>

/* ------------------------------------- Stack ------------------------------------- */

typedef struct Stack stack_t;

stack_t *stack_create(size_t element_size, int capacity);
void stack_destroy(stack_t *s);
int stack_is_empty(const stack_t *s);
int stack_is_full(stack_t *s);
int stack_push(stack_t *s, const void *element);
int stack_pop(stack_t *s);
int stack_peek(const stack_t *s, void *element);

/* ------------------------------------- Linked List ------------------------------------- */

typedef struct LinkedList {
    int data;
    struct LinkedList *next;
} linked_list_t;

linked_list_t *linked_list_create(int element);

linked_list_t *linked_list_append(linked_list_t *list, int element);

linked_list_t *linked_list_delete(linked_list_t *list, const linked_list_t *element);

linked_list_t *linked_list_find(linked_list_t *list, int element);

void linked_list_destroy(linked_list_t *list);

/* ------------------------------------- Linked Queue ------------------------------------- */

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

/* ------------------------------------- Linked Stack ------------------------------------- */

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

/* ------------------------------------- Binary Tree ------------------------------------- */

typedef struct BinaryTree binary_tree_t;

binary_tree_t *binary_tree_create(int item);
binary_tree_t *binary_tree_search(binary_tree_t *tree, int item);
int *get_item(binary_tree_t *tree);
void binary_tree_destroy(binary_tree_t *tree);

#endif // DATA_STRUCTURES_H
