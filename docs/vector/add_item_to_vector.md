[Collections](../collections.md) &rarr; [Vector](vector.md) &rarr;

# add_item_to_vector

```c
    void add_item_to_vector(vector_t *iface, void *item);
```

Adds an item to the end of the vector.

## Parameters

Argument|Description
--------|-----------
iface|Pointer to a `vector_t` interface
item|An item

## Complexity

O(1), amortized time, reallocation may happen.\
If a reallocation happens, the reallocation is itself up to linear in the entire size.

## Example

```c
    #include "vector.h"

    int main()
    {
        vector_t *v = create_vector();
        add_item_to_vector(v, "one");
        add_item_to_vector(v, "two");
        add_item_to_vector(v, "three");
        //...
        destroy_vector(v);
        return 0;
    }
```
