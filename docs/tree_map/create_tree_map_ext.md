[Collections](../collections.md) &rarr; [Tree Map](tree_map.md) &rarr;

# create_tree_map_ext

```c
    tree_map_t * create_tree_map_ext(int (*comparator)(void*, void*), const allocator_t *allocator);
```

Creates an empty tree map using a specified (memory allocator)[../allocator/allocator.md]. Never returns `NULL`.

The created map after using must be freed by the [`destroy_tree_map`](destroy_tree_map.md) (or the [`destroy_tree_map_and_content`](destroy_tree_map_and_content.md)) function.

## Parameters

Argument|Description
--------|-----------
comparator|A function that [compares](../comparator.md) two elements
allocator|Pointer to a memory allocator

## Example

Creation a tree map in which keys are C strings:

```c
    #include "tree_map.h"
    #include <string.h>

    allocator_t custom_allocator = 
    {
        // ...
    };

    int main(void)
    {
        tree_map_t *map = create_tree_map_ext((void*)strcmp, &custom_allocator);
        // ...
        destroy_tree_map(map);
        return 0;
    }
```
