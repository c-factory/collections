/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The balance tree implementation
*/

#include "balanced_tree.h"

bt_node_t * create_node_of_balanced_tree(const allocator_t *allocator)
{
	bt_node_t *node = allocator->allocate(sizeof(bt_node_t));
	node->key = NULL;
	node->height = 1;
	node->left = NULL;
	node->right = NULL;
	return node;
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

/*
node* findmin(node* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left?findmin(p->left):p;
}

node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
{
	if( p->left==0 )
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* remove(node* p, int k) // удаление ключа k из дерева p
{
	if( !p ) return 0;
	if( k < p->key )
		p->left = remove(p->left,k);
	else if( k > p->key )
		p->right = remove(p->right,k);	
	else //  k == p->key 
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if( !r ) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}
*/

void traversal_of_balanced_tree(bt_node_t *root, void (*callback)(void*))
{
	if (root->left)
		traversal_of_balanced_tree(root->left, callback);
	callback(root->key);
	if (root->right)
		traversal_of_balanced_tree(root->right, callback);
}
