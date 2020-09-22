[Collections](../collections.md) &rarr; [Tree Set](tree_set.md) &rarr;

# add_item_to_tree_set

```c
    bool add_item_to_tree_set(tree_set_t *iface, void *item);
```

Adds an item to a set.\
Returns `TRUE` if an item was added (before was not exists in the set), otherwise `FALSE`.

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

    int main()
    {
        tree_set_t *s = create_tree_set((void*)strcmp);
        add_item_to_tree_set(s, "zero");
        add_item_to_tree_set(s, "one");
        add_item_to_tree_set(s, "two");
        add_item_to_tree_set(s, "three");
        add_item_to_tree_set(s, "one");
        add_item_to_tree_set(s, "zero");
        iterator_t *i = create_iterator_from_tree_set(s);
        while (has_next_item(i))
        {
            printf("%s\n", next_item(i));
        }
        destroy_iterator(i);
        destroy_tree_set(s);
        return 0;
    }
```

Output:

    one
    three
    two
    zero
