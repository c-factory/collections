[Collections](../collections.md) &rarr; [Tree Map](tree_map.md) &rarr;

# destroy_tree_map_and_content

```c
    void destroy_tree_map_and_content(tree_map_t *iface,
            void (*key_destructor)(void *), void (*value_destructor)(void *));
```

Destructs the tree map and also its data using a destructor.

## Parameters

Argument|Description
--------|-----------
iface|Pointer to a `tree_map_t` interface
key_destructor|Destructor that will destroy each key (can be `NULL`)
value_destructor|Destructor that will destroy each value (can be `NULL`)

Destructor takes one argument (pointer to data). For example, as a destructor, the `free` library function can be used, for items, created by the `malloc` function. For complex structs, a programmer has to implement appropriate destructors.

## Example

```c
    #include "tree_map.h"
    #include <string.h>
    #include <stdio.h>

    int main(void)
    {
        tree_map_t *map = create_tree_map((void*)strcmp);
        add_pair_to_tree_map(map, strdup("zero"), strdup("0")); // 'strdup' allocates memory for strings
        add_pair_to_tree_map(map, strdup("one"), strdup("1"));
        add_pair_to_tree_map(map, strdup("two"), strdup("2"));
        add_pair_to_tree_map(map, strdup("three"), strdup("3"));
        add_pair_to_tree_map(map, strdup("four"), strdup("4"));
        map_iterator_t *iter = create_iterator_from_tree_map(map);
        while(has_next_pair(iter))
        {
            const pair_t *pair = get_pair_from_tree_map(map, next_pair(iter)->key);
            printf("%s -> %s\n", pair->key, pair->value);
        }
        destroy_map_iterator(iter);
        destroy_tree_map_and_content(map, free, free); /* here, the stdlib 'free' method is used
                                                        for strings deallocation */
        return 0;
    }

```
Output:

    four -> 4
    one -> 1
    three -> 3
    two -> 2
    zero -> 0
