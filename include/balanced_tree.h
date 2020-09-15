/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The balanced tree interface
	Based on it, the 'tree_set' and the 'tree_map' collections are built 
*/

#pragma once

#include "allocator.h"

typedef struct balanced_tree_t balanced_tree_t;

struct balanced_tree_t
{
	void * key;
	int height;
	balanced_tree_t * left;
	balanced_tree_t * right;
};

balanced_tree_t * create_node_of_balanced_tree(const allocator_t *allocator);
balanced_tree_t * insert_node_into_balanced_tree(balanced_tree_t *root, balanced_tree_t *node, int (*comparator)(void*, void*));
void traversal_of_balanced_tree(balanced_tree_t *root, void (*callback)(void*));
