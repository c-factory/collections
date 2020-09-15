    #include "tree_set.h"
    #include <stdio.h>
    #include <string.h>

    void print_balance_tree(const balanced_tree_t * const node)
    {
        if (node->left)
            print_balance_tree(node->left);
        printf("%s\n", node->key);
        if (node->right)
            print_balance_tree(node->right);
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

        print_balance_tree(set->root);
        return 0;
    }
