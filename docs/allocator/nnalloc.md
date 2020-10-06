[Collections](../collections.md) &rarr; [Allocators](allocator.md) &rarr;

# nnalloc

```c
    void * nnalloc(size_t size);
```

Means "Not Null Allocator". Allocates a block of `size` bytes of memory, returning a pointer to the beginning of the block, but never returns `NULL`. If memory is full, terminates application. This is a wrapper for the library function `malloc`.

## Examples

```c
    #include "allocator.h"

    int main()
    {
        char *s = nnalloc(1024);
        // ...
        free(s);
        return 0;
    }
```
