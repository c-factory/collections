[Collections](../collections.md) &rarr; [Tree Map](tree_map.md) &rarr;

# create_iterator_from_tree_map

```c
    map_iterator_t * create_iterator_from_tree_map(tree_map_t *iface);
```

Returns an [iterator](../iterator/iterator.md), created from a tree map.\
Because the tree map structure is built on a balanced binary tree, the iterator will traverse the tree in ascending order of keys.

## Parameters

Argument|Description
--------|-----------
iface|Pointer to a `tree_map_t` interface

## Example

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
