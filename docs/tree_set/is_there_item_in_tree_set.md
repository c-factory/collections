[Collections](../collections.md) &rarr; [Tree Set](tree_set.md) &rarr;

# is_there_item_in_tree_set

```c
    bool is_there_item_in_tree_set(tree_set_t *iface, void *item);
```

Checks if there is an item in a tree set.

## Parameters

Argument|Description
--------|-----------
iface|Pointer to a `tree_set_t` interface
item|An item

## Complexity

O(log<sub>2</sub>N)

## Example

```c
    #include "tree_set.h"
    #include <stdio.h>
    #include <string.h>

    void check(tree_set_t *set, char *item)
    {
        bool result = is_there_item_in_tree_set(set, item);
        if (result)
            printf("The item '%s' exists in the set.\n", item);
        else
            printf("The item '%s' was not found in the set.\n", item);
    }

    int main()
    {
        tree_set_t *set = create_tree_set((void*)strcmp);
        add_item_to_tree_set(set, "zero");
        add_item_to_tree_set(set, "one");
        add_item_to_tree_set(set, "two");
        add_item_to_tree_set(set, "three");
        check(set, "one");
        check(set, "five");
        destroy_tree_set(set);
        return 0;
    }

```

Output:

    The item 'one' exists in the set.
    The item 'five' was not found in the set.
