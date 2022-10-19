/*****************************************************   
 * Author : Avia Avikasis                            *
 * Reviewer: Eitan                                   *
 * 15/07/2022                                        *
 * Description : imlementation of binary search tree *
 *                                                   *
 *****************************************************/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include "bst.h"

#define TRUE 1

typedef enum 
{
	LEFT,
	RIGHT,
	CHILDREN_NUM
} bst_children_ty;


struct bst
{
    node_ty *dummy_root; 
    cmp_func cmp;
    void *params;
};

struct node
{
    void *data;
    node_ty *children[CHILDREN_NUM];
    node_ty *parent;
};

/* static functions */
static int IsEnd(bst_iterator_ty iter , const bst_ty *bst);
static int Flag(const bst_ty *bst,void *data,bst_iterator_ty iterator);
static int MatchSide(bst_iterator_ty child);
static node_ty *GetParent(bst_iterator_ty node);
static int IsDummy(bst_iterator_ty iterator);
static int IsEnd(bst_iterator_ty iter , const bst_ty *bst);
static int IsMatch(const bst_ty *bst, void *data , bst_iterator_ty iter);
static int IsLeaf(bst_iterator_ty position);
static void SwapAndDelete(bst_iterator_ty position ,bst_iterator_ty swap_node);


static node_ty **GetChildren(bst_iterator_ty node)
{
	return node->children;
}


static node_ty *CreateNode(void *data , node_ty *parent)
{
	node_ty *new_node = (node_ty*)malloc(sizeof(node_ty));
	if(NULL == new_node)
	{
		return NULL;
	}

	new_node->data = data;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	new_node->parent = parent;
	return new_node;
}


bst_ty *BstCreate(cmp_func cmp, void *params)
{
	node_ty *dummy_node = NULL;
	bst_ty *new_bst = NULL;
	assert(NULL != cmp);
	 
	new_bst = (bst_ty*)malloc(sizeof(bst_ty));
	if(NULL == new_bst)
	{
		return NULL;
	}
	dummy_node = CreateNode(NULL , NULL);
	new_bst->dummy_root = dummy_node;
	new_bst->cmp = cmp;
	new_bst->params = params;
	
	return new_bst;
}

int BstIsEmpty(const bst_ty *bst)
{
	assert(NULL != bst);
	return (NULL == *(GetChildren(bst->dummy_root)));
}

size_t BstSize(const bst_ty *bst)
{
	int counter = 0;
	node_ty *run_iter = BstBegin(bst);
	while(NULL != run_iter && !IsEnd(run_iter , bst))
	{
		++counter;
		run_iter = BstGetNext(run_iter);
	}	
	return counter ;
}

static int Flag(const bst_ty *bst, void *data, bst_iterator_ty iterator)
{
	return (NULL == BstGetData(iterator) || 
			 0 > bst->cmp(data , BstGetData(iterator) , NULL)) ? LEFT : RIGHT;
}


bst_iterator_ty BstInsert(bst_ty *bst, void *data)
{
	int insert = 0;
	bst_iterator_ty run_iter = NULL;
	bst_iterator_ty temp_iter = NULL;
	int side_flag = 0;
	
	assert(NULL != bst);
	
	run_iter = bst->dummy_root;
	
	while(0 == insert)
	{ 
		side_flag = Flag(bst , data , run_iter);
		temp_iter = GetChildren(run_iter)[side_flag];
		
		if(NULL == temp_iter)
		{
			run_iter->children[side_flag] = CreateNode(data , run_iter);
			insert = 1;
		}
		else
		{
			run_iter = temp_iter;
		}
	}
	return run_iter->children[side_flag];
}

void *BstGetData(bst_iterator_ty iterator)
{
	assert(NULL != iterator);
	return iterator->data;
}


static int MatchSide(bst_iterator_ty child)
{
	return (child == GetChildren(GetParent(child))[LEFT]) ? LEFT : RIGHT;
}


static node_ty *GetParent(bst_iterator_ty node)
{
	assert(NULL != node);
	return node->parent;
}

void BstDestroy(bst_ty *bst)
{
	bst_iterator_ty save_parent = NULL;
	bst_iterator_ty free_iter = NULL;
	
	assert(NULL != bst);
	free_iter = bst->dummy_root;
	
	while(!BstIsEmpty(bst))
	{
		if(NULL != GetChildren(free_iter)[LEFT])
		{
			free_iter = GetChildren(free_iter)[LEFT];
		}
		
		else if(NULL != GetChildren(free_iter)[RIGHT])
		{
			free_iter = GetChildren(free_iter)[RIGHT];	
		}
		else
		{
			save_parent = GetParent(free_iter);
			save_parent->children[MatchSide(free_iter)] = NULL;
			free(free_iter);
			free_iter = save_parent;
		}
	}
	free(bst->dummy_root);
	free(bst);		
}


bst_iterator_ty BstBegin(const bst_ty *bst)
{
	bst_iterator_ty run_iter = NULL;
	assert(NULL != bst);
	
	run_iter = bst->dummy_root;
	while(NULL != GetChildren(run_iter)[LEFT])
	{
		run_iter = GetChildren(run_iter)[LEFT];
	}	
	
	return (BstIterIsEqual(run_iter , bst->dummy_root) ? NULL : run_iter);
}


bst_iterator_ty BstEnd(const bst_ty *bst)
{
	assert(NULL != bst);
	return bst->dummy_root;
}

bst_iterator_ty BstGetNext(bst_iterator_ty iterator)
{
	assert(NULL != iterator);
	
	if(NULL == GetChildren(iterator)[RIGHT])
	{
		while(RIGHT == MatchSide(iterator))
		{
			iterator = GetParent(iterator);
		}
		return GetParent(iterator);
	}
	
	iterator = GetChildren(iterator)[RIGHT];
	
	while(NULL != GetChildren(iterator)[LEFT])
	{
		iterator = GetChildren(iterator)[LEFT];
	}
	
	return iterator;
}

static int IsDummy(bst_iterator_ty iterator)
{
	assert(NULL != iterator);
	return (NULL == BstGetData(iterator));
}

bst_iterator_ty BstGetPrev(bst_iterator_ty iterator)
{
	assert(NULL != iterator);
	
	if(NULL == GetChildren(iterator)[LEFT])
	{
		while(LEFT == MatchSide(iterator) && !IsDummy(GetParent(iterator)))
		{
			iterator = GetParent(iterator);
		}
		return GetParent(iterator);
	}
	
	iterator = GetChildren(iterator)[LEFT];
	
	while(NULL != GetChildren(iterator)[RIGHT])
	{
		iterator = GetChildren(iterator)[RIGHT];
	}
	
	return iterator;	
}


int BstIterIsEqual(bst_iterator_ty iterator1, bst_iterator_ty iterator2)
{
	assert(NULL != iterator1);
	assert(NULL != iterator2);
	return (iterator1 == iterator2);
}


int BstForEach(bst_iterator_ty from, bst_iterator_ty to, 
									action_func action, void *params)
{
	int return_func = 0; 
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != action);
	
	while(!BstIterIsEqual(from , to))
	{
		return_func = action(BstGetData(from) , params);
		if(0 != return_func)
		{
			return return_func;
		}
		from = BstGetNext(from);
	}
	return return_func;
}

static int IsEnd(bst_iterator_ty iter , const bst_ty *bst)
{
	return (BstIterIsEqual(iter , BstEnd(bst)));
}


static int IsMatch(const bst_ty *bst, void *data , bst_iterator_ty iter)
{
	assert(NULL != bst);
	assert(NULL != data);
	assert(NULL != iter);
	
	return (0 == bst->cmp(data , BstGetData(iter) , bst->params));
}


bst_iterator_ty BstFind(const bst_ty *bst, void *data)
{
	bst_iterator_ty run_iter = NULL;
	bst_iterator_ty temp_iter = NULL;
	int side_flag = 0;
	assert(NULL != bst);
	assert(NULL != data);
	run_iter = GetChildren(bst->dummy_root)[LEFT];
	
	while(TRUE)
	{
		if(IsMatch(bst , data , run_iter))
		{
			return run_iter;
		}
		
		side_flag = Flag(bst , data , run_iter);
		temp_iter = GetChildren(run_iter)[side_flag];
		
		if(NULL == temp_iter)
		{
			return temp_iter;
		}
		
		run_iter = temp_iter;
	}	
}


static int IsLeaf(bst_iterator_ty position)
{
	assert(NULL != position);
	return (NULL == GetChildren(position)[LEFT] &&
			NULL == GetChildren(position)[RIGHT]);
}


static void SwapAndDelete(bst_iterator_ty position ,
										bst_iterator_ty swap_node)
{
	bst_iterator_ty save_parent = NULL;
	position->data = BstGetData(swap_node);
	
	if(IsLeaf(swap_node))
	{
		save_parent = GetParent(swap_node);
		save_parent->children[MatchSide(swap_node)] = NULL;
		free(swap_node);
	}
	else if (NULL == GetChildren(GetParent(swap_node))[LEFT])
	{
		swap_node->parent->children[MatchSide(swap_node)] =
						GetChildren(GetParent(swap_node))[RIGHT];	
	}
	else
	{		
		swap_node->parent->children[MatchSide(swap_node)] =
						GetChildren(GetParent(swap_node))[LEFT];
	}
	
}


void *BstRemove(bst_iterator_ty position)
{

	bst_iterator_ty swap_node = NULL;
	bst_iterator_ty save_parent = NULL;
	void *ret = NULL;
	assert(NULL != position);
	
	ret = BstGetData(position);
	
	if(IsLeaf(position))
	{
		save_parent = GetParent(position);
		save_parent->children[MatchSide(position)] = NULL;
		free(position);
		return ret;
	}
	else if(NULL == position->children[RIGHT])
	{
		swap_node = BstGetPrev(position);
	}
	else
	{
		swap_node = BstGetNext(position);
	}
	
	SwapAndDelete(position , swap_node);
	return ret;
}
























