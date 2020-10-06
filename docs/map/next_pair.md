[Collections](../collections.md) &rarr; [Map](map.md) &rarr; [Map Iterator](map_iterator.md) &rarr; 

# next_pair

```c
    const pair_t * next_pair(map_iterator_t *iface);
```

Returns the next pair from a map iterator, or `NULL`, if an iterator is empty.

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
        while(has_next_pair(iter))
        {
            const pair_t *pair = next_pair(iter); // here we take the next pair
            printf("%s -> %s\n", pair->key, pair->value);
        }
        destroy_map_iterator(iter);
        destroy_tree_map(map);
        return 0;
    }
```
