[Collections](../collections.md) &rarr;

# Map

The map is an abstract set of pairs key-value, in which each key is unique. Another name for this structure - associative array.

## Implementations

* **[Tree Map](../tree_map/tree_map.md)** - a map based on binary balanced tree.

## Include

The file `map.h` contains all definitions.

## Data types

```c
    typedef  struct
    {
        void *key;
        void *value;
    } pair_t;

    typedef struct
    {
        iterator_t base;
    } map_iterator_t;
```

### pair_t

The `pair_t` struct represents a pair key-value.

### map_iterator_t

The `map_iterator_t` struct represents an iterator for traversing over a map. This iterator extends the base [`iterator_t`](../iterator/iterator.md) interface (can be cast to it) but returns objects of the `pair_t` type.\
See **[description](map_iterator.md)** in the separate doc.
