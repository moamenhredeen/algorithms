//
// Created by moamen on 3/14/26.
//

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct LinkedList {
    int data;
    struct LinkedList *next;
} linked_list_t;

linked_list_t *linked_list_create(int element);

linked_list_t *linked_list_append(linked_list_t *list, int element);

linked_list_t *linked_list_delete(linked_list_t *list, const linked_list_t *element);

linked_list_t *linked_list_find(linked_list_t *list, int element);

void linked_list_destroy(linked_list_t *list);

#endif // LINKED_LIST_H
