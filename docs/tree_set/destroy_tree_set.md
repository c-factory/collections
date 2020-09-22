[Collections](../collections.md) &rarr; [Tree Set](tree_set.md) &rarr;

# destroy_tree_set

```c
    void destroy_tree_set(tree_set_t *iface);
```

Destructs the tree set itself, but does not destruct the set data.

## Parameters

Argument|Description
--------|-----------
iface|Pointer to a `tree_set_t` interface

## Example

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
