[Collections](../collections.md) &rarr; [Vector](vector.md) &rarr;

# create_iterator_from_vector

```c
    iterator_t * create_iterator_from_vector(vector_t *iface);
```

Returns an [iterator](../iterator/iterator.md), created from a vector.

## Parameters

Argument|Description
--------|-----------
iface|Pointer to a `vector_t` interface

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

        iterator_t *i = create_iterator_from_vector(v);
        while(has_next_item(i))
        {
            printf("%s\n", next_item(i));
        }
        destroy_iterator(i);

        destroy_vector(v);
        return 0;
    }
```
