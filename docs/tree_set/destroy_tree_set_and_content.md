[Collections](../collections.md) &rarr; [Tree Set](tree_set.md) &rarr;

# destroy_tree_set_and_content

```c
    void destroy_tree_set_and_content(tree_set_t *iface, void (*destructor)(void *));
```

Destructs the tree set and also its data using a destructor.

## Parameters

Argument|Description
--------|-----------
iface|Pointer to a `tree_set_t` interface
destructor|Destructor that will destroy each item

Destructor takes one argument (pointer to data). For example, as a destructor, the `free` library function can be used, for items, created by the `malloc` function. For complex structs, a programmer has to implement appropriate destructors.

## Example

```c
    #include "tree_set.h"
    #include <stdio.h>
    #include <string.h>

    int main()
    {
        tree_set_t *s = create_tree_set((void*)strcmp);
        add_item_to_tree_set(s, strdup("zero")); // 'strdup' allocates memory for strings
        add_item_to_tree_set(s, strdup("one"));
        add_item_to_tree_set(s, strdup("two"));
        add_item_to_tree_set(s, strdup("three"));
        iterator_t *i = create_iterator_from_tree_set(s);
        while (has_next_item(i))
        {
            printf("%s\n", next_item(i));
        }
        destroy_iterator(i);
        destroy_tree_set_and_content(s, free); /* here, the stdlib 'free' method is used
                                                for strings deallocation */
        return 0;
    }
```

Output:

    one
    three
    two
    zero
