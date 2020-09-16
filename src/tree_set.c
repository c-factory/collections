/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The tree-set implementation
*/

#include "tree_set.h"

typedef struct
{
    size_t size;
    bt_node_t * root;
    const allocator_t * allocator;
    int (*comparator)(void*, void*);
} tree_set_impl_t;

typedef struct node_t node_t;

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
    bt_node_t *node = create_node_of_balanced_tree(this->allocator);
    node->key = item;
    this->root = insert_node_into_balanced_tree(this->root, node, this->comparator);
    this->size++;
}

void traverse_over_tree_set(tree_set_t *iface, void (*callback)(void*))
{
    tree_set_impl_t *this = (tree_set_impl_t*)iface;
    traversal_of_balanced_tree(this->root, callback);
}

iterator_t * create_iterator_from_tree_set(tree_set_t *iface)
{
    tree_set_impl_t *this = (tree_set_impl_t*)iface;
    return create_iterator_from_balanced_tree(this->root, this->allocator);
}
