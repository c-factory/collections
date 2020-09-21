[Collections](../collections.md) &rarr;

# Tree Set

The tree set is a set of unique items, based on binary balanced tree. This structure guarantees that any operation with set of _N_ items will not be performed more than _log<sub>2</sub>(N)_ steps.

## Include

The file `tree_set.h` contains all definitions.

## Data types

```c
    typedef struct
    {
        const size_t size;
    } tree_set_t;
```

### tree_set_t

The `tree_set_t` struct contains only one field:

* **size** - current size of set.

The field cannot be modified directly. All changes are performed with functions only.

## Functions

* **[create_tree_set](create_tree_set.md)** - creates an empty tree set;
