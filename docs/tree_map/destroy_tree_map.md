[Collections](../collections.md) &rarr; [Tree Map](tree_map.md) &rarr;

# destroy_tree_map

```c
    void destroy_tree_map(tree_map_t *iface);
```

Destructs the tree map itself, but does not destruct the map data.

## Parameters

Argument|Description
--------|-----------
iface|Pointer to a `tree_map_t` interface

## Example

```c
    #include "tree_map.h"
    #include <string.h>

    int main()
    {
        tree_map_t *m = create_tree_map((void*)strcmp);
        // ...
        destroy_tree_map(m);
        return 0;
    }
```
