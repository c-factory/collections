[Collections](collections.md) &rarr;

# Comparator

A comparator function is used as an argument when creating collections and searching for collections data.

## Signature

```c
    int (*comparator)(void *left, void *right);
```

Comparator returns:

Value|Condition
--------|-----------
0|if _left = right_
&gt; 0|if _left > right_
&lt; 0|if _left < right_

## Where it's used

As mandatory parameter when creating tree-based collections:

```c
    tree_set_t * create_tree_set(int (*comparator)(void*, void*));
```

As a parameter when searching in collection:

```c
    vector_index_t index_of_item_of_vector(vector_t *iface, void *item, int (*comparator)(void*, void*));
```

## Example

The library `strcmp` function is a comparator for strings, that matches this signature.\
Creating a set of strings:

```c
    tree_set_t *set = create_tree_set((void*)strcmp);
```
