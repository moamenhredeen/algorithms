//
// Created by moamen on 3/14/26.
//

#include <stddef.h>

#include "ds/linked_list.h"

#include <stdlib.h>

linked_list_t *linked_list_create(const int element)
{
    linked_list_t *list = malloc(sizeof(linked_list_t));
    list->data = element;
    list->next = NULL;
    return list;
}

linked_list_t *linked_list_append(linked_list_t *list, const int element)
{
    if (list == NULL) {
        return NULL;
    }
    linked_list_t *new_list = malloc(sizeof(linked_list_t));
    new_list->data = element;
    new_list->next = NULL;

    linked_list_t *last = list;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_list;
    return new_list;
}

linked_list_t *linked_list_delete(linked_list_t *list, const linked_list_t *element)
{
    if (list == NULL) {
        return NULL;
    }
    linked_list_t *prev = NULL;
    linked_list_t *current = NULL;

    current = list;
    if (current == element) {
        if (current->next == NULL) {
            free(current);
            return NULL;
        }
        list = current->next;
        free(current);
        return list;
    }

    prev = current;
    current = current->next;
    while (current != NULL) {
        if (current == element) {
            prev->next = current->next;
            free(current);
            return list;
        }
        prev = current;
        current = current->next;
    }
    return list;
}

linked_list_t *linked_list_find(linked_list_t *list, const int element)
{
    if (list == NULL) {
        return NULL;
    }

    linked_list_t *current = list;
    while (current != NULL) {
        if (current->data == element) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void linked_list_destroy(linked_list_t *list)
{
    if (list == NULL) {
        return;
    }
    linked_list_t *current = list;
    linked_list_t *next = NULL;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
