[Collections](../collections.md) &rarr; [Tree Set](tree_set.md) &rarr;

# traverse_over_tree_set

```c
    void traverse_over_tree_set(tree_set_t *iface, void (*callback)(void*, void*), void* obj);
```

Traverses over a set and calls a callback, without iterator creation.\
Because the tree set structure is built on a balanced binary tree, the function will traverse the tree in ascending order of items.

## Parameters

Argument|Description
--------|-----------
iface|Pointer to a `tree_set_t` interface
callback|A callback that takes two arguments: first is any pointer, and second is an item of a set
obj|An object that will pass as the first argument

## Example

```c
    #include "tree_set.h"
    #include <stdio.h>
    #include <string.h>

    void print(const char* str) // the function as an object
    {
        printf("%s\n", str);
    }

    void callback(void *obj, void *item)
    {
        void (*fn)(const char*) = obj;
        fn(item);
    }

    int main()
    {
        tree_set_t *s = create_tree_set((void*)strcmp);
        add_item_to_tree_set(s, "zero");
        add_item_to_tree_set(s, "one");
        add_item_to_tree_set(s, "two");
        add_item_to_tree_set(s, "three");
        traverse_over_tree_set(s, callback, print);
        destroy_tree_set(s);
        return 0;
    }
```

Output:

    one
    three
    two
    zero
