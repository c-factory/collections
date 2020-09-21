[Collections](../collections.md) &rarr; [Tree Set](tree_set.md) &rarr;

# create_tree_set

```c
    tree_set_t * create_tree_set(int (*comparator)(void*, void*));
```

Returns a new empty set. Never returns `NULL`.

The created set after using must be freed by the [`destroy_tree_set`](destroy_tree_set.md) (or the [`destroy_tree_set_and_content`](destroy_tree_set_and_content.md)) function.

## Parameters

Argument|Description
--------|-----------
comparator|A function that [compares](../comparator.md) two elements

## Example

Creation a tree set that contains C strings:

```c
    #include "tree_set.h"
    #include <string.h>

    int main()
    {
        tree_set_t *s = create_tree_set((void*)strcmp);
        // ...
        destroy_tree_set(s);
        return 0;
    }
```
