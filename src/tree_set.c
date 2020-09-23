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

static int default_comparator(void *left, void *right)
{
    if (left < right) return -1;
    if (left > right) return 1;
    return 0;
}

tree_set_t * create_tree_set(int (*comparator)(void*, void*))
{
    const allocator_t *allocator = get_system_allocator();
    tree_set_impl_t *this = allocator->allocate(sizeof(tree_set_impl_t));
    this->size = 0;
    this->root = NULL;
    this->allocator = allocator;
    this->comparator = comparator ? comparator : default_comparator;
    return (tree_set_t *)this;
}

tree_set_t * create_tree_set_ext(int (*comparator)(void*, void*), const allocator_t *allocator)
{
    tree_set_impl_t *this = allocator->allocate(sizeof(tree_set_impl_t));
    this->size = 0;
    this->root = NULL;
    this->allocator = allocator;
    this->comparator = comparator ? comparator : default_comparator;
    return (tree_set_t *)this;
}

static void destroy_node(bt_node_t *node, const allocator_t *allocator)
{
    if (node->left)
        destroy_node(node->left, allocator);
    if (node->right)
        destroy_node(node->right, allocator);

    allocator->release(node, sizeof(bt_node_t));
}

void destroy_tree_set(tree_set_t *iface)
{
    tree_set_impl_t *this = (tree_set_impl_t*)iface;
    if (this->root)
        destroy_node(this->root, this->allocator);
    this->allocator->release(this, sizeof(tree_set_impl_t));
}

static void destroy_node_and_content(bt_node_t *node, const allocator_t *allocator, void (*destructor)(void *))
{
    if (node->left)
        destroy_node_and_content(node->left, allocator, destructor);
    if (node->right)
        destroy_node_and_content(node->right, allocator, destructor);

    destructor(node->key);
    allocator->release(node, sizeof(bt_node_t));
}

void destroy_tree_set_and_content(tree_set_t *iface, void (*destructor)(void *))
{
    tree_set_impl_t *this = (tree_set_impl_t*)iface;
    if (this->root)
        destroy_node_and_content(this->root, this->allocator, destructor);
    this->allocator->release(this, sizeof(tree_set_impl_t));
}

bool add_item_to_tree_set(tree_set_t *iface, void *item)
{
    tree_set_impl_t *this = (tree_set_impl_t*)iface;
    bt_node_t *old_node = find_node_in_balanced_tree(this->root, item, this->comparator);
    if (old_node)
        return false;
    bt_node_t *node = this->allocator->allocate(sizeof(bt_node_t));
    init_node_of_balanced_tree(node);
    node->key = item;
    this->root = insert_node_into_balanced_tree(this->root, node, this->comparator);
    this->size++;
    return true;
}

bool is_there_item_in_tree_set(tree_set_t *iface, void *item)
{
    tree_set_impl_t *this = (tree_set_impl_t*)iface;
    bt_node_t *existing_node = find_node_in_balanced_tree(this->root, item, this->comparator);
    return existing_node != NULL;
}

bool remove_item_from_tree_set(tree_set_t *iface, void *item)
{
    tree_set_impl_t *this = (tree_set_impl_t*)iface;
    bt_node_t *removed_item = NULL;
    bt_node_t *new_root = remove_node_from_balanced_tree(this->root, item, this->comparator, &removed_item);
    if (!removed_item)
        return false;
    this->root = new_root;
    this->size--;
    this->allocator->release(removed_item, sizeof(bt_node_t));
    return true;
}

void traverse_over_tree_set(tree_set_t *iface, void (*callback)(void*, void*), void* obj)
{
    tree_set_impl_t *this = (tree_set_impl_t*)iface;
    traverse_over_balanced_tree(this->root, callback, obj);
}

static void * node_converter(bt_node_t *node)
{
    return node->key;
}

iterator_t * create_iterator_from_tree_set(tree_set_t *iface)
{
    tree_set_impl_t *this = (tree_set_impl_t*)iface;
    return create_iterator_from_balanced_tree(this->root, this->allocator, node_converter);
}
