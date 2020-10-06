[Collections](../collections.md) &rarr; [Iterator](iterator.md) &rarr;

# has_next_item

```c
    bool has_next_item(iterator_t *iface);
```

Checks if there are more items in an iterator.

## Parameters

Argument|Description
--------|-----------
iface|Pointer to a `iterator_t` interface

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
        while(has_next_item(i)) // here we check if there is another item
        {
            printf("%s\n", next_item(i));
        }
        destroy_iterator(i);

        destroy_vector(v);
        return 0;
    }
```
