[Collections](../collections.md) &rarr; [Map](map.md) &rarr; 

# Map Iterator

The map iterator represents an iterator for traversing over a map. This iterator extends the base [`iterator_t`](../iterator/iterator.md) interface (can be cast to it) but returns objects of the `pair_t` type.

## Include

The file `map.h` contains all definitions.

## Data types

```c
    typedef struct
    {
        iterator_t base;
    } map_iterator_t;
```

### map_iterator_t

The `map_iterator_t` struct wraps the base [`iterator_t`](../iterator/iterator.md) struct.

## Functions

* **[destroy_map_iterator](destroy_map_iterator.md)** - destructs a map iterator;
* **[has_next_pair](has_next_pair.md)** - checks if there are more pairs in a map iterator;
* **[next_pair](next_pair.md)** - returns the next pair from a map iterator.
