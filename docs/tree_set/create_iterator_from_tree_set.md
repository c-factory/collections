[Collections](../collections.md) &rarr; [Tree Set](tree_set.md) &rarr;

# create_iterator_from_tree_set

```c
    iterator_t * create_iterator_from_tree_set(tree_set_t *iface);
```

Returns an [iterator](../iterator/iterator.md), created from a tree set.

## Parameters

Argument|Description
--------|-----------
iface|Pointer to a `tree_set_t` interface

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
        iterator_t *i = create_iterator_from_tree_set(s); // create an iterator
        while (has_next_item(i))
        {
            printf("%s\n", next_item(i));
        }
        destroy_iterator(i); // don't forget to destroy it!
        destroy_tree_set(s);
        return 0;
    }
```

Output:

    one
    three
    two
    zero
