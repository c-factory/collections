[Collections](../collections.md) &rarr; [Tree Map](tree_map.md) &rarr;

# remove_pair_from_tree_map

```c
    void * remove_pair_from_tree_map(tree_map_t *iface, void *key);
```

Removes a pair by its key from a tree map.\
Returns a value if a pair was removed (before exists in the map), otherwise `NULL`. If needed, this value can be freed using the returned pointer.

## Parameters

Argument|Description
--------|-----------
iface|Pointer to a `tree_map_t` interface
key|A key

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
        printf("The size of the map is %d items\n", map->size);
        remove_pair_from_tree_map(map, "two");
        remove_pair_from_tree_map(map, "five");
        printf("Now, the size is %d items\n", map->size);
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

    The size of the map is 5 items
    Now, the size is 4 items
    four -> 4
    one -> 1
    three -> 3
    zero -> 0
