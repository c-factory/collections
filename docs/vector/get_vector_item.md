[Collections](../collections.md) &rarr; [Vector](vector.md) &rarr;

# get_vector_item

```c
    void * get_vector_item(vector_t *iface, vector_index_t index);
```

Returns an item from a vector, from specified position, or `NULL` if the position is incorrect.

## Parameters

Argument|Description
--------|-----------
iface|Pointer to a `vector_t` interface
index|Item position

## Complexity

O(1)

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

        for (vector_index_t i = 0; i < v->size; i++)
        {
            printf("%s\n", get_vector_item(v, i));
        }

        destroy_vector(v);
        return 0;
    }
```

A more obvious and faster solution is to get the element directly from the `data` array.\
However, this method does not check if the index is outside the array:

```c
    #include "vector.h"
    #include <stdio.h>

    int main()
    {
        vector_t *v = create_vector();
        add_item_to_vector(v, "one");
        add_item_to_vector(v, "two");
        add_item_to_vector(v, "three");

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
    two
    three
