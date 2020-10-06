[Collections](../collections.md) &rarr;

# Iterator

Iterator is the interface for sequentially accessing items in a collection. Each collection provides its own implementation of the iterator.\
Iterators do not contain a copy of a collection, it contains only pointers. Therefore, as a rule, it is not possible to change the collection's data while the iterator is in use.

## Include

The file `iterator.h` contains all definitions.

## Data types

```c
    typedef struct iterator_t iterator_t;

    struct iterator_t
    {
        void (*destroy)(iterator_t *iface);
        bool (*has_next)(iterator_t *iface);
        void* (*next)(iterator_t *iface);
    };
```

### iterator_t

The `iterator_t` struct contains 3 function pointers:

* **destroy** - destructor for the iterator;
* **has_next** - checks if there are more items in the iterator;
* **next** - returns the next item from the iterator, or `NULL`, if the iterator is empty.

## Functions

Here defined 3 helper function, each is a wrapper around the corresponding function pointer:

* **[destroy_iterator](destroy_iterator.md)** - destructs an iterator;
* **[has_next_item](has_next_item.md)** - checks if there are more items in an iterator;
* **[next_item](next_item.md)** - returns the next item from an iterator.
