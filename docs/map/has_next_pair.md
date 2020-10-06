[Collections](../collections.md) &rarr; [Map](map.md) &rarr; [Map Iterator](map_iterator.md) &rarr; 

# has_next_pair

```c
    bool has_next_pair(map_iterator_t *iface);
```

Checks if there are more pairs in a map iterator.

## Parameters

Argument|Description
--------|-----------
iface|Pointer to a `map_iterator_t` interface

## Example

```c
    #include "tree_map.h"
    #include <string.h>
    #include <stdio.h>

    int main(void)
    {
        tree_map_t *map = create_tree_map((void*)strcmp);
        add_pair_to_tree_map(map, "zero", "0");
        add_pair_to_tree_map(map, "one", "1");
        add_pair_to_tree_map(map, "two", "2");
        add_pair_to_tree_map(map, "three", "3");
        add_pair_to_tree_map(map, "four", "4");
        map_iterator_t *iter = create_iterator_from_tree_map(map);
        while(has_next_pair(iter)) // here we check if there is another pair
        {
            const pair_t *pair = next_pair(iter);
            printf("%s -> %s\n", pair->key, pair->value);
        }
        destroy_map_iterator(iter);
        destroy_tree_map(map);
        return 0;
    }
```
