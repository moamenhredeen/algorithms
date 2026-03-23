/**
 * @file data_structures.h
 * @brief Common data structure interfaces.
 *
 * This header declares generic stack, linked-list, linked-queue,
 * linked-stack, and binary-tree data structures.
 *
 * @note Ownership convention: every `*_create` function allocates memory
 *       and returns a pointer that the **caller owns**. The caller is
 *       responsible for freeing that memory by calling the corresponding
 *       `*_destroy` function when the data structure is no longer needed.
 *
 * Created by moamen on 3/22/26.
 */

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stddef.h>

/* ------------------------------------- Stack ------------------------------------- */

typedef struct Stack stack_t;

/**
 * Create a new stack that stores elements of @p element_size bytes
 * with the given @p capacity.
 *
 * @param element_size Size in bytes of each element.
 * @param capacity     Maximum number of elements the stack can hold.
 * @return Pointer to the newly created stack, or NULL on allocation failure.
 *         The caller must free the returned stack with stack_destroy().
 */
stack_t *stack_create(size_t element_size, int capacity);

/**
 * Destroy the stack and free all associated memory.
 */
void stack_destroy(stack_t *s);

/**
 * Check whether the stack is empty.
 * @return Non-zero if empty, 0 otherwise.
 */
int stack_is_empty(const stack_t *s);

/**
 * Check whether the stack is full.
 * @return Non-zero if full, 0 otherwise.
 */
int stack_is_full(stack_t *s);

/**
 * Push a copy of @p element onto the stack.
 * @return 0 on success, non-zero on failure.
 */
int stack_push(stack_t *s, const void *element);

/**
 * Remove the top element from the stack.
 * @return 0 on success, non-zero on failure.
 */
int stack_pop(stack_t *s);

/**
 * Copy the top element into the buffer pointed to by @p element
 * without removing it from the stack.
 * @return 0 on success, non-zero on failure.
 */
int stack_peek(const stack_t *s, void *element);

/* ------------------------------------- Linked List ------------------------------------- */

typedef struct LinkedList {
    int data;
    struct LinkedList *next;
} linked_list_t;

/**
 * Create a new single-element linked list containing @p element.
 *
 * @return Pointer to the new node, or NULL on allocation failure.
 *         The caller must free the list with linked_list_destroy().
 */
linked_list_t *linked_list_create(int element);

/**
 * Append @p element to the end of @p list.
 * @return Pointer to the head of the list, or NULL on allocation failure.
 */
linked_list_t *linked_list_append(linked_list_t *list, int element);

/**
 * Delete the node @p element from @p list.
 * @return Pointer to the head of the modified list.
 */
linked_list_t *linked_list_delete(linked_list_t *list, const linked_list_t *element);

/**
 * Find the first node containing @p element.
 * @return Pointer to the matching node, or NULL if not found.
 */
linked_list_t *linked_list_find(linked_list_t *list, int element);

/**
 * Destroy the entire linked list and free all nodes.
 */
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

/**
 * Create an empty linked queue.
 *
 * @return Pointer to the new queue, or NULL on allocation failure.
 *         The caller must free the queue with linked_queue_destroy().
 */
linked_queue_t *linked_queue_create(void);

/**
 * Destroy the queue and free all nodes.
 */
void linked_queue_destroy(linked_queue_t *s);

/**
 * Enqueue @p element at the back of the queue.
 */
void linked_queue_push(linked_queue_t *s, const int element);

/**
 * Dequeue and return the front element.
 */
int linked_queue_pop(linked_queue_t *s);

/**
 * Return the front element without removing it.
 */
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

/**
 * Create an empty linked stack.
 *
 * @return Pointer to the new stack, or NULL on allocation failure.
 *         The caller must free the stack with linked_stack_destroy().
 */
linked_stack_t *linked_stack_create(void);

/**
 * Destroy the stack and free all nodes.
 */
void linked_stack_destroy(linked_stack_t *s);

/**
 * Push @p element onto the stack.
 */
void linked_stack_push(linked_stack_t *s, const int element);

/**
 * Pop and return the top element.
 */
int linked_stack_pop(linked_stack_t *s);

/**
 * Return the top element without removing it.
 */
int linked_stack_peek(const linked_stack_t *s);

/* ------------------------------------- Binary Tree ------------------------------------- */

typedef struct BinaryTree binary_tree_t;

/**
 * Create a new binary tree node with the given item.
 *
 * @return Pointer to the newly created node, or NULL on allocation failure.
 *         The caller must free the tree with binary_tree_destroy().
 */
binary_tree_t *binary_tree_create(int item);

/**
 * Recursively destroy the binary tree and free all allocated memory.
 */
void binary_tree_destroy(binary_tree_t *tree);

/**
 * Search for an item in the binary tree.
 * Returns a pointer to the node containing the item, or NULL if not found.
 */
binary_tree_t *binary_tree_search(binary_tree_t *tree, int item);

/**
 * Find the node with the minimum value in the binary tree.
 * Returns a pointer to the node with the smallest item.
 */
binary_tree_t *binary_tree_find_minimum(binary_tree_t *tree);

/**
 * Find the node with the maximum value in the binary tree.
 * Returns a pointer to the node with the largest item.
 */
binary_tree_t *binary_tree_find_maximum(binary_tree_t *tree);

/**
 * Traverse the binary tree in-order, calling @p func on each node.
 *
 * @param tree      Root of the tree to traverse (may be NULL).
 * @param func      Callback invoked for each node.
 * @param user_data Opaque pointer forwarded to @p func on every call.
 */
void binary_tree_traverse(binary_tree_t *tree, void (*func)(binary_tree_t *node, void *user_data),
                          void *user_data);

/**
 * Get the item stored in the given tree node.
 */
int get_item(binary_tree_t *tree);

#endif // DATA_STRUCTURES_H
