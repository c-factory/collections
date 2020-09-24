/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The tree-map implementation
*/

#include "tree_map.h"

typedef struct tree_map
{
    bt_node_t base;
    pair_t pair;
} map_node_t;

typedef struct
{
    size_t size;
    map_node_t * root;
    const allocator_t * allocator;
    int (*comparator)(void*, void*);
} tree_map_impl_t;

static int default_comparator(void *left, void *right)
{
    if (left < right) return -1;
    if (left > right) return 1;
    return 0;
}

tree_map_t * create_tree_map(int (*comparator)(void*, void*))
{
    const allocator_t *allocator = get_system_allocator();
    tree_map_impl_t *this = allocator->allocate(sizeof(tree_map_impl_t));
    this->size = 0;
    this->root = NULL;
    this->allocator = allocator;
    this->comparator = comparator ? comparator : default_comparator;
    return (tree_map_t *)this;
}

tree_map_t * create_tree_map_ext(int (*comparator)(void*, void*), const allocator_t *allocator)
{
    tree_map_impl_t *this = allocator->allocate(sizeof(tree_map_impl_t));
    this->size = 0;
    this->root = NULL;
    this->allocator = allocator;
    this->comparator = comparator ? comparator : default_comparator;
    return (tree_map_t *)this;
}

static void destroy_node(map_node_t *node, const allocator_t *allocator)
{
    if (node->base.left)
        destroy_node((map_node_t*)node->base.left, allocator);
    if (node->base.right)
        destroy_node((map_node_t*)node->base.right, allocator);

    allocator->release(node, sizeof(map_node_t));
}

void destroy_tree_map(tree_map_t *iface)
{
    tree_map_impl_t *this = (tree_map_impl_t*)iface;
    if (this->root)
        destroy_node(this->root, this->allocator);
    this->allocator->release(this, sizeof(tree_map_impl_t));
}

static void destroy_node_and_content(map_node_t *node, const allocator_t *allocator,
            void (*key_destructor)(void *), void (*value_destructor)(void *))
{
    if (node->base.left)
        destroy_node_and_content((map_node_t*)node->base.left, allocator, key_destructor, value_destructor);
    if (node->base.right)
        destroy_node_and_content((map_node_t*)node->base.right, allocator, key_destructor, value_destructor);

    if (key_destructor)
        key_destructor(node->base.key);
    if (value_destructor)
        value_destructor(node->pair.value);
    allocator->release(node, sizeof(map_node_t));
}

void destroy_tree_map_and_content(tree_map_t *iface,
            void (*key_destructor)(void *), void (*value_destructor)(void *))
{
    tree_map_impl_t *this = (tree_map_impl_t*)iface;
    if (this->root)
        destroy_node_and_content(this->root, this->allocator, key_destructor, value_destructor);
    this->allocator->release(this, sizeof(tree_map_impl_t));
}

bool add_pair_to_tree_map(tree_map_t *iface, void *key, void *value)
{
    tree_map_impl_t *this = (tree_map_impl_t*)iface;
    bt_node_t *old_node = find_node_in_balanced_tree(&this->root->base, key, this->comparator);
    if (old_node)
        return false;
    map_node_t *node = this->allocator->allocate(sizeof(map_node_t));
    init_node_of_balanced_tree(&node->base);
    node->base.key = key;
    node->pair.key = key;
    node->pair.value = value;
    this->root = (map_node_t*)insert_node_into_balanced_tree(&this->root->base, &node->base, this->comparator);
    this->size++;
    return true;
}

const pair_t * get_pair_from_tree_map (tree_map_t *iface, void *key)
{
    tree_map_impl_t *this = (tree_map_impl_t*)iface;
    map_node_t *node = (map_node_t*)find_node_in_balanced_tree(&this->root->base, key, this->comparator);
    return node ? &node->pair : NULL;
}

void * remove_item_from_tree_map(tree_map_t *iface, void *key)
{
    tree_map_impl_t *this = (tree_map_impl_t*)iface;
    map_node_t *removed_item = NULL;
    map_node_t *new_root = (map_node_t*)remove_node_from_balanced_tree(&this->root->base, key, this->comparator, (bt_node_t**)&removed_item);
    if (!removed_item)
        return false;
    this->root = new_root;
    this->size--;
    void *value = removed_item->pair.value;
    this->allocator->release(removed_item, sizeof(map_node_t));
    return value;
}

static void * node_converter(bt_node_t *node)
{
    map_node_t *map_node = (map_node_t*)node;
    return &map_node->pair;
}

map_iterator_t * create_iterator_from_tree_map(tree_map_t *iface)
{
    tree_map_impl_t *this = (tree_map_impl_t*)iface;
    return (map_iterator_t*)create_iterator_from_balanced_tree(&this->root->base, this->allocator, node_converter);
}

void traverse_over_tree_map(tree_map_t *iface, void (*callback)(void*, pair_t*), void* obj)
{
    tree_map_impl_t *this = (tree_map_impl_t*)iface;
    traverse_over_balanced_tree(&this->root->base, (void(*)(void*, void*))callback, obj, node_converter);
}
