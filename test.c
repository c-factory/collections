#include "tree_map.h"
#include <string.h>
#include <stdio.h>

int main(void)
{
    tree_map_t *map = create_tree_map((void*)strcmp);
    add_pair_to_tree_map(map, "zero", "0");
    add_pair_to_tree_map(map, "one", "1");
    add_pair_to_tree_map(map, "two", "2");
    add_pair_to_tree_map(map, "three", "3");
    add_pair_to_tree_map(map, "four", "4");
    map_iterator_t *iter = create_iterator_from_tree_map(map);
    while(has_next_pair(iter))
    {
        const pair_t *pair = get_pair_from_tree_map(map, next_pair(iter)->key);
        printf("%s -> %s\n", pair->key, pair->value);
    }
    destroy_map_iterator(iter);
    destroy_tree_map(map);
    return 0;
}
