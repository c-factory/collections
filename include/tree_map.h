/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The tree-map interface
*/

#pragma once

#include "allocator.h"
#include "balanced_tree.h"

typedef struct
{
    const size_t size;
} tree_map_t;

typedef  struct
{
    void *key;
    void *value;
} pair_t;

typedef struct
{
    iterator_t base;
} map_iterator_t;

tree_map_t * create_tree_map(int (*comparator)(void*, void*));
tree_map_t * create_tree_map_ext(int (*comparator)(void*, void*), const allocator_t *allocator);
void destroy_tree_map(tree_map_t *iface);
void destroy_tree_map_and_content(tree_map_t *iface,
            void (*key_destructor)(void *), void (*value_destructor)(void *));
void * add_pair_to_tree_map(tree_map_t *iface, void *key, void *value);
const pair_t * get_pair_from_tree_map (tree_map_t *iface, void *key);
void * remove_pair_from_tree_map(tree_map_t *iface, void *key);
map_iterator_t * create_iterator_from_tree_map(tree_map_t *iface);
void traverse_over_tree_map(tree_map_t *iface, void (*callback)(void*, pair_t*), void* obj);

static __inline void destroy_map_iterator(map_iterator_t *iface)
{
    destroy_iterator(&iface->base);
}

static __inline bool has_next_pair(map_iterator_t *iface)
{
    return has_next_item(&iface->base);
}

static __inline const pair_t * next_pair(map_iterator_t *iface)
{
    return (const pair_t*)next_item(&iface->base);
}
