[Collections](../collections.md) &rarr; [Vector](vector.md) &rarr;

# create_vector_ext

```c
    vector_t * create_vector_ext(const allocator_t *allocator, size_t init_capacity);
```

Creates an empty vector with initial capacity using a specified memory allocator. Never returns `NULL`.

The created vector after using must be freed by the [`destroy_vector`](destroy_vector.md) (or the [`destroy_vector_and_content`](destroy_vector_and_content.md)) function.

## Parameters

Argument|Description
--------|-----------
allocator|Pointer to a memory allocator
init_capacity|Initial vector capacity, i.e. number of items that can be added without memory reallocation

The system ("standard") allocator is returned by the [`get_system_allocator`](../allocator/get_system_allocator.md) function.

## Example

```c
    #include "vector.h"

    int main()
    {
        vector_t *v = create_vector_ext(get_system_allocator(), 1024);
        // ...
        destroy_vector(v);
        return 0;
    }
```
