[Collections](../collections.md) &rarr; [Vector](vector.md) &rarr;

# index_of_item_of_vector

```c
    vector_index_t index_of_item_of_vector(vector_t *iface, void *item, int (*comparator)(void*, void*));
```

Searches an item position in a vector.\
Returns an index (first occurrence of matching item), or the size of a vector if no item was found.

## Parameters

Argument|Description
--------|-----------
iface|Pointer to a `vector_t` interface
item|An item
comparator|A comparator, i.e. a function that returns a nonzero value if arguments are diff.

If the comparator is `NULL`, the item addresses are compared.

## Complexity

O(N)

## Example

```c
    #include "vector.h"
    #include <stdio.h>
    #include <string.h>

    int main()
    {
        vector_t *v = create_vector();
        add_item_to_vector(v, "one");
        add_item_to_vector(v, "two");
        add_item_to_vector(v, "three");

        vector_index_t i = index_of_item_of_vector(v, "two", (void*)strcmp);
        vector_index_t j = index_of_item_of_vector(v, "four", (void*)strcmp);
        printf("result: %d, %d\n", i, j);

        destroy_vector(v);
        return 0;
    }
```

Output:

    result: 1, 3
    