[Collections](../collections.md) &rarr; [Tree Map](tree_map.md) &rarr;

# traverse_over_tree_map

```c
    void traverse_over_tree_map(tree_map_t *iface, void (*callback)(void*, pair_t*), void* obj);
```

Traverses over a map and calls a callback, without iterator creation.\
Because the tree map structure is built on a balanced binary tree, the function will traverse the tree in ascending order of keys.

## Parameters

Argument|Description
--------|-----------
iface|Pointer to a `tree_map_t` interface
callback|A callback that takes two arguments: first is any pointer, and second is a pair of a map
obj|An object that will pass as the first argument

## Example

```c
    #include "tree_map.h"
    #include <stdio.h>
    #include <string.h>

    void print(const char* key, const char *value) // the function as an object
    {
        printf("%s -> %s\n", key, value);
    }

    void callback(void *obj, pair_t *pair)
    {
        void (*fn)(const char*, const char*) = obj;
        fn(pair->key, pair->value);
    }

    int main()
    {
        tree_map_t *map = create_tree_map((void*)strcmp);
        add_pair_to_tree_map(map, "zero", "0");
        add_pair_to_tree_map(map, "one", "1");
        add_pair_to_tree_map(map, "two", "2");
        add_pair_to_tree_map(map, "three", "3");
        traverse_over_tree_map(map, callback, print);
        destroy_tree_map(map);
        return 0;
    }
```

Output:

    one -> 1
    three -> 3
    two -> 2
    zero -> 0
