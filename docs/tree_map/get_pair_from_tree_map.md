[Collections](../collections.md) &rarr; [Tree Map](tree_map.md) &rarr;

# get_pair_from_tree_map

```c
    const pair_t * get_pair_from_tree_map(tree_map_t *iface, void *key);
```

Returns a [pair](../map/pair.md) by key from a tree map.

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
    #include <stdio.h>
    #include <string.h>

    void check(tree_map_t *map, char *key)
    {
        const pair_t *pair = get_pair_from_tree_map(map, key);
        if (pair)
            printf("The pair '%s' -> '%s' exists in the map.\n", pair->key, pair->value);
        else
            printf("The pair with the key '%s' was not found in the map.\n", key);
    }

    int main()
    {
        tree_map_t *map = create_tree_map((void*)strcmp);
        add_pair_to_tree_map(map, "zero", "0");
        add_pair_to_tree_map(map, "one", "1");
        add_pair_to_tree_map(map, "two", "2");
        add_pair_to_tree_map(map, "three", "3");
        check(map, "one");
        check(map, "five");
        destroy_tree_map(map);
        return 0;
    }
```

Output:

    The pair 'one' -> '1' exists in the map.
    The pair with the key 'five' was not found in the map.
