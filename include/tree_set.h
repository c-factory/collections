/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The tree-set interface
*/

#pragma once

#include "allocator.h"
#include "balanced_tree.h"

typedef struct
{
    const size_t size;
} tree_set_t;

tree_set_t * create_tree_set(int (*comparator)(void*, void*));
tree_set_t * create_tree_set_ext(int (*comparator)(void*, void*), const allocator_t *allocator);
void destroy_tree_set(tree_set_t *iface);
void destroy_tree_set_and_content(tree_set_t *iface, void (*destructor)(void *));
bool add_item_to_tree_set(tree_set_t *iface, void *item);
bool is_there_item_in_tree_set(tree_set_t *iface, void *item);
bool remove_item_from_tree_set(tree_set_t *iface, void *item);
void traverse_over_tree_set(tree_set_t *iface, void (*callback)(void*));
iterator_t * create_iterator_from_tree_set(tree_set_t *iface);
