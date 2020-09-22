[Collections](../collections.md) &rarr;

# Tree Set

The tree set is a set of unique items, based on binary balanced tree. This structure guarantees that any operation with set of _N_ items will not be performed more than _log<sub>2</sub>N_ steps.

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
* **[create_tree_set_ext](create_tree_set_ext.md)** - creates an empty tree set using a specified memory allocator;
* **[destroy_tree_set](destroy_tree_set.md)** - destructs a tree set itself, but does not destruct its data;
* **[destroy_tree_set_and_content](destroy_tree_set_and_content.md)** - destructs a tree set and also its data using a destructor;
* **[add_item_to_tree_set](add_item_to_tree_set.md)** - adds an item to a tree set;
* **[is_there_item_in_tree_set](is_there_item_in_tree_set.md)** - checks if there is an item in a tree set;
* **[remove_item_from_tree_set](remove_item_from_tree_set.md)** - removes an item from a tree set;
* **[create_iterator_from_tree_set](create_iterator_from_tree_set.md)** - returns an iterator, created from a tree set.
