    #include "tree_set.h"
    #include <stdio.h>
    #include <string.h>

    void print_string(void *obj)
    {
        printf("%s\n", obj);
    }

    int main()
    {
        tree_set_t *set = create_tree_set((void*)strcmp);
        add_item_to_tree_set(set, "class");
        add_item_to_tree_set(set, "z-buffer");
        add_item_to_tree_set(set, "include");
        add_item_to_tree_set(set, "data");
        add_item_to_tree_set(set, "iterator");
        add_item_to_tree_set(set, "allocator");

        traverse_over_tree_set(set, print_string);
        return 0;
    }