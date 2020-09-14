[Collections](../collections.md) &rarr; [Iterator](iterator.md) &rarr;

# next_item

```c
    void * next_item(iterator_t *iface);
```

returns the next item from the iterator, or `NULL`, if the iterator is empty.

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
        while(has_next_item(i))
        {
            printf("%s\n", next_item(i)); // here we take the next item
        }
        destroy_iterator(i);

        destroy_vector(v);
        return 0;
    }
```
