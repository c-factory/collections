[Collections](../collections.md) &rarr;

# Tree Map

The tree map is a set of pairs key-value, in which each key is unique. Another name for this structure - associative array.\
The tree map is based on binary balanced tree. This structure guarantees that any operation with set of _N_ pairs will not be performed more than _log<sub>2</sub>N_ steps.

## Include

The file `tree_map.h` contains all definitions.

## Data types

```c
    typedef struct
    {
        const size_t size;
    } tree_map_t;
```

### tree_map_t

The `tree_map_t` struct contains only one field:

* **size** - current size of map.

The field cannot be modified directly. All changes are performed with functions only.

## Functions

* **[create_tree_map](create_tree_map.md)** - creates an empty tree map;
* **[create_tree_map_ext](create_tree_map_ext.md)** - creates an empty tree map using a specified memory allocator;
* **[destroy_tree_map](destroy_tree_map.md)** - destructs a tree map itself, but does not destruct its data;
* **[destroy_tree_map_and_content](destroy_tree_map_and_content.md)** - destructs a tree map and also its data using a destructor;
* **[add_pair_to_tree_map](add_pair_to_tree_map.md)** - adds a pair to a tree map;
* **[get_pair_from_tree_map](get_pair_from_tree_map.md)** - returns a pair by key from a tree map;
* **[remove_pair_from_tree_map](remove_pair_from_tree_map.md)** - removes a pair from a tree map;
* **[create_iterator_from_tree_map](create_iterator_from_tree_map.md)** - returns a [map iterator](../map/map_iterator.md), created from a tree map;
* **[traverse_over_tree_map](traverse_over_tree_map.md)** - traverses over a tree map and calls a callback, without iterator creation.
