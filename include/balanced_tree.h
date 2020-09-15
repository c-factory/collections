/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The balanced tree interface
	Based on it, the 'tree_set' and the 'tree_map' collections are built 
*/

#pragma once

typedef struct balanced_tree_t balanced_tree_t;

struct balanced_tree_t
{
	const void * const key;
	const int height;
	const balanced_tree_t * const left;
	const balanced_tree_t * const right;
};

balanced_tree_t * insert_node_into_balanced_tree(balanced_tree_t *root, balanced_tree_t *node, int (*comparator)(void*, void*));
