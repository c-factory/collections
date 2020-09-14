[Collections](../collections.md) &rarr; [Vector](vector.md) &rarr;

# set_vector_item

```c
    void * set_vector_item(vector_t *iface, vector_index_t index, void *item);
```

Replaces an item from a vector at specified position.\
Adds an item to the end of a vector if the position incorrect.\
Returns the item that was replaced (or `NULL` if no one item was replaced). The returned value can be used for freeing memory.

## Parameters

Argument|Description
--------|-----------
iface|Pointer to a `vector_t` interface
index|Item position
item|A new item

## Complexity

O(1)

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
        set_vector_item(v, 1, "four");

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
        
        void *p = set_vector_item(v, 1, strdup("four"));
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
    four
    three
