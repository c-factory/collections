/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The tree-set implementation
*/

#include "tree_set.h"

typedef struct
{
    size_t size;
    balanced_tree_t * root;
    const allocator_t * allocator;
    int (*comparator)(void*, void*);
} tree_set_impl_t;

typedef struct node_t node_t;

struct node_t
{
	void * key;
	int height;
	node_t * left;
	node_t * right;
};

tree_set_t * create_tree_set(int (*comparator)(void*, void*))
{
    const allocator_t *allocator = get_system_allocator();
    tree_set_impl_t *this = allocator->allocate(sizeof(tree_set_impl_t));
    this->size = 0;
    this->root = NULL;
    this->allocator = allocator;
    this->comparator = comparator;
    return (tree_set_t *)this;
}

void add_item_to_tree_set(tree_set_t *iface, void *item)
{
    tree_set_impl_t *this = (tree_set_impl_t*)iface;
    node_t *node = this->allocator->allocate(sizeof(node_t));
    node->key = item;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    this->root = insert_node_into_balanced_tree(this->root, (balanced_tree_t*)node, this->comparator);
    this->size++;
}
