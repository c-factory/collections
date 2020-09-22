[Collections](../collections.md) &rarr; [Tree Set](tree_set.md) &rarr;

# remove_item_from_tree_set

```c
    bool remove_item_from_tree_set(tree_set_t *iface, void *item);
```

Removes an item from a tree set.\
Returns `TRUE` if an item was removed (before exists in the set), otherwise `FALSE`.

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
        printf("The size of the set is %d items\n", s->size);
        remove_item_from_tree_set(s, "one");
        remove_item_from_tree_set(s, "zero");
        printf("Now, the size is %d items\n", s->size);
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

    The size of the set is 4 items
    Now, the size is 2 items
    three
    two
