[Collections](../collections.md) &rarr; [Vector](vector.md) &rarr;

# destroy_vector

```c
    void destroy_vector(vector_t *iface);
```

Destructs the vector itself, but does not destruct the vector data.

## Parameters

Argument|Description
--------|-----------
iface|Pointer to a `vector_t` interface

## Example

```c
    #include "vector.h"

    int main()
    {
        vector_t *v = create_vector();
        // ...
        destroy_vector(v);
        return 0;
    }
```
