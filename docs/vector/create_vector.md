[Collections](../collections.md) &rarr; [Vector](vector.md) &rarr;

# create_vector

```c
    vector_t * create_vector();
```

Returns a new empty vector. Never returns `NULL`.

The created vector after using must be freed by the [`destroy_vector`](destroy_vector.md) (or the [`destroy_vector_and_content`](destroy_vector_and_content.md)) function.

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
