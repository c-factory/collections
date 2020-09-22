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

tree_map_t * create_tree_map(int (*comparator)(void*, void*));
void destroy_tree_map(tree_map_t *iface);
bool add_pair_to_tree_map(tree_map_t *iface, void *key, void *value);
pair_t get_pair_from_tree_map (tree_map_t *iface, void *key);
iterator_t * create_iterator_from_tree_map(tree_map_t *iface);
/*
tree_set_t * create_tree_set_ext(int (*comparator)(void*, void*), const allocator_t *allocator);
void destroy_tree_set(tree_set_t *iface);
void destroy_tree_set_and_content(tree_set_t *iface, void (*destructor)(void *));
bool add_item_to_tree_set(tree_set_t *iface, void *item);
bool is_there_item_in_tree_set(tree_set_t *iface, void *item);
bool remove_item_from_tree_set(tree_set_t *iface, void *item);
void traverse_over_tree_set(tree_set_t *iface, void (*callback)(void*, void*), void* obj);
iterator_t * create_iterator_from_tree_set(tree_set_t *iface);
*/