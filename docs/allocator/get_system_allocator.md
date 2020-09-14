[Collections](../collections.md) &rarr; [Allocators](allocator.md) &rarr;

# get_system_allocator

```c
    const allocator_t * get_system_allocator();
```

Returns the system ("standard") allocator. This is a wrapper for the library functions `malloc` and `free`.

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
