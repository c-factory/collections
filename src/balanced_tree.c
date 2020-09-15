/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The balance tree implementation
*/

#include "balanced_tree.h"

typedef struct node_t node_t;

struct node_t
{
	void * key;
	int height;
	node_t * left;
	node_t * right;
};

static __inline int get_node_height(node_t* p)
{
	return p ? p->height : 0;
}

static __inline int calc_balance_factor (node_t* p)
{
	return get_node_height(p->right) - get_node_height(p->left);
}

static __inline void fix_node_height(node_t* p)
{
	int hl = get_node_height(p->left);
	int hr = get_node_height(p->right);
	p->height = ( hl > hr ? hl : hr ) + 1;
}

static node_t * rotate_right(node_t* p)
{
	node_t* q = p->left;
	p->left = q->right;
	q->right = p;
	fix_node_height(p);
	fix_node_height(q);
	return q;
}

static node_t * rotate_left(node_t* q)
{
	node_t* p = q->right;
	q->right = p->left;
	p->left = q;
	fix_node_height(q);
	fix_node_height(p);
	return p;
}

static node_t * balance(node_t* p)
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

static node_t * insert(node_t* p, node_t *q, int (*comparator)(void*, void*))
{
	if( !p )
		return q;
	if( comparator(q->key, p->key) < 0)
		p->left = insert(p->left, q, comparator);
	else
		p->right = insert(p->right, q, comparator);
	return balance(p);
}

balanced_tree_t * insert_node_into_balanced_tree(balanced_tree_t *root, balanced_tree_t *node, int (*comparator)(void*, void*))
{
	return (balanced_tree_t*)insert((node_t*)root, (node_t*)node, comparator);
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