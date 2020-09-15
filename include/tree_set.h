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
    const balanced_tree_t * const root;
} tree_set_t;

tree_set_t * create_tree_set(int (*comparator)(void*, void*));
void add_item_to_tree_set(tree_set_t *iface, void *item);