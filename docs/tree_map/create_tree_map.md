[Collections](../collections.md) &rarr; [Tree Map](tree_map.md) &rarr;

# create_tree_map

```c
    tree_map_t * create_tree_map(int (*comparator)(void*, void*));
```

Returns a new empty map. Never returns `NULL`.

The created map after using must be freed by the [`destroy_tree_map`](destroy_tree_map.md) (or the [`destroy_tree_map_and_content`](destroy_tree_map_and_content.md)) function.

## Parameters

Argument|Description
--------|-----------
comparator|A function that [compares](../comparator.md) two elements

## Example

Creation a tree map in which keys are C strings:

```c
#include "tree_map.h"
#include <string.h>

int main(void)
{
    tree_map_t *map = create_tree_map((void*)strcmp);
    // ...
    destroy_tree_map(map);
    return 0;
}

```
