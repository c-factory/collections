[Collections](../collections.md) &rarr;

# Allocators

The collection library supports the concept of flexible memory management through the use of different allocators.\
The allocator is the interface that allocates and frees memory blocks.

A programmer can implement a custom allocator that is better suited for specific purposes.

## Include

The file `allocator.h` contains all definitions.

## Data types

```c
    typedef struct
    {
        void *(*allocate)(size_t);
        void (*release)(void*, size_t);
    } allocator_t;
```

### allocator_t

The `allocator_t` struct contains 2 function pointers:

* **allocate** - a function that allocates a memory block of the specified size. This function never returns NULL, that is either function allocates a block or an application aborts. Thus, not needed to check the return value after allocation;
* **release** - a function that releases a memory block. Parameters are the address of a memory block and the size of a memory block.

## Functions

* **[nnalloc](nnalloc.md)** - allocates a block of memory, returning a pointer to the beginning of the block, but never returns `NULL`;
* **[get_system_allocator](get_system_allocator.md)** - returns the system ("standard") allocator, i.e. wrapper for the library functions `malloc` and `free`.

## Creating custom allocator

```c
    #include "allocator.h"

    static void * custom_allocate(size_t size)
    {
        // ...kind of magic
    }

    static void custom_release(void *ptr, size_t size)
    {
        // ...another kind of magic
    }

    allocator_t custom_allocator =
    {
        custom_allocate,
        custom_release
    };
```
