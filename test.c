    #include "tree_set.h"
    #include <stdio.h>
    #include <string.h>

    //void print_string(void *obj)
    //{
    //    printf("%s\n", obj);
    //}

    int main()
    {
        tree_set_t *set = create_tree_set((void*)strcmp);
        add_item_to_tree_set(set, "class");
        add_item_to_tree_set(set, "z-buffer");
        add_item_to_tree_set(set, "include");
        add_item_to_tree_set(set, "data");
        add_item_to_tree_set(set, "class");
        add_item_to_tree_set(set, "iterator");
        add_item_to_tree_set(set, "allocator");

        iterator_t *iter = create_iterator_from_tree_set(set);
        while(has_next_item(iter))
        {
            void *data = next_item(iter);
            printf("%s\n", data);
        }
        destroy_iterator(iter);

        printf("%d\n", tree_set_contains_item(set, "include"));
        printf("%d\n", tree_set_contains_item(set, "blah_blah_blah"));

        destroy_tree_set(set);
        return 0;
    }
