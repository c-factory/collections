[Collections](../collections.md) &rarr; [Iterator](iterator.md) &rarr;

# destroy_iterator

```c
    void destroy_iterator(iterator_t *iface);
```

Destructs the iterator.

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
            printf("%s\n", next_item(i));
        }
        destroy_iterator(i); // here we destroy the iterator

        destroy_vector(v);
        return 0;
    }
```
