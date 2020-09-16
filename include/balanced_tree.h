/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The balanced tree interface
	Based on it, the 'tree_set' and the 'tree_map' collections are built 
*/

#pragma once

#include "allocator.h"
#include "iterator.h"

typedef struct bt_node_t bt_node_t; // balanced tree node

struct bt_node_t
{
	void * key;
	int height;
	bt_node_t * left;
	bt_node_t * right;
};

bt_node_t * create_node_of_balanced_tree(const allocator_t *allocator);
void * destroy_balanced_tree(bt_node_t *root, const allocator_t *allocator, size_t node_size);
bt_node_t * insert_node_into_balanced_tree(bt_node_t *root, bt_node_t *node, int (*comparator)(void*, void*));
void traversal_of_balanced_tree(bt_node_t *root, void (*callback)(void*));
iterator_t * create_iterator_from_balanced_tree(bt_node_t *root, const allocator_t *allocator);
