# How i Program C

## Typing is not the Problem

the bottleneck in programming is never how fast you type. you spend far more time reading code than writing it — reading to understand what it does, reading to find where to make a change, reading to figure out why something broke.

this means optimizing for fewer keystrokes is the wrong trade-off. saving 10 characters in a variable name costs you every time someone (including future you) has to stop and think about what it means.

ambiguity is the real enemy. if a line of code can be interpreted in more than one way, it will be misread eventually. write code that can only be understood one way.

## Clever is evil

"clever" code optimizes for the writer's moment of satisfaction, not for the reader's ability to understand it six months later. every time the language lets you hide what is actually happening, you create a trap for the next person — and that person is usually you.

#### operator overloading

what does this mean? pairwise multiplication? dot product? cross product?

```c++
vec_a = vec_b * vec_c;
```

you cannot know without finding the operator definition. these cannot be misunderstood:

```c++
vector_mul(vec_a, vec_b, vec_c);
vector_dot(vec_a, vec_b, vec_c);
vector_cross(vec_a, vec_b, vec_c);
```

the operation is in the name. no lookup required.

#### function overloading

```c++
int    add(int a, int b);
float  add(float a, float b);
double add(double a, double b);
```

what happens when you write this?

```c++
x = add(2, 2.2);
```

the C++ standard defines which overload the compiler picks (it promotes `2` to `double` and calls the `double` version). the problem is that most people do not know that, and even if they do, it is not obvious when reading the code. you have to simulate the overload resolution rules in your head.

why not just say what you mean?

```c++
int    addi(int a, int b);
float  addf(float a, float b);
double addd(double a, double b);
```

now `addi(2, 3)` is unambiguous. `addd(2.0, 2.2)` is unambiguous. and `addi(2, 2.2)` gives you a compiler warning about truncation — which is exactly what you want.

#### implicit conversions

another form of cleverness that causes real bugs:

```c
unsigned int a = 10;
int b = -1;

if (b < a) {
    // you expect this to run, but it does not
    // b is implicitly converted to unsigned, -1 becomes 4294967295
}
```

the compiler silently converts `-1` to a very large unsigned number. the comparison is technically well-defined by the standard, but it does not do what the programmer intended. this class of bug has caused real security vulnerabilities.

#### why C gets this right

C does not have operator overloading. C does not have function overloading. this is not a limitation — it is a design decision. when you read C code, `a + b` is always arithmetic. a function name always refers to exactly one function. there is no hidden dispatch, no implicit conversion magic beyond the basic promotion rules.

the language forces you to be explicit, and explicit code is code you can trust when reading it.

## Naming

good code is wide code. wide means long, descriptive names for types, functions, and variables. a name should tell you what something is or does without needing to read the implementation. short names save keystrokes but cost understanding — and as we established, typing is not the problem.

pick naming conventions and stick to them across the entire codebase:

```c
// typedef: snake_case + _t suffix
// struct tag: PascalCase
typedef struct LinkedList {
    int                  data;
    struct LinkedList    *next;
} linked_list_t;

// functions: snake_case
void draw_point(linked_list_t p);

// variables: snake_case
linked_list_t *head;
```

#### build a vocabulary

define words that have a specific meaning in your codebase and use them consistently. when a reader sees one of these words, they should immediately know what kind of thing they are looking at:

| suffix/word  | meaning                                           |
|--------------|---------------------------------------------------|
| `_array`     | contiguous array of elements                      |
| `_type`      | usually an enum discriminating variants           |
| `_node`      | element that links to other elements              |
| `_entity`    | generic networked or identifiable thing            |
| `_handle`    | opaque pointer — caller should not dereference it |
| `_func`      | function pointer or used as one                   |
| `_internal`  | not part of the public API, do not call directly  |
| `_count`     | number of elements (not bytes)                    |
| `_size`      | size in bytes                                     |
| `_capacity`  | total allocated space (elements or bytes)          |

the distinction between `count`, `size`, and `capacity` alone prevents a large class of off-by-one and buffer overflow bugs.

#### structured naming

put the type or module first, then the operation. this groups related functions together in autocomplete, documentation, and your mental model:

```c
// Bad: verb first scatters related functions across the alphabet
create_linked_list();
destroy_linked_list();
print_linked_list();

// Good: module first groups them together
linked_list_create();
linked_list_destroy();
linked_list_print();
```

for larger projects, extend the pattern: `library_module_operation`

```c
mylib_linked_list_create();
mylib_hash_map_insert();
```

this is C's version of namespaces. it is not as pretty as `namespace` or modules, but it works everywhere and has zero overhead.

#### symmetric naming

every operation that acquires a resource should have a clearly named reverse. the names should form obvious pairs so that a reader can immediately tell what undoes what:

```c
// Bad: "remove" is not the opposite of "create"
linked_list_create();
linked_list_remove();

// Good: create/destroy is a clear pair
linked_list_create();
linked_list_destroy();
```

common symmetric pairs to use consistently:

| acquire       | release        |
|---------------|----------------|
| `create`      | `destroy`      |
| `init`        | `deinit`       |
| `open`        | `close`        |
| `lock`        | `unlock`       |
| `push`        | `pop`          |
| `alloc`       | `free`         |
| `acquire`     | `release`      |

if you use `init` somewhere and `deinit` somewhere else but `destroy` in a third place, you have introduced ambiguity. pick one pair per concept and use it everywhere.

## Long functions are good

conventional wisdom says functions should be short — a page or two at most. the reasoning is that small functions are easier to understand in isolation. but this ignores the cost: when you split sequential work into many small functions, you scatter the execution flow across the file. now instead of reading top to bottom, you are jumping around, holding a mental call stack, trying to reconstruct what actually happens and in what order.

if a sequence of operations must happen in a specific order, their code should follow sequentially. a 2000-line function where you can read straight down and see exactly what happens first, second, third is easier to reason about than 40 tiny functions where the actual execution order is hidden behind layers of indirection.

> Awareness of all the code that is actually executing is important,
> and it is too easy to have very large blocks of code that you just always skip over while debugging,
> even though they have performance and stability implications.
>
> -- John Carmack

#### the real enemy is hidden state mutation

the argument for inlining is not about performance. it is about visibility. when operations are buried deep inside nested function calls, several things go wrong:

- **latency creeps in**: it becomes hard to tell if operation A finishes before operation B starts. in a game running at 60fps, one frame of extra input latency can ship unnoticed — and [it nearly did on Doom 3 BFG](http://number-none.com/blow/john_carmack_on_inlined_code.html), exactly as Carmack predicted
- **unnecessary calls multiply**: if `FullUpdate()` calls `PartialUpdateA()` and `PartialUpdateB()`, someone will eventually call `PartialUpdateB()` directly thinking they are being efficient. most bugs come from the execution state not being what you think it is
- **conditional skipping breeds bugs**: skipping an expensive operation to "optimize" often also skips state updates that something else depends on. you get better benchmark numbers and more bugs

#### when to inline

- if a function is only called from a single place, inline it
- if a function is called from multiple places, see if you can arrange for the work to happen in one place with flags, and inline that
- if there are multiple versions of a function, consider a single function with more parameters

#### when not to inline

inlining runs into conflict with modularity, and good judgment matters. heavyweight objects with clear boundaries are reasonable break points. the goal is not to have one giant function for the entire program — it is to stop splitting sequential logic into small functions just because someone said functions should be short.

#### practical tips for long functions

use large comment blocks to delimit logical sections within the function. use bare braced blocks `{ }` to scope local variables and allow editor folding:

```c
void game_frame(game_state_t *state) {
    // ── input sampling ──────────────────────────
    {
        int raw_x = input_read_axis(AXIS_X);
        int raw_y = input_read_axis(AXIS_Y);
        state->input.x = clamp(raw_x, -128, 127);
        state->input.y = clamp(raw_y, -128, 127);
    }

    // ── physics update ──────────────────────────
    {
        float dt = state->frame_dt;
        state->pos.x += state->vel.x * dt;
        state->pos.y += state->vel.y * dt;
        // ...
    }

    // ── collision ───────────────────────────────
    {
        // ...
    }

    // ── rendering ───────────────────────────────
    {
        // ...
    }
}
```

each section reads like a chapter. local variables are scoped to where they are used. the execution order is obvious. and you cannot accidentally call "physics update" from somewhere else, because it is not a function — it is just code that runs in sequence.

#### execute and inhibit

rather than conditionally skipping work, consider always doing the work and then inhibiting or ignoring the result:

```c
// Bad: conditional execution, easy to skip needed state updates
if (player->alive) {
    player_update_physics(player);
    player_update_animation(player);
}

// Better: always execute, inhibit results
player_update_physics(player);
player_update_animation(player);
if (!player->alive) {
    player_reset_frame_state(player);
}
```

the second version takes slightly more absolute time, but it reduces variability in frame times and eliminates a class of bugs where the skipped path leaves state inconsistent. worst case performance matters more than average case performance.

#### factor out pure functions

when a long function becomes too much to manage, the answer is not to blindly split it into small impure functions. factor out **pure functions** — functions that only read their inputs and return a value without touching any global state:

```c
// pure: no side effects, easy to test, safe to call from anywhere
float calculate_damage(float base, float armor, float multiplier) {
    return (base - armor) * multiplier;
}
```

keep the state mutations inline and visible. push the computation into pure functions. this gives you the best of both worlds: the sequential clarity of inlined code and the reusability of functions, without the hidden state mutation bugs.

## API Design

#### start from the outside and go in

do not start by writing the implementation and then wrapping an API around it. start from the caller's perspective: what does the user of this code want to do? write the call sites first, then make them compile.

```c
// step 1: write the code you WISH you could write
hash_map_t *map = hash_map_create(64);
hash_map_insert(map, "name", "Carmack");
hash_map_insert(map, "engine", "idTech");

const char *name = hash_map_get(map, "name");

hash_map_destroy(map);
```

this tells you exactly what your API needs to look like before you write a single line of implementation. the function signatures, the parameter order, the naming — all of it falls out of what feels natural at the call site.

if the call site looks ugly or confusing, the API is wrong. fix it before you implement it, when the cost of change is near zero.

#### write tests first (TDD)

a similar approach: write the tests before the implementation. tests are just call sites with expectations, so they force the same outside-in thinking:

```c
void test_hash_map_insert_and_get(void) {
    hash_map_t *map = hash_map_create(16);

    hash_map_insert(map, "key", "value");
    ASSERT_STR_EQ(hash_map_get(map, "key"), "value");
    ASSERT_NULL(hash_map_get(map, "missing"));

    hash_map_destroy(map);
}
```

now you have a specification for what the code should do, a way to verify it works, and an API that was designed from the user's perspective — all before writing the implementation.

#### API design principles

- **minimize the surface area**: expose only what the caller needs. fewer functions means fewer things to learn, fewer things to break, and fewer things to maintain
- **make the common case easy and the rare case possible**: the function most people call should have the fewest parameters. power-user variations can take extra arguments
- **return errors, do not print them**: the API should never call `printf` or `exit`. return an error code or NULL and let the caller decide how to handle it
- **do not require initialization order**: if calling function B before function A causes a crash, your API is fragile. either enforce the order or remove it
- **make resource ownership obvious**: if the caller must free the return value, the function name should make that clear (`create`/`destroy`, not `get`)

```c
// Bad: caller has no idea they need to free this
char *get_username(user_t *user);

// Good: "create" signals the caller owns the result
char *username_create(user_t *user);
// or: copy into a caller-provided buffer, no ownership transfer
void username_get(user_t *user, char *buf, size_t buf_size);
```

#### design for the error path

most APIs are designed for the happy path and then errors are bolted on as an afterthought. think about errors from the start:

```c
// what happens if the file doesn't exist?
// what happens if the buffer is too small?
// what happens if malloc fails inside this function?
// what happens if the caller passes NULL?
```

decide upfront: do you return error codes, set errno, return NULL, or use an out-parameter? pick one convention and use it everywhere in the module.

```c
// consistent convention: return 0 on success, -1 on error
int config_load(config_t *cfg, const char *path);
int config_get_int(config_t *cfg, const char *key, int *out_value);
int config_get_str(config_t *cfg, const char *key, char *buf, size_t buf_size);
```

the caller can always check the pattern the same way. no surprises.

## Object Oriented Programming

OOP languages wrap several concepts behind syntax that hides what is actually happening:

```c++
object = new Type();
object.operation();
```

there are at least two hidden things here:
- `new` is a special keyword that calls `malloc` (or equivalent), then calls a constructor function, then returns a pointer — three operations disguised as one
- `object.operation()` is syntax sugar for `operation(this = object)` — a regular function call with an implicit first argument

in C, the same thing looks like this:

```c
user_t *user = user_create("Carmack");
user_set_role(user, ROLE_ADMIN);
user_destroy(user);
```

nothing is hidden. `user_create` clearly allocates and returns an object. `user_set_role` clearly takes the object as its first argument and operates on it. `user_destroy` clearly frees it. every operation is a visible function call with explicit arguments.

#### why this is better

in C++, reading `object.operation()` tells you almost nothing:
- is it virtual? you cannot tell without checking the class hierarchy
- does it modify the object? you cannot tell without reading the implementation
- does it touch global state? you cannot tell without reading the implementation
- does it allocate memory? you cannot tell without reading the implementation

in C, `module_operation(object)` is always a direct call to a known function. there is no vtable lookup, no implicit `this`, no constructor/destructor chain firing behind the scenes. what you read is what executes.

#### information hiding with opaque pointers

C does not have `private` or `public` keywords, but it has something better: the opaque pointer pattern. the public header exposes only a forward declaration. the caller can hold a pointer to the type but cannot access its fields — because the struct definition only exists in the implementation file.

```c
/* ── user.h (public) ─────────────────────────── */
typedef struct User user_t;  // forward declaration, size unknown to caller

user_t *user_create(const char *name);
void    user_destroy(user_t *user);
void    user_set_role(user_t *user, int role);
const char *user_get_name(user_t *user);
```

```c
/* ── user.c (internal) ───────────────────────── */
#include "user.h"

struct User {
    long  id;
    char  name[64];
    int   role;
};

user_t *user_create(const char *name) {
    user_t *u = calloc(1, sizeof *u);
    if (!u) return NULL;
    strncpy(u->name, name, sizeof u->name - 1);
    return u;
}

void user_destroy(user_t *user) {
    free(user);
}

void user_set_role(user_t *user, int role) {
    user->role = role;
}

const char *user_get_name(user_t *user) {
    return user->name;
}
```

the caller includes `user.h` and can only interact through the provided functions. they cannot read or write struct fields directly. if you change the internal layout of `struct User` — reorder fields, add new ones, change types — no code outside `user.c` needs to recompile (as long as the header stays the same).

this is stronger encapsulation than C++ `private`, because with `private` the struct layout is still visible in the header (the compiler needs it for `sizeof`). with opaque pointers, the layout is truly hidden.

#### why not void pointer?

you might think: why not just use `typedef void *user_handle_t` in the public header? it also hides the struct. the difference is type safety.

an incomplete type (`typedef struct User user_t`) tells the compiler "this is a specific type, you just don't know what's inside it." the compiler enforces that you only use it where a `user_t *` is expected:

```c
typedef struct User user_t;

user_t *a = user_create("Alice");
user_t *b = user_create("Bob");

a = b;            // OK: same type
int *x = a;       // ERROR: incompatible pointer types
a->name;          // ERROR: dereferencing incomplete type
sizeof(user_t);   // ERROR: incomplete type
```

a `void *` tells the compiler nothing. it accepts any pointer and converts to any pointer silently:

```c
typedef void *user_handle_t;

user_handle_t a = user_create("Alice");
user_handle_t b = config_create("/etc/foo");  // completely unrelated type

a = b;            // OK: no warning, silent bug
int *x = a;       // OK: no warning
```

with `void *`, you can pass a `config_t *` where a `user_t *` is expected and the compiler will say nothing — you get a silent bug at runtime. with an incomplete type, the compiler catches it at compile time. there is no reason to use `void *` when a forward declaration gives you both information hiding and type safety.

#### the trade-off

opaque pointers force all access through function calls and require heap allocation (the caller cannot stack-allocate something whose size they do not know). for performance-critical inner loops or small value types, this overhead matters. use opaque pointers for heavyweight module-level objects (a database connection, a renderer, a config parser) where the encapsulation benefit outweighs the indirection cost. for small data like vectors, colors, or rectangles — just use plain structs.

## Macros

macros are text substitution performed by the preprocessor before the compiler ever sees your code. this makes them powerful and dangerous — they operate outside the type system, outside scoping rules, and outside everything the compiler can check for you.

as a general rule: if you can do it with a function, a `const`, an `enum`, or an `inline`, do not use a macro. but there are things that only macros can do, and those are the cases worth knowing.

#### why macros are dangerous

macros do not respect scope, types, or evaluation rules:

```c
// double evaluation: x gets incremented twice
#define MAX(a, b) ((a) > (b) ? (a) : (b))
int x = 5, y = 3;
int z = MAX(x++, y);  // x is incremented twice, z and x are not what you expect

// no type checking: compiles but produces garbage
MAX("hello", 42)

// namespace pollution: every file that includes this header
// now has MAX redefined, possibly conflicting with other libraries
```

always wrap macro arguments in parentheses, and wrap the entire expression in an outer set of parentheses. but even then, you cannot fix the double evaluation problem without compiler extensions.

#### what macros are actually good for

macros can do things that functions cannot: they can capture the call site's file name and line number, generate code based on tokens, and conditionally compile entire sections.

##### compile-time constants and configuration

prefer `enum` for integer constants and `static const` for typed values. use `#define` only when you need the value available to the preprocessor itself (for `#if` checks):

```c
// Bad: untyped, no scope
#define MAX_USERS 1024

// Good: typed, scoped, debugger-visible
enum { MAX_USERS = 1024 };

// OK: needed for preprocessor conditionals
#define PLATFORM_LINUX 1
#if PLATFORM_LINUX
    // ...
#endif
```

##### debug wrappers with `__FILE__` and `__LINE__`

`__FILE__` and `__LINE__` are predefined macros that expand to the current source file and line number at the call site. functions cannot capture their caller's location — only macros can. this makes them essential for debugging infrastructure:

```c
void *debug_malloc(size_t size, const char *file, int line);
void *debug_realloc(void *ptr, size_t size, const char *file, int line);
void  debug_free(void *ptr, const char *file, int line);

#ifdef MEMORY_DEBUG
#define malloc(size)       debug_malloc(size, __FILE__, __LINE__)
#define realloc(ptr, size) debug_realloc(ptr, size, __FILE__, __LINE__)
#define free(ptr)          debug_free(ptr, __FILE__, __LINE__)
#endif
```

now every allocation in your codebase automatically records where it happened. when you detect a leak or a double-free, you know exactly which file and line allocated the memory. the caller's code does not change at all — they still write `malloc(n)`.

the same pattern works for any resource: file handles, locks, sockets. wrap the acquire/release functions with macros that inject the call site.

##### assert with context

the standard `assert` already uses `__FILE__` and `__LINE__`, but you can build a better one that logs more information:

```c
#define ASSERT(expr)                                                    \
    do {                                                                \
        if (!(expr)) {                                                  \
            fprintf(stderr, "ASSERT FAILED: %s [%s:%d]\n",             \
                    #expr, __FILE__, __LINE__);                         \
            abort();                                                    \
        }                                                               \
    } while (0)
```

the `#expr` stringifies the expression, so `ASSERT(x > 0)` prints `"ASSERT FAILED: x > 0 [main.c:42]"`. the `do { ... } while (0)` wrapper ensures the macro behaves like a single statement in all contexts (after `if`, in comma-separated expressions, etc.).

##### generic containers with macros

C has no templates, but macros can generate type-specific code. this is ugly but sometimes necessary for performance-critical containers where `void *` indirection is too costly:

```c
#define DEFINE_DYNAMIC_ARRAY(type, prefix)                              \
    typedef struct {                                                    \
        type   *data;                                                   \
        size_t  count;                                                  \
        size_t  capacity;                                               \
    } prefix##_array_t;                                                 \
                                                                        \
    prefix##_array_t prefix##_array_create(size_t cap) {                \
        prefix##_array_t arr = {0};                                     \
        arr.data = malloc(cap * sizeof(type));                          \
        arr.capacity = cap;                                             \
        return arr;                                                     \
    }                                                                   \
                                                                        \
    void prefix##_array_push(prefix##_array_t *arr, type value) {       \
        if (arr->count >= arr->capacity) {                              \
            arr->capacity *= 2;                                         \
            arr->data = realloc(arr->data, arr->capacity * sizeof(type)); \
        }                                                               \
        arr->data[arr->count++] = value;                                \
    }

DEFINE_DYNAMIC_ARRAY(int, int)
DEFINE_DYNAMIC_ARRAY(float, float)

// usage:
int_array_t nums = int_array_create(16);
int_array_push(&nums, 42);
```

this generates fully type-safe, inlineable code with no `void *` casting. the trade-off is that errors in the macro are nearly impossible to read, and debugging through macro-generated code is painful. use this sparingly and only when the performance gain over a `void *`-based container is measurable.

#### rules for writing macros

- always wrap arguments in parentheses: `((a) + (b))`, not `(a + b)`
- always wrap the full expression in outer parentheses
- use `do { ... } while (0)` for statement macros
- use `UPPER_CASE` names so they are visually distinct from functions
- never put semicolons at the end of a macro definition — the caller adds them
- prefer `static inline` functions when possible — they give you type checking, proper scoping, and debuggability


## Memory

everything in a running program lives in memory. if a variable exists, it exists at some address. if a function exists, its machine code sits at some address. there is nothing magical about any of it — memory is one large array of bytes, and every piece of data your program uses is a range of bytes within that array.

a pointer is an integer that holds the address of a byte. that is all it is. on a 64-bit system, a pointer is a 64-bit number. it does not "know" what it points to — the type system is a compile-time fiction that helps the compiler (and you) interpret the bytes correctly.

#### why pointers have types

if a pointer is just an address, why does the compiler care whether it is an `int *` or a `short *`? because the type tells the compiler how many bytes to read and how to interpret them when you dereference:

```c
void  *ptr;        // untyped: the compiler does not know how to dereference this

short *short_ptr;
int   *int_ptr;

short s = *short_ptr;  // reads 2 bytes, interprets as a signed 16-bit integer
int   i = *int_ptr;    // reads 4 bytes, interprets as a signed 32-bit integer
```

the address might be the same, but the result of dereferencing depends entirely on the type. this is why casting pointers carelessly is dangerous — you are telling the compiler to read a different number of bytes or interpret them as a different type, and if you are wrong, you get garbage or a crash.

#### the memory model

a C program sees memory as a flat address space divided into regions with different lifetimes:

```
┌─────────────────────┐ high addresses
│       stack         │ local variables, function arguments
│         ↓           │ grows downward, automatic lifetime
├─────────────────────┤
│                     │
│    (free space)     │
│                     │
├─────────────────────┤
│         ↑           │ grows upward, manual lifetime
│        heap         │ malloc/calloc/realloc
├─────────────────────┤
│   uninitialized     │ global/static variables initialized to zero
│      (BSS)          │
├─────────────────────┤
│    initialized      │ global/static variables with explicit values
│      (data)         │
├─────────────────────┤
│       text          │ machine code (read-only)
└─────────────────────┘ low addresses
```

understanding which region a piece of data lives in tells you its lifetime:
- **stack**: lives until the function returns. do not return pointers to stack variables
- **heap**: lives until you call `free`. you control the lifetime, you are responsible for it
- **data/BSS**: lives for the entire program. global and static variables
- **text**: the compiled code itself. read-only

most bugs involving memory come from confusing these lifetimes: returning a pointer to a stack variable (dangling pointer), forgetting to free heap memory (leak), or freeing it twice (double-free).

### Pointer Arithmetic

since a pointer is just an integer referencing a byte in memory, we can do math on it.
the key insight is that arithmetic on pointers is **scaled by the size of the type** the pointer points to.

```c
int arr[5] = {10, 20, 30, 40, 50};
int *p = arr;

p + 1   // moves forward by sizeof(int) bytes, not 1 byte
p + 2   // points to arr[2], moved 2 * sizeof(int) bytes forward
```

this is why pointer types matter: the compiler needs to know how far to jump.

```c
char *cp = (char *)arr;
int  *ip = arr;

cp + 1  // moves 1 byte forward
ip + 1  // moves 4 bytes forward (assuming sizeof(int) == 4)
```

array indexing is just pointer arithmetic in disguise:

```c
arr[i]      // is exactly the same as *(arr + i)
*(arr + 3)  // == arr[3] == 40
```

subtracting two pointers gives you the number of **elements** between them, not bytes:

```c
int *a = &arr[1];
int *b = &arr[4];
b - a   // == 3 (not 3 * sizeof(int))
```

**Rules:**
- you can add or subtract an integer to/from a pointer
- you can subtract two pointers of the same type
- you **cannot** add two pointers, multiply, or divide them
- pointer arithmetic is only defined within an array (or one past the end), going out of bounds is undefined behavior

### Structs

a struct is not an object. it is just a size and a set of offsets. the compiler takes your field declarations and turns them into: "the struct is N bytes total, field X starts at byte offset Y." that is all a struct is.

```c
typedef struct {
    unsigned long  tid;      // offset 0
    char           name[32]; // offset 8  (assuming 8-byte long)
    unsigned char  age;      // offset 40
} user_t;
```

accessing a field is just pointer arithmetic: take the base address of the struct, add the field's offset, interpret the bytes at that location as the field's type. `user.age` is really `*(unsigned char *)((char *)&user + offset_of_age)`.

#### offsetof

the standard way to get a field's offset is the `offsetof` macro from `<stddef.h>`:

```c
#include <stddef.h>

size_t off = offsetof(user_t, age);  // == 40 (on most 64-bit systems)
```

under the hood, many implementations do something like this:

```c
#define offsetof(type, member) (size_t)(&((type *)0)->member)
```

cast NULL to a pointer of the struct type, access the member, take its address — the result is the offset in bytes from the start of the struct.

#### Padding and alignment

the compiler may insert padding bytes between fields to satisfy alignment requirements. most hardware reads data faster (or only correctly) when values sit at addresses that are multiples of their size.

```c
typedef struct {
    char  a;    // 1 byte
                // 3 bytes padding
    int   b;    // 4 bytes, must be aligned to 4-byte boundary
    char  c;    // 1 byte
                // 3 bytes padding (so the struct size is a multiple of 4)
} padded_t;

// sizeof(padded_t) == 12, not 6
```

this is why you should not assume `sizeof(struct) == sum of sizeof(fields)`. if size matters, order your fields from largest to smallest to minimize padding:

```c
typedef struct {
    int   b;    // 4 bytes
    char  a;    // 1 byte
    char  c;    // 1 byte
                // 2 bytes padding
} compact_t;

// sizeof(compact_t) == 8, saved 4 bytes
```

#### Struct inheritance

once you understand that a struct is just offsets, you can do useful things. here is how to implement a form of inheritance in C:

```c
typedef enum {
    RECTANGLE,
    CIRCLE
} shape_type_t;

typedef struct {
    char         name[32];
    shape_type_t type;
} shape_t;

typedef struct {
    shape_t      header;
    unsigned int radius;
} circle_t;

typedef struct {
    shape_t      header;
    unsigned int width;
    unsigned int height;
} rectangle_t;
```

the trick: `header` is the first field in both `circle_t` and `rectangle_t`, so it sits at offset 0. a pointer to a `circle_t` and a pointer to its `header` field have the same address. this means you can safely cast between `shape_t *` and `circle_t *`:

```c
unsigned int calculate_area(shape_t *shape) {
    if (shape->type == CIRCLE) {
        circle_t *c = (circle_t *) shape;
        return 3.14 * c->radius * c->radius;
    } else if (shape->type == RECTANGLE) {
        rectangle_t *r = (rectangle_t *) shape;
        return r->width * r->height;
    }
    return 0;
}
```

this works because casting `shape` to `circle_t *` does not change the address. it just tells the compiler to interpret the bytes after the header as `circle_t`'s extra fields. the C standard guarantees that a pointer to a struct and a pointer to its first member have the same address.

this is the same pattern used throughout real C codebases: the Linux kernel (`struct list_head`), BSD sockets (`struct sockaddr`), and many others.

### Allocating Memory

C treats memory as what it actually is: a finite resource that you explicitly acquire and release. this is not a deficiency, it is a design choice.

languages that hide memory management behind garbage collectors give you convenience at the cost of control. you do not know when memory is freed, you cannot predict pauses, and you lose awareness of how much memory your program is actually using.

in C, every allocation is visible. every lifetime is explicit. this means more responsibility, but also more understanding. when something leaks, you can trace it. when something is freed too early, you can find it. there is no layer of abstraction between you and what the machine is doing.

#### What malloc actually does

`malloc` is not magic. you ask for N bytes, the system gives you a pointer to a contiguous block of at least N bytes, or `NULL` if it cannot. that's it. no initialization, no type information, no constructor. just raw bytes.

```c
void *malloc(size_t size);
```

it returns `void *` because `malloc` does not know or care what you are storing. you are responsible for knowing what lives there.

```c
int *p = malloc(sizeof *p);  // you get sizeof(int) bytes, they contain garbage
```

`free` is the reverse: you hand back the pointer, the system reclaims the bytes. there is no destructor, no cleanup. if the struct contains pointers to other allocations, you must free those first.

```c
void free(void *ptr);
```

#### sizeof

`sizeof` is not a function, it is part of the language. the compiler resolves it at compile time (except for VLAs).

```c
// Bad
double *a = malloc(sizeof(double)); // could go out of sync if the type of a changed

// Good
double *a;
a = malloc(sizeof *a); // type and allocation size are always in sync
```

always tie `sizeof` to the variable, not the type. if you change `double *a` to `float *a`, the good version stays correct automatically.

#### Allocating arrays

```c
int *arr = malloc(n * sizeof *arr);
```

beware of integer overflow: if `n` is large, `n * sizeof *arr` can wrap around to a small number, and you get a tiny allocation that you treat as a large array. `calloc` avoids this problem and also zero-initializes:

```c
int *arr = calloc(n, sizeof *arr);
// calloc checks for overflow internally
// all bytes are set to zero
```

use `calloc` when you want zero-initialized memory or when the multiplication could overflow. use `malloc` when you are going to immediately write all the data yourself.

#### Ownership and lifetime

every `malloc` needs a corresponding `free`. the question is: **who owns the memory?**

in C, ownership is a convention, not a language feature. you must decide and document it:

```c
// caller owns the returned memory, caller must free it
user_t *user_create(const char *name);

// takes ownership, frees the memory
void user_destroy(user_t *user);
```

rules to live by:
- whoever allocates should (usually) be responsible for freeing
- if a function returns allocated memory, document that the caller must free it
- if a function takes ownership of a pointer, document that the caller must not use it after
- never free memory you did not allocate
- never use memory after freeing it (use-after-free)
- never free the same pointer twice (double-free)

#### realloc pitfalls

`realloc` resizes an existing allocation. it may move the data to a new location and return a different pointer.

```c
// WRONG: if realloc fails, it returns NULL and you lose the original pointer
p = realloc(p, new_size);

// RIGHT: use a temporary
void *tmp = realloc(p, new_size);
if (tmp == NULL) {
    // handle error, p is still valid
} else {
    p = tmp;
}
```

also: after `realloc`, any other pointers into the old block are invalid, because the data may have moved.

#### Arena allocation

`malloc` and `free` pair well for objects with independent lifetimes. but many real programs allocate a batch of things, use them together, and discard them all at once. for this pattern, an arena (bump allocator) is simpler and faster:

```c
typedef struct {
    char   *buf;
    size_t  size;
    size_t  offset;
} arena_t;

arena_t arena_create(size_t size) {
    arena_t a;
    a.buf    = malloc(size);
    a.size   = size;
    a.offset = 0;
    return a;
}

void *arena_alloc(arena_t *a, size_t bytes) {
    if (a->offset + bytes > a->size) return NULL;
    void *ptr = a->buf + a->offset;
    a->offset += bytes;
    return ptr;
}

// free everything at once, no need to track individual allocations
void arena_destroy(arena_t *a) {
    free(a->buf);
}
```

the idea: allocate one big block up front, hand out pieces of it by bumping a pointer forward. when you are done, free the entire block. no per-object bookkeeping, no fragmentation, no forgetting to free something.

this is how many game engines, compilers, and web servers manage memory for request-scoped or frame-scoped work.

### What Actually Happens When You Access Memory

so far we have talked about memory from the program's perspective: stack, heap, malloc, free. but there is a deeper layer. your program does not touch physical RAM directly — there is hardware and an entire operating system between you and the actual bytes. understanding this layer changes how you think about every data structure and every allocation strategy.

#### memory is virtualized

every process gets its own virtual address space. when your code dereferences a pointer, the address is not a physical location in RAM — it is a virtual address. the CPU's memory management unit (MMU) translates it to a physical address on every single access, using a **page table** managed by the OS.

the virtual address space is divided into **pages** (typically 4 KB on x86). physical memory is divided into **frames** of the same size. the page table maps each virtual page to a physical frame:

```
  virtual address space                physical memory
  ┌──────────────┐                   ┌──────────────┐
  │   page 0     │ ─────────────────▶│   frame 7    │
  ├──────────────┤                   ├──────────────┤
  │   page 1     │ ──────────┐      │   frame 1    │
  ├──────────────┤           │      ├──────────────┤
  │   page 2     │ ───┐      │      │   frame 4    │
  ├──────────────┤    │      │      ├──────────────┤
  │   page 3     │    │      └─────▶│   frame 3    │
  ├──────────────┤    │              ├──────────────┤
  │     ...      │    └────────────▶│   frame 9    │
  └──────────────┘                   └──────────────┘
```

the important thing: pages do not need to be contiguous in physical memory. the OS can scatter them across physical frames and the program never knows — it sees a flat, contiguous address space. this virtualization has consequences we will come back to.

#### but memory access is slow

the translation from virtual to physical is not the bottleneck — the MMU handles that in hardware with a TLB (translation lookaside buffer) cache. the real problem is what happens after translation: actually reading the bytes from RAM.

modern CPUs do not read from main memory directly. they read from a hierarchy of caches, each one smaller and faster than the one below it:

```
  ┌────────────────────────────────────┐
  │           registers                │  ~0 cycles      (~0.3 ns)
  │           (few KB)                 │
  ├────────────────────────────────────┤
  │          L1 cache                  │  ~3-4 cycles    (~1 ns)
  │       (32-64 KB per core)          │
  ├────────────────────────────────────┤
  │          L2 cache                  │  ~7-14 cycles   (~3-5 ns)
  │       (256 KB - 1 MB per core)     │
  ├────────────────────────────────────┤
  │          L3 cache                  │  ~30-50 cycles  (~10-20 ns)
  │       (8-64 MB shared)             │
  ├────────────────────────────────────┤
  │        main memory (DRAM)          │  ~100-300 cycles (~50-100 ns)
  │        (8-128 GB)                  │
  ├────────────────────────────────────┤
  │         SSD / disk                 │  ~10,000 - 10,000,000 cycles
  │         (TB)                       │
  └────────────────────────────────────┘
```

the gap between L1 cache and main memory is roughly **100×**. that is not a small difference — it is the difference between a function running at full speed and one that stalls on every memory access.

to put it in perspective: an integer addition takes about 1 cycle. a floating-point multiply takes about 3-5 cycles. an L1 cache hit takes 3-4 cycles. a main memory access takes 100+ cycles. **math is effectively free compared to a cache miss.** when you are optimizing a program, you are almost always optimizing for memory access patterns — not for fewer instructions.

> The purpose of all programs, and all parts of those programs, is to transform data from one form to
> another. If you don't understand the data, you don't understand the problem.
>
> There is no loaded gun loaded more loaded than a loaded cache miss.
>
> — Mike Acton, "Data-Oriented Design and C++", CppCon 2014

#### cache lines: the unit of transfer

when the CPU reads an address, it does not fetch just the bytes you asked for. it fetches an entire **cache line** — typically 64 bytes on x86. this line is stored in L1, and the next access to any byte within that line is a cache hit:

```
  memory:
  ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
  │ a0 │ a1 │ a2 │ a3 │ a4 │ a5 │ a6 │ a7 │ a8 │ a9 │ a10│ a11│ a12│ a13│ a14│ a15│
  └────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┘
  ◄────────────────────── 64-byte cache line ──────────────────────►

  you access a0 → the CPU loads a0 through a15 into L1 cache
  you access a1 → cache hit (already in L1)
  you access a2 → cache hit
  ...
  you access a15 → cache hit
  you access a16 → cache miss, new cache line loaded
```

this means **sequential access patterns are fast** — each cache miss loads 64 bytes of useful data. random access patterns are slow — each access loads 64 bytes but you only use a few before jumping elsewhere.

the CPU also has a **hardware prefetcher** that detects sequential access patterns and starts loading the next cache lines before you even ask for them. by the time your loop reaches the next cache line, it is already in L1. this makes sequential iteration over contiguous data even faster in practice than the raw latency numbers suggest.

all of this — the cache hierarchy, cache lines, the prefetcher — has a direct consequence for how you should choose and organize your data structures.

#### data locality: why arrays beat linked lists

consider two ways to store a collection of integers: a contiguous array and a linked list.

**arrays** lay elements next to each other in memory:

```c
int *arr = malloc(n * sizeof *arr);
for (int i = 0; i < n; i++) {
    arr[i] = i;
}

int sum = 0;
for (int i = 0; i < n; i++) {
    sum += arr[i];
}
```

```
  cache line 0                        cache line 1
  ┌───┬───┬───┬───┬───┬───┬───┬───┐  ┌───┬───┬───┬───┬───┬───┬───┬───┐
  │ 0 │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │  │ 8 │ 9 │10 │11 │12 │13 │14 │15 │  ...
  └───┴───┴───┴───┴───┴───┴───┴───┘  └───┴───┴───┴───┴───┴───┴───┴───┘
       (16 ints per 64-byte cache line, assuming 4-byte int)
```

reading `arr[0]` loads the first cache line: elements 0 through 15 are now in L1. the next 15 accesses are all hits. the prefetcher runs ahead loading future cache lines. for N elements, you get roughly N / 16 cache misses, and the prefetcher hides most of that latency.

**linked lists** scatter nodes across the heap:

```c
typedef struct Node {
    int          data;
    struct Node *next;
} node_t;

int sum = 0;
for (node_t *n = head; n != NULL; n = n->next) {
    sum += n->data;
}
```

```
  heap memory:

  addr 0x100           addr 0x500           addr 0x230
  ┌────────────┐       ┌────────────┐       ┌────────────┐
  │ data: 0    │       │ data: 1    │       │ data: 2    │
  │ next: 0x500│──────▶│ next: 0x230│──────▶│ next: ...  │──▶ ...
  └────────────┘       └────────────┘       └────────────┘

  cache line at 0x0C0          cache line at 0x4C0          cache line at 0x200
  ┌──────────────────────┐     ┌──────────────────────┐     ┌──────────────────────┐
  │ node A + 48B wasted  │     │ node B + 48B wasted  │     │ node C + 48B wasted  │
  └──────────────────────┘     └──────────────────────┘     └──────────────────────┘
```

each `node_t` is 16 bytes (4 bytes data + 4 bytes padding + 8 bytes pointer on 64-bit). but each access loads a 64-byte cache line — you use 16 bytes and waste 48. every `n = n->next` is a **pointer chase** into a random memory location, which is almost always a cache miss. the prefetcher cannot help because it cannot predict where `next` points — the pattern looks random from the hardware's perspective.

the numbers tell the story. for iterating over 1,000,000 integers:

```
  array (sequential access):
      cache misses:   1,000,000 / 16 = 62,500
      effective cost:  62,500 × ~5 cycles (prefetcher hides most latency)
                     ≈ 312,500 cycles

  linked list (pointer chasing):
      cache misses:   ~1,000,000 (each node likely on a different cache line)
      effective cost:  1,000,000 × ~100 cycles
                     ≈ 100,000,000 cycles

  ratio: the linked list is roughly 300× slower for pure iteration
```

these are approximate, but the order of magnitude is real. Bjarne Stroustrup demonstrated this empirically in [*"Why you should avoid Linked Lists"*](https://www.youtube.com/watch?v=YQs6IC-vgmo) — even for insertion in the middle, a dynamic array with `memmove` beats a linked list for sizes up to tens of thousands of elements. the reason is counterintuitive: shifting contiguous data in cache is cheap because it is a sequential operation that the prefetcher handles well, while walking a linked list to find the insertion point requires random memory accesses that stall the CPU:

```c
// shifting thousands of elements in a contiguous array — a streaming
// sequential operation that the prefetcher handles efficiently
memmove(&arr[pos + 1], &arr[pos], (count - pos) * sizeof *arr);
arr[pos] = value;
```

#### realloc revisited

now we can circle back to `realloc` with a better understanding. people avoid dynamic arrays because they fear that growing them with `realloc` is expensive. but remember: memory is virtualized.

for large allocations backed by `mmap`, the OS can use `mremap()` (on Linux) to grow the allocation by remapping virtual pages — no data is copied at all. the kernel just updates the page table:

```
  before realloc (4 pages):

  virtual                physical
  ┌──────────┐         ┌──────────┐
  │  page 0  │ ───────▶│ frame 12 │
  ├──────────┤         ├──────────┤
  │  page 1  │ ───────▶│ frame 13 │
  ├──────────┤         ├──────────┤
  │  page 2  │ ───────▶│ frame 14 │
  ├──────────┤         ├──────────┤
  │  page 3  │ ───────▶│ frame 15 │
  └──────────┘         └──────────┘

  after realloc to 8 pages (via mremap):

  virtual                physical
  ┌──────────┐         ┌──────────┐
  │  page 0  │ ───────▶│ frame 12 │  ← same data, no copy
  ├──────────┤         ├──────────┤
  │  page 1  │ ───────▶│ frame 13 │  ← same data, no copy
  ├──────────┤         ├──────────┤
  │  page 2  │ ───────▶│ frame 14 │  ← same data, no copy
  ├──────────┤         ├──────────┤
  │  page 3  │ ───────▶│ frame 15 │  ← same data, no copy
  ├──────────┤         ├──────────┤
  │  page 4  │ ───────▶│ frame 20 │  ← new page
  ├──────────┤         ├──────────┤
  │  page 5  │ ───────▶│ frame 21 │  ← new page
  ├──────────┤         ├──────────┤
  │  page 6  │ ───────▶│ frame 22 │  ← new page
  ├──────────┤         ├──────────┤
  │  page 7  │ ───────▶│ frame 23 │  ← new page
  └──────────┘         └──────────┘
```

no bytes were copied. the OS just assigned new physical frames to the new virtual pages and updated the page table. this is an O(1) operation regardless of how much data you have. even for smaller allocations, `realloc` can often extend the block in place if there is free space adjacent to it.

with geometric growth (doubling the capacity), `realloc` is called only O(log N) times for N insertions, and the amortized cost per element is O(1). this makes the dynamic array the best default collection: cheap to grow, cache-friendly to iterate, and simple to reason about.

```c
typedef struct {
    int    *data;
    size_t  count;
    size_t  capacity;
} int_array_t;

int_array_t int_array_create(size_t initial_capacity) {
    int_array_t arr = {0};
    arr.data     = malloc(initial_capacity * sizeof *arr.data);
    arr.capacity = initial_capacity;
    return arr;
}

int int_array_push(int_array_t *arr, int value) {
    if (arr->count >= arr->capacity) {
        size_t new_cap = arr->capacity * 2;
        void *tmp = realloc(arr->data, new_cap * sizeof *arr->data);
        if (!tmp) return -1;
        arr->data     = tmp;
        arr->capacity = new_cap;
    }
    arr->data[arr->count++] = value;
    return 0;
}

void int_array_destroy(int_array_t *arr) {
    free(arr->data);
}
```

#### when linked lists actually make sense

linked lists are not useless. they have legitimate use cases:

- **O(1) splice at a known position**: if you already have a pointer to a node and need to insert or remove next to it, a linked list does this without moving any other data. this matters for LRU caches, free lists inside allocators, and scheduler queues
- **intrusive lists**: the Linux kernel's `struct list_head` pattern embeds the list node inside the data struct itself. no separate allocation per node, and a node can live on multiple lists simultaneously
- **you never iterate the whole list**: if you only access the head or tail (a queue, a stack), the sequential access argument is weaker

but if your primary operation is "iterate over all elements" or "access by index," use an array. always.

#### references

- Ulrich Drepper, [*What Every Programmer Should Know About Memory*](https://people.freebsd.org/~lstewart/articles/cpumemory.pdf) (2007) — the definitive reference on memory hierarchy, caches, and writing cache-friendly code
- Mike Acton, [*Data-Oriented Design and C++*](https://www.youtube.com/watch?v=rX0ItVEVjHc), CppCon 2014 — the talk that made a generation of C++ programmers think about cache lines
- Bjarne Stroustrup, [*Why you should avoid Linked Lists*](https://www.youtube.com/watch?v=YQs6IC-vgmo) — empirical demonstration that vector beats list even for insertion-heavy workloads
- Chandler Carruth, [*Efficiency with Algorithms, Performance with Data Structures*](https://www.youtube.com/watch?v=fHNmRkzxHWs), CppCon 2014 — practical guidance on choosing data structures for cache performance
- [Intel 64 and IA-32 Architectures Optimization Reference Manual](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html) — hardware-level details on cache hierarchy and prefetching
