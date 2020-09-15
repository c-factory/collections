[Collections](../collections.md) &rarr; [Vector](vector.md) &rarr;

# remove_item_from_vector

```c
    void * remove_item_from_vector(vector_t *iface, vector_index_t index);
```

Removes an item from a vector, from specified position.\
Returns the item that was deleted (or `NULL` if no one item was deleted). The returned value can be used for freeing memory.

## Parameters

Argument|Description
--------|-----------
iface|Pointer to a `vector_t` interface
index|Item position

## Complexity

O(N) common case\
O(1) if the last element is removed

## Example

Without memory allocation/freeing for items: 

```c
    #include "vector.h"
    #include <stdio.h>

    int main()
    {
        vector_t *v = create_vector();
        add_item_to_vector(v, "one");
        add_item_to_vector(v, "two");
        add_item_to_vector(v, "three");
        remove_item_from_vector(v, 1);

        for (vector_index_t i = 0; i < v->size; i++)
        {
            printf("%s\n", v->data[i]);
        }

        destroy_vector(v);
        return 0;
    }
```

With memory allocation:

```c
    #include "vector.h"
    #include <stdio.h>
    #include <string.h>

    int main()
    {
        vector_t *v = create_vector();
        add_item_to_vector(v, strdup("one")); // 'using' strdup for string copying
        add_item_to_vector(v, strdup("two"));
        add_item_to_vector(v, strdup("three"));
        
        void *p = remove_item_from_vector(v, 1);
        free(p); // freeing memory of the item that was deleted

        for (vector_index_t i = 0; i < v->size; i++)
        {
            printf("%s\n", v->data[i]);
        }

        destroy_vector_and_content(v, free);
        return 0;
    }
```

Output:

    one
    three
