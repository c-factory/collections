    #include "tree_map.h"
    #include <stdio.h>
    #include <string.h>

    void print(const char* key, const char *value) // the function as an object
    {
        printf("%s -> %s\n", key, value);
    }

    void callback(void *obj, pair_t *pair)
    {
        void (*fn)(const char*, const char*) = obj;
        fn(pair->key, pair->value);
    }

    int main()
    {
        tree_map_t *map = create_tree_map((void*)strcmp);
        add_pair_to_tree_map(map, "zero", "0");
        add_pair_to_tree_map(map, "one", "1");
        add_pair_to_tree_map(map, "two", "2");
        add_pair_to_tree_map(map, "three", "3");
        traverse_over_tree_map(map, callback, print);
        destroy_tree_map(map);
        return 0;
    }
