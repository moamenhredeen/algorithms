#ifndef ALGORITHMS_DATA_STRUCTURES_H
#define ALGORITHMS_DATA_STRUCTURES_H
#include <stddef.h>

/**
 * static-sized stack
 */
typedef struct Stack {
    void *data;
    int top;
    int capacity;
    size_t element_size;
} stack_t;


stack_t*    stack_create    (size_t element_size, int capacity);
void        stack_destroy   (stack_t *s);
int         stack_is_empty  (const stack_t *s);
int         stack_is_full   (stack_t *s);
int         stack_push      (stack_t *s, const void *element);
int         stack_pop       (stack_t *s);
int         stack_peek      (const stack_t *s, void* element);

#endif //ALGORITHMS_DATA_STRUCTURES_H