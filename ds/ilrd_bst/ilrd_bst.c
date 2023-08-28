/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Binary Search tree		*/
/*   Date:		18/01/23				*/
/*	 Reviewer:	Gal						*/
/*										*/
/****************************************/

#include <assert.h>		/* assert */
#include <stdlib.h>		/* malloc */

#include "ilrd_bst.h"	/* bst header file */

#define ROOT(bst) (bst->end->children[LEFT])
#define WHICH_CHILD(node) ((node) == (node->parent->children[RIGHT]))
#define NUM_OF_CHILD (2)

struct bst_node
{
	void *data;
	bst_node_t *parent;
	bst_node_t *children[NUM_OF_CHILD];
};

struct bst
{
	bst_node_t *end;
	bst_cmp_t cmp;
};

typedef enum direction
{
	LEFT = 0,
	RIGHT
}direction_t;

static bst_iter_t NodeToIter(bst_node_t *node);
static bst_node_t *IterToNode(bst_iter_t iter);
static void InitBST(bst_t *bst, bst_node_t *end, bst_cmp_t cmp);
static void InitNode(bst_node_t *current, bst_node_t *left_child, bst_node_t 
						*right_child, bst_node_t *parent, void *data);
static bst_node_t *CreateLeaf(bst_node_t *parent, int direction, void *data);
static void UpdateParent(bst_node_t *parent, bst_node_t *child, int direction);
static bst_node_t *FindMin(bst_node_t *node);
static bst_node_t *FindMax(bst_node_t *node);
static bst_node_t *FindBiggerParent(bst_node_t *node);
static bst_node_t *FindSmallerParent(bst_node_t *node);
static void RemoveLeaf(bst_node_t *node);
static void RemoveNodeWith1Child(bst_node_t *node);
static void RemoveNodeWith2Children(bst_node_t *node);

/*------------------------------BSTCreate---------------------------------*/
bst_t *BSTCreate(bst_cmp_t cmp)
{
	bst_t *tree = NULL;
	bst_node_t *dummy = NULL;
	
	assert(NULL != cmp);
	
	tree = (bst_t *)malloc(sizeof(bst_t));
	if (NULL == tree)
	{
		return NULL;
	}
	
	dummy = (bst_node_t *)malloc(sizeof(bst_node_t));
	if (NULL == dummy)
	{
		free(tree);
		tree = NULL;
		
		return NULL;
	}
	
	InitBST(tree, dummy, cmp);
	
	return tree;
}

/*------------------------------BSTDestroy---------------------------------*/
void BSTDestroy(bst_t *bst)
{
	bst_node_t *runner = NULL;
	bst_node_t *tmp = NULL;	
	
	runner = ROOT(bst);
	
	while (!BSTIsEmpty(bst))
	{
		if (NULL != runner->children[LEFT])
		{
			runner = runner->children[LEFT];
		}
		else if (NULL != runner->children[RIGHT])
		{
			runner = runner->children[RIGHT];
		}
		else
		{
			tmp = runner;
			runner = runner->parent;
			
			if (WHICH_CHILD(tmp))
			{
				runner->children[RIGHT] = NULL;
			}
			else
			{
				runner->children[LEFT] = NULL;
			}

			free(tmp);
			tmp = NULL;
		}
	}
		
	free(bst->end);
	bst->end = NULL;
	
	free(bst);
	bst = NULL;
}

/*--------------------------------BSTInsert---------------------------------*/
bst_iter_t BSTInsert(bst_t *bst, void *data)
{
	bst_node_t *runner = NULL;
	bst_node_t *parent = NULL;
	int cmp_res = 0;
	int direction = LEFT;
	
	assert(NULL != bst);
	assert(BSTFind(bst, data) == BSTEnd(bst));
	
	runner = ROOT(bst);
	parent = bst->end;
	
	while (NULL != runner)
	{
		parent = runner;
		cmp_res = bst->cmp(data, BSTGetVal(NodeToIter(runner)));
		assert(0 != cmp_res);

		if (0 < cmp_res)
		{
			direction = RIGHT;
			runner = runner->children[RIGHT];
		}
		else
		{
			direction = LEFT;
			runner = runner->children[LEFT];
		}
	}
	
	runner = CreateLeaf(parent, direction, data);
	if (NULL == runner)
	{
		return (BSTEnd(bst));
	}
	
	return (NodeToIter(runner));
}


/*--------------------------------BSTRemove-----------------------------------*/
void BSTRemove(bst_iter_t where)
{
	bst_node_t *node = NULL;
	size_t num_of_children = 0;
	
	assert(NULL != where);
	
	node = IterToNode(where);
	num_of_children = (NULL != node->children[LEFT]) + (NULL != node->children[RIGHT]);
	
	switch (num_of_children)
	{
		case 0:
		{
			RemoveLeaf(node);
			break;
		}
		case 1:
		{
			RemoveNodeWith1Child(node);
			break;
		}
		case 2:
		{
			RemoveNodeWith2Children(node);
			break;
		}
		default:
		{
			break;
		}
	}
}

/*--------------------------------BSTFind-----------------------------------*/
bst_iter_t BSTFind(const bst_t *bst, const void *data)
{
	bst_node_t *runner = NULL;
	bst_node_t *end = NULL;
	bst_node_t *ret_val = NULL;
	int cmp_res = 0;
	
	assert(NULL != bst);
	
	runner = ROOT(bst);
	end = IterToNode(BSTEnd(bst));
	ret_val = end;
	
	while (NULL != runner && ret_val == end)
	{
		cmp_res = bst->cmp(data, runner->data);
		
		if (0 < cmp_res)
		{
			runner = runner->children[RIGHT];
		}
		else if (0 > cmp_res)
		{
			runner = runner->children[LEFT];
		}
		else
		{
			ret_val = runner;
		}
	}
	
	return (NodeToIter(ret_val));
}

/*--------------------------------BSTNext-----------------------------------*/
bst_iter_t BSTNext(bst_iter_t current)
{
	bst_node_t *runner = NULL;
	
	assert(NULL != current);
	
	runner = IterToNode(current);
	
	if (NULL == runner->children[RIGHT])
	{
		if (NULL == runner->parent->parent)
		{
			return (runner->parent);
		}
		else
		{
			runner = FindBiggerParent(runner);
		}
	}
	else
	{
		runner = FindMin(runner->children[RIGHT]);
	}
	
	return (NodeToIter(runner));
}

/*--------------------------------BSTPrev-----------------------------------*/
bst_iter_t BSTPrev(bst_iter_t current)
{
	bst_node_t *runner = NULL;
	
	assert(NULL != current);
	
	runner = IterToNode(current);
	
	if (NULL == runner->children[LEFT])
	{
		if (NULL == runner->parent->parent)
		{
			return (runner->parent);
		}
		else
		{
			runner = FindSmallerParent(runner);
		}
	}
	else
	{
		runner = FindMax(runner->children[LEFT]);
	}
	
	return (NodeToIter(runner));
}

/*------------------------------BSTIsEqual---------------------------------*/
int BSTIsEqual(bst_iter_t one, bst_iter_t other)
{
	assert(NULL != one);
	assert(NULL != other);
	
	return(one == other);
}

/*---------------------------------BSTBegin----------------------------------*/
bst_iter_t BSTBegin(const bst_t *bst)
{
	bst_node_t *first = NULL;
	
	assert(bst);
	
	first = FindMin(ROOT(bst));
	
	return (NodeToIter(first));
}

/*---------------------------------BSTEnd----------------------------------*/
bst_iter_t BSTEnd(const bst_t *bst)
{
	assert(NULL != bst);
	
	return (NodeToIter(bst->end));
}

/*-------------------------------BSTForEach--------------------------------*/
int BSTForEach(bst_iter_t from, bst_iter_t to, bst_callback_t callback,
																	void *param)
{
	int status = 0;
	bst_iter_t iter = {0};
	
	assert(from);
	assert(to);
	assert(callback);
	
	iter = from;
	
	while (NULL != IterToNode(iter)->parent && !BSTIsEqual(iter, to) && !status)
	{
		status = callback(BSTGetVal(iter), param);
		iter = BSTNext(iter);
	}
	
	return status;
}

/*--------------------------------BSTCount---------------------------------*/
size_t BSTCount(const bst_t *bst)
{
	bst_iter_t runner = NULL;
	bst_iter_t end = NULL;
	size_t counter = 0;
	
	assert(NULL != bst);
	
	runner = BSTBegin(bst);
	end = BSTEnd(bst);
	
	while (!BSTIsEqual(runner, end))
	{
		runner = BSTNext(runner);
		++counter;
	}
	
	return counter;
}

/*------------------------------BSTIsEmpty---------------------------------*/
int BSTIsEmpty(const bst_t *bst)
{
	assert(NULL != bst);
	
	return (NULL == ROOT(bst));
}

/*------------------------------BSTGetVal---------------------------------*/
void *BSTGetVal(bst_iter_t iter)
{
	bst_node_t *node = NULL;
	
	assert(NULL != iter);
	
	node = IterToNode(iter);
	
	return (node->data);
}

/**********************************************************************/
/************************** service functions *************************/
/**********************************************************************/

/*----------------------------NodeToIter-------------------------------*/
static bst_iter_t NodeToIter(bst_node_t *node)
{
	assert(NULL != node);
	
	return ((bst_iter_t)node);
}

/*----------------------------IterToNode-------------------------------*/
static bst_node_t *IterToNode(bst_iter_t iter)
{
	assert(NULL != iter);
	
	return ((bst_node_t *)iter);
}

/*----------------------------InitBST-------------------------------*/
static void InitBST(bst_t *bst, bst_node_t *end, bst_cmp_t cmp)
{
	assert(NULL != bst);
	
	bst->cmp = cmp;
	bst->end = end;
	
	InitNode(bst->end, NULL, NULL, NULL, NULL);
}

/*----------------------------InitNode-------------------------------*/
static void InitNode(bst_node_t *current, bst_node_t *left_child, bst_node_t 
						*right_child, bst_node_t *parent, void *data)
{
	current->children[LEFT] = left_child;
	current->children[RIGHT] = right_child;
	current->parent = parent;
	current->data = data;
}

/*----------------------------CreateLeaf-------------------------------*/
static bst_node_t *CreateLeaf(bst_node_t *parent, int direction, void *data)
{
	bst_node_t *node = NULL;

	assert (NULL != parent);
	
	node = (bst_node_t *)malloc(sizeof(bst_node_t));
	if (NULL == node)
	{
		return NULL;
	}
	
	UpdateParent(parent, node, direction);
	
	InitNode(node, NULL, NULL, parent, data);
	
	return node;
}

/*----------------------------UpdateParent-------------------------------*/
static void UpdateParent(bst_node_t *parent, bst_node_t *child, int direction)
{
	assert(NULL != parent);
	
	parent->children[direction] = child;
}

/*------------------------------FindMin---------------------------------*/
static bst_node_t *FindMin(bst_node_t *node)
{
	while (NULL != node->children[LEFT])
	{
		node = node->children[LEFT];
	}
	
	return (node);
}

/*------------------------------FindMax---------------------------------*/
static bst_node_t *FindMax(bst_node_t *node)
{
	while (NULL != node->children[RIGHT])
	{
		node = node->children[RIGHT];
	}
	
	return (node);
}

/*--------------------------FindBiggerParent---------------------------*/
static bst_node_t *FindBiggerParent(bst_node_t *node)
{
	while (WHICH_CHILD(node))
	{
		node = node->parent;
	}
	
	node = node->parent;
	
	return node;
}

/*--------------------------FindSmallerParent---------------------------*/
static bst_node_t *FindSmallerParent(bst_node_t *node)
{
	while (!WHICH_CHILD(node))
	{
		node = node->parent;
	}
	
	node = node->parent;
	
	return node;
}

/*-----------------------------RemoveLeaf------------------------------*/
static void RemoveLeaf(bst_node_t *node)
{
	assert(NULL != node);
	
	UpdateParent(node->parent, NULL, WHICH_CHILD(node));
	free(node);
	node = NULL;
}

/*------------------------RemoveNodeWith1Child-----------------------*/
static void RemoveNodeWith1Child(bst_node_t *node)
{
	direction_t direction = LEFT;
	
	assert(NULL != node);
	
	direction = (NULL == node->children[LEFT]);
	
	UpdateParent(node->parent, node->children[direction], WHICH_CHILD(node));
	node->children[direction]->parent = node->parent;

	free(node);
	node = NULL;
}

/*---------------------RemoveNodeWith2Children--------------------*/
static void RemoveNodeWith2Children(bst_node_t *node)
{
	bst_node_t *next_node = NULL;
	
	assert(NULL != node);
	
	next_node = IterToNode(BSTNext(NodeToIter(node)));
	
	node->data = next_node->data;
	UpdateParent(next_node->parent, next_node->children[RIGHT], 
					WHICH_CHILD(next_node));
	
	if (NULL != next_node->children[RIGHT])
	{
		next_node->children[RIGHT]->parent = next_node->parent;
	}
	
	free(next_node);
	next_node = NULL;
}
