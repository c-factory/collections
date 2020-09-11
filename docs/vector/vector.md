[Collections](../collections.md) &rarr;

# Vector

The vector is a container in which elements are stored contiguously.

Vectors allow random access; that is, an element of a vector may be referenced in the same manner as elements of arrays (by array indices). Access to any element takes the same time. However, adding and removing an element from the middle of a vector causes all elements to shift, i.e., it is a slow operation.

## Include

The file `vector.h` contains all definitions.

## Data types

```c
    typedef struct
    {
        const size_t size;
        const void * const * data;
    } vector_t;

    typedef size_t vector_index_t;
```

### vector_t

The `vector_t` struct contains 2 fields:

* **size** - current vector size
* **data** - data array

Both fields cannot be modified directly. All changes are performed with functions only.

### vector_index_t

Index for accessing vector items. It's an unsigned integer.

## Functions

* **[create_vector](create_vector.md)** - creates an empty vector;
* **[create_vector_ext](create_vector_ext.md)** - creates an empty vector with initial capacity using a specified memory allocator;
* **[destroy_vector](destroy_vector.md)** - releases a vector;
* **[destroy_vector_and_content](destroy_vector_and_content.md)** - releases a vector and also its content using a destructor;
