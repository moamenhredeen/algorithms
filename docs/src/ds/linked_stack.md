# Linked Stack

A stack implemented using a singly linked list with no fixed capacity.

## Interface

```c
{{#include ../../../include/data_structures.h:152:188}}
```

## Implementation

```c
{{#include ../../../src/ds/linked_stack.c}}
```

## Complexity

| Operation | Time |
|-----------|------|
| Create    | O(1) |
| Push      | O(1) |
| Pop       | O(1) |
| Peek      | O(1) |
| Destroy   | O(n) |
