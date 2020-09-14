[Collections](../collections.md) &rarr; [Vector](vector.md) &rarr;

# insert_item_into_vector

```c
    void insert_item_into_vector(vector_t *iface, vector_index_t index, void *item);
```

Inserts an item into a vector at specified position.\
If the specified position greater than or equal to the current vector size, adds an item to the end.

## Parameters

Argument|Description
--------|-----------
iface|Pointer to a `vector_t` interface
index|Item position after insert
item|An item

## Complexity

O(N)

## Example

```c
    #include "vector.h"
    #include <stdio.h>

    int main()
    {
        vector_t *v = create_vector();
        add_item_to_vector(v, "one");
        add_item_to_vector(v, "two");
        add_item_to_vector(v, "three");
        insert_item_into_vector(v, 1, "inserted item");

        for (vector_index_t i = 0; i < v->size; i++)
        {
            printf("%s\n", v->data[i]);
        }

        destroy_vector(v);
        return 0;
    }
```

Output:

    one
    inserted item
    two
    three
