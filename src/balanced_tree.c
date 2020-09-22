/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The balance tree implementation
*/

#include "balanced_tree.h"
#include <assert.h>

void init_node_of_balanced_tree(bt_node_t *node)
{
	node->key = NULL;
	node->height = 1;
	node->left = NULL;
	node->right = NULL;
}

static __inline int get_node_height(bt_node_t* p)
{
	return p ? p->height : 0;
}

static __inline int calc_balance_factor (bt_node_t* p)
{
	return get_node_height(p->right) - get_node_height(p->left);
}

static __inline void fix_node_height(bt_node_t* p)
{
	int hl = get_node_height(p->left);
	int hr = get_node_height(p->right);
	p->height = ( hl > hr ? hl : hr ) + 1;
}

static bt_node_t * rotate_right(bt_node_t* p)
{
	bt_node_t* q = p->left;
	p->left = q->right;
	q->right = p;
	fix_node_height(p);
	fix_node_height(q);
	return q;
}

static bt_node_t * rotate_left(bt_node_t* q)
{
	bt_node_t* p = q->right;
	q->right = p->left;
	p->left = q;
	fix_node_height(q);
	fix_node_height(p);
	return p;
}

static bt_node_t * balance(bt_node_t* p)
{
	fix_node_height(p);
	int pbf = calc_balance_factor(p);
	if( pbf == 2 )
	{
		if( calc_balance_factor(p->right) < 0 )
			p->right = rotate_right(p->right);
		return rotate_left(p);
	}
	if( pbf == -2 )
	{
		if( calc_balance_factor(p->left) > 0  )
			p->left = rotate_left(p->left);
		return rotate_right(p);
	}
	return p;
}

bt_node_t * insert_node_into_balanced_tree(bt_node_t *root, bt_node_t *new_node, int (*comparator)(void*, void*))
{
	if( !root )
		return new_node;
	if( comparator(new_node->key, root->key) < 0)
		root->left = insert_node_into_balanced_tree(root->left, new_node, comparator);
	else
		root->right = insert_node_into_balanced_tree(root->right, new_node, comparator);
	return balance(root);
}

bt_node_t * find_node_in_balanced_tree(bt_node_t *root, void *key, int (*comparator)(void*, void*))
{
	if (!root)
		return NULL;

	int result = comparator(key, root->key);
	if (0 == result)
		return root;
	return find_node_in_balanced_tree(result < 0 ? root->left : root->right, key, comparator);
}

bt_node_t * find_min_node(bt_node_t* p)
{
	return p->left ? find_min_node(p->left) : p;
}

bt_node_t * remove_min_node(bt_node_t* p)
{
	if( p->left==0 )
		return p->right;
	p->left = remove_min_node(p->left);
	return balance(p);
}

bt_node_t * remove_node_from_balanced_tree(bt_node_t *root, void *key, int (*comparator)(void*, void*), bt_node_t **removed_node)
{
	if( !root )
		return NULL;
	int result = comparator(key, root->key);
	if ( result < 0 )
	{
		bt_node_t* new_left = remove_node_from_balanced_tree(root->left, key, comparator, removed_node);
		if (!new_left && !(*removed_node))
			return NULL;
		root->left = new_left;
		return balance(root);
	}
	else if ( result > 0 )
	{
		bt_node_t* new_right = remove_node_from_balanced_tree(root->right, key, comparator, removed_node);
		if (!new_right && !(*removed_node))
			return NULL;
		root->right = new_right;
		return balance(root);
	}
	else
	{
		*removed_node = root;
		bt_node_t* q = root->left;
		bt_node_t* r = root->right;
		if( !r )
			return q;
		bt_node_t* min = find_min_node(r);
		min->right = remove_min_node(r);
		min->left = q;
		return balance(min);
	}
}

void traverse_over_balanced_tree(bt_node_t *root, void (*callback)(void*, void*), void *obj)
{
	if (root->left)
		traverse_over_balanced_tree(root->left, callback, obj);
	callback(obj, root->key);
	if (root->right)
		traverse_over_balanced_tree(root->right, callback, obj);
}

typedef enum
{
	state_not_visited,
	state_next_left,
	state_next_this,
	state_next_right
} bt_traversal_state;

typedef struct
{
	bt_node_t *node;
	bt_traversal_state state;
} bt_traversal_data_t;

typedef struct
{
    void (*destroy)(iterator_t *iface);
    bool (*has_next)(iterator_t *iface);
    void* (*next)(iterator_t *iface);
	const allocator_t *allocator;
    bt_traversal_data_t *data;
	int max_depth;
	int depth;
} bt_iterator_t;

static void destroy_bt_iterator(iterator_t *iface)
{
    bt_iterator_t *this = (bt_iterator_t*)iface;
	if (this->data)
		this->allocator->release(this->data, (size_t)(sizeof(bt_traversal_data_t) * this->max_depth));
    this->allocator->release(this, sizeof(bt_iterator_t));
}

static bool bt_iterator_has_next_item(iterator_t *iface)
{
    bt_iterator_t *this = (bt_iterator_t*)iface;
    return this->depth >= 0;
}

static __inline void add_node_to_iterator(bt_iterator_t *this, bt_node_t *node)
{
	this->depth++;
	assert(this->depth < this->max_depth);
	this->data[this->depth].node = node;
	this->data[this->depth].state = state_not_visited;	
}

static void prepare_next_item(bt_iterator_t *this)
{
	while(true)	
	{
		bt_traversal_data_t *data = &this->data[this->depth];
		switch(data->state)
		{
			case state_not_visited:
			{
				bt_node_t *node = data->node;
				if (node->left)
				{
					data->state = state_next_left;
					add_node_to_iterator(this, node->left);
				}
				else
				{
					data->state = state_next_this;
					return;
				}
				break;
			}

			case state_next_left:
				data->state = state_next_this;
				return;

			case state_next_this:
			{
				bt_node_t *node = data->node;
				if (node->right)
				{
					data->state = state_next_right;
					add_node_to_iterator(this, node->right);
				}
				else
				{
					this->depth--;
					if (this->depth < 0)
						return;
				}
				break;
			}

			case state_next_right:
				this->depth--;
				if (this->depth < 0)
					return;
				break;
		}
	};
}

static void * bt_iterator_get_next_item(iterator_t *iface)
{
    bt_iterator_t *this = (bt_iterator_t*)iface;
	assert(this->data[this->depth].state == state_next_this);
	void *item = this->data[this->depth].node->key;
	prepare_next_item(this);
	return item;
}

iterator_t * create_iterator_from_balanced_tree(bt_node_t *root, const allocator_t *allocator)
{
	bt_iterator_t *this = allocator->allocate(sizeof(bt_iterator_t));
	this->destroy = destroy_bt_iterator;
	this->has_next = bt_iterator_has_next_item;
	this->next = bt_iterator_get_next_item;
	this->allocator = allocator;
	this->depth = -1;
	if (!root)
	{
		this->max_depth = 0;
		this->data = NULL;
	}
	else
	{
		this->max_depth = root->height;
		this->data = allocator->allocate((size_t)sizeof(bt_traversal_data_t) * this->max_depth);
		add_node_to_iterator(this, root);
		prepare_next_item(this);
	}	
	return (iterator_t*)this;
}
