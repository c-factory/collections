[Collections](../collections.md) &rarr; [Tree Set](tree_set.md) &rarr;

# create_tree_set_ext

```c
    tree_set_t * create_tree_set_ext(int (*comparator)(void*, void*), const allocator_t *allocator);
```

Creates an empty tree set using a specified (memory allocator)[../allocator/allocator.md]. Never returns `NULL`.

The created set after using must be freed by the [`destroy_tree_set`](destroy_tree_set.md) (or the [`destroy_tree_set_and_content`](destroy_tree_set_and_content.md)) function.

## Parameters

Argument|Description
--------|-----------
comparator|A function that [compares](../comparator.md) two elements
allocator|Pointer to a memory allocator

## Example

Creation a tree set that contains C strings:

```c
    #include "tree_set.h"
    #include <string.h>

    allocator_t custom_allocator = 
    {
        // ...
    };

    int main()
    {
        tree_set_t *s = create_tree_set_ext((void*)strcmp, &custom_allocator);
        // ...
        destroy_tree_set(s);
        return 0;
    }
```
