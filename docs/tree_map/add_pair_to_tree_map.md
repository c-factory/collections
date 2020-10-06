[Collections](../collections.md) &rarr; [Tree Map](tree_map.md) &rarr;

# add_pair_to_tree_map

```c
    void * add_pair_to_tree_map(tree_map_t *iface, void *key, void *value);
```

Adds a pair to a map.\
Returns an old value if pair with the same key was present in the map before.

## Parameters

Argument|Description
--------|-----------
iface|Pointer to a `tree_map_t` interface
key|A key
value|A value

## Complexity

O(log<sub>2</sub>N)

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
            const pair_t *pair = next_pair(iter);
            printf("%s -> %s\n", pair->key, pair->value);
        }
        destroy_map_iterator(iter);
        destroy_tree_map(map);
        return 0;
    }
```

Output:

    four -> 4
    one -> 1
    three -> 3
    two -> 2
    zero -> 0
