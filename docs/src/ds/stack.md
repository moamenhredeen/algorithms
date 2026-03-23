# Stack

An array-based stack that stores elements of any type using a fixed-capacity buffer.

## Interface

```c
{{#include ../../../include/data_structures.h:23:70}}
```

## Implementation

```c
{{#include ../../../src/ds/stack.c}}
```

## Complexity

| Operation | Time |
|-----------|------|
| Create    | O(1) |
| Push      | O(1) |
| Pop       | O(1) |
| Peek      | O(1) |
| Is Empty  | O(1) |
