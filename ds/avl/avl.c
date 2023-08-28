/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	AVL             		*/
/*   Date:		31/01/23				*/
/*	 Reviewer:	Eliran					*/
/*										*/
/****************************************/

#include <assert.h>	/* assert */
#include <stdlib.h>	/* malloc */

#include "avl.h"	/* avl header file */

#define MAX(a,b) (((a) > (b)) ? (a) : (b))

typedef enum direction
{
	LEFT = 0,
	RIGHT,
	NUM_OF_CHILD
}direction_t;

typedef struct avl_node
{
	void *data;
	size_t height;
	struct avl_node *children[NUM_OF_CHILD];
} avl_node_t;

struct avl
{
	avl_node_t *root;
	avl_cmp_t cmp;
};

typedef enum status
{
	SUCCESS = 0,
	FAIL
} status_t;

typedef enum bool
{
	FALSE = 0,
	TRUE
} bool_t;

typedef int (*foreach_t)(avl_node_t *node, avl_callback_t callback, 
						void *param);
						
/*---------------------------Function declerations---------------------------*/

static void RecRemovePostOrder(avl_node_t *node);
static avl_node_t *RecInsert(avl_node_t *node, avl_node_t *curr, avl_cmp_t cmp);
static void InitNode(avl_node_t *node, void *data);

static avl_node_t *RecRemove(avl_node_t *node, void *data, avl_cmp_t cmp);
static avl_node_t *RemoveNode(avl_node_t *node, avl_cmp_t cmp);
static avl_node_t *RemoveLeaf(avl_node_t *node);
static avl_node_t *RemoveNodeWith1Child(avl_node_t *node);
static avl_node_t *RemoveNodeWith2Children(avl_node_t *node, avl_cmp_t cmp);

static size_t GetNumOfChildren(avl_node_t *node);
static avl_node_t *GetMinChild(avl_node_t *node);
						
static int Count(void *data, void *param);
static ssize_t GetHeight(avl_node_t *node);

static int GetBalance(avl_node_t *node);
static avl_node_t *ReBalance(avl_node_t *node);
static avl_node_t *Rotate(avl_node_t *node, direction_t direction);
static void UpdateHeight(avl_node_t *node);

static int ForeachPreOrder(avl_node_t *node, avl_callback_t callback, 
							void *param);
static int ForeachInOrder(avl_node_t *node, avl_callback_t callback, 
							void *param);
static int ForeachPostOrder(avl_node_t *node, avl_callback_t callback, 
							void *param);
static void *RecFind(avl_node_t *node, const void *data, avl_cmp_t cmp, 
					int *found);

/*------------------------------AVLCreate---------------------------------*/
avl_t *AVLCreate(avl_cmp_t cmp)
{
	avl_t *avl = NULL;
	
	assert(NULL != cmp);
	
	avl = (avl_t *)malloc(sizeof(avl_t));
	if (NULL == avl)
	{
		return NULL;
	}
	
	avl->root = NULL;
	avl->cmp = cmp;
	
	return avl;
}

/*------------------------------AVLDestroy---------------------------------*/
void AVLDestroy(avl_t *avl)
{
	assert(NULL != avl);
	
	RecRemovePostOrder(avl->root);
	
	free(avl);
	avl = NULL;
}

/*--------------------------------AVLInsert---------------------------------*/
int AVLInsert(avl_t *avl, void *data)
{
	avl_node_t *new_node = NULL;
	
	assert(NULL != avl);
	
	new_node = (avl_node_t *)malloc(sizeof(avl_node_t));	
	if (NULL == new_node)
	{
		return FAIL;
	}
	
	InitNode(new_node, data);
	
	avl->root = RecInsert(new_node, avl->root, avl->cmp);

	return SUCCESS;
}

/*--------------------------------AVLRemove---------------------------------*/
void AVLRemove(avl_t *avl, void *data)
{
	assert(NULL != avl);

	avl->root = RecRemove(avl->root, data, avl->cmp);
}

/*--------------------------------AVLFind-----------------------------------*/
int AVLFind(const avl_t *avl, const void *data, void **found_data)
{
	int found = FALSE;

	assert(NULL != avl);
	assert(NULL != data);
	assert(NULL != found_data);
		
	*found_data = RecFind(avl->root, data, avl->cmp, &found);
	
	return found;
}

/*-------------------------------AVLForEach--------------------------------*/
int AVLForEach(avl_t *avl, avl_callback_t callback, void *param, order_t order)
{
	avl_node_t *root = NULL;
	int status = SUCCESS;
	
	assert(NULL != avl);
	assert(NULL != callback);

	root = avl->root;
	
	switch (order)
	{
		case PRE:
		{
			status = ForeachPreOrder(root, callback, param);
			break;
		}
		case IN:
		{
			status = ForeachInOrder(root, callback, param);
			break;
		}	
		case POST:
		{
			status = ForeachPostOrder(root, callback, param);
			break;
		}
		default:
		{
			break;
		}
	}
	return status;

}

/*-------------------------------AVLGetHeight-------------------------------*/
ssize_t AVLGetHeight(const avl_t *avl)
{
	ssize_t height = -1;
	assert(NULL != avl);
	
	if (!AVLIsEmpty(avl))
	{
		height = GetHeight(avl->root) - 1;
	}
	
	return height;
}

/*--------------------------------AVLCount---------------------------------*/
size_t AVLCount(const avl_t *avl)
{
	size_t counter = 0;
	
	assert(NULL != avl);
	
	AVLForEach((avl_t *)avl, &Count, &counter, IN);
	
	return counter;
}

/*------------------------------AVLIsEmpty---------------------------------*/
int AVLIsEmpty(const avl_t *avl)
{
	assert(NULL != avl);
	
	return (NULL == avl->root);
}


/**********************************************************************/
/************************** service functions *************************/
/**********************************************************************/

/*------------------------RecRemovePostOrder---------------------------*/
static void RecRemovePostOrder(avl_node_t *node)
{
	if (NULL == node)
	{
		return;
	}
	
	RecRemovePostOrder(node->children[LEFT]);
	RecRemovePostOrder(node->children[RIGHT]);
	
	free(node);
	node = NULL;
}

/*------------------------------RecInsert---------------------------------*/
static avl_node_t *RecInsert(avl_node_t *node, avl_node_t *curr, avl_cmp_t cmp)
{
	direction_t direction = LEFT;
	int cmp_res = 0;
	
	assert(NULL != cmp);
	assert(NULL != node);
	
	if (NULL == curr)
	{
		return node;
	}
	
	cmp_res = cmp(node->data, curr->data);
	assert(cmp_res != 0);
	
	direction = (0 < cmp_res);
	curr->children[direction] = RecInsert(node, curr->children[direction], cmp);
	
	UpdateHeight(curr);
	
	return ReBalance(curr);
}

/*------------------------------RecRemove---------------------------------*/
static avl_node_t *RecRemove(avl_node_t *node, void *data, avl_cmp_t cmp)
{
	direction_t direction = LEFT;
	int cmp_res = 0;
	
	if (NULL == node)
	{
		return node;
	}
	
	cmp_res = cmp(node->data, data);
	if (0 != cmp_res)
	{
		direction = (0 > cmp_res);
		node->children[direction] = 
					RecRemove(node->children[direction], data, cmp);
	}
	else
	{
		node = RemoveNode(node, cmp);
	}
	
	if (NULL == node)
	{
		return node;
	}
	
	UpdateHeight(node);
	
	return ReBalance(node);
}

/*------------------------------RecFind---------------------------------*/
static void *RecFind(avl_node_t *node, const void *data, avl_cmp_t cmp, 
					int *found)
{
	if (NULL == node)
	{
		return NULL;
	}
	
	if (0 == cmp(data, node->data))
	{
		*found = TRUE;
		return node->data;
	}
	else
	{
		return RecFind(node->children[0 < cmp(data, node->data)], 
						data, cmp, found);
	}
}

/*------------------------------GetHeight---------------------------------*/
static ssize_t GetHeight(avl_node_t *node)
{
	if (NULL == node)
	{
		return 0;
	}
	
	return node->height;
}

/*------------------------------Count---------------------------------*/
static int Count(void *data, void *param)
{
	assert(NULL != param);
	
	++(*(size_t *)param);
	(void)data;
	
	return SUCCESS;
}

/*----------------------------ForeachPreOrder---------------------------*/
static int ForeachPreOrder(avl_node_t *node, avl_callback_t callback, 
							void *param)
{
	status_t status = SUCCESS;
	
	if (NULL == node)
	{
		return SUCCESS;
	}
	
	status = callback(node->data, param);
	if (SUCCESS != status)
	{
		return status;
	}
	
	status = ForeachPreOrder(node->children[LEFT], callback, param);
	if (SUCCESS != status)
	{
		return status;
	}
	
	return ForeachPreOrder(node->children[RIGHT], callback, param);
}

/*----------------------------ForeachInOrder---------------------------*/
static int ForeachInOrder(avl_node_t *node, avl_callback_t callback, 
							void *param)
{
	status_t status = SUCCESS;
	
	if (NULL == node)
	{
		return SUCCESS;
	}
	
	status = ForeachInOrder(node->children[LEFT], callback, param);
	if (SUCCESS != status)
	{
		return status;
	}

	status = callback(node->data, param);
	if (SUCCESS != status)
	{
		return status;
	}
		
	return ForeachInOrder(node->children[RIGHT], callback, param);
}

/*----------------------------ForeachPostOrder---------------------------*/
static int ForeachPostOrder(avl_node_t *node, avl_callback_t callback, 
							void *param)
{
	status_t status = SUCCESS;
	
	if (NULL == node)
	{
		return SUCCESS;
	}
	
	status = ForeachPostOrder(node->children[LEFT], callback, param);
	if (SUCCESS != status)
	{
		return status;
	}

	status = ForeachPostOrder(node->children[RIGHT], callback, param);
	if (SUCCESS != status)
	{
		return status;
	}
	
	
	return callback(node->data, param);
}

/*----------------------------InitNode---------------------------*/
static void InitNode(avl_node_t *node, void *data)
{
	assert(NULL != node);
	
	node->data = data;
	node->height = 1;
	node->children[LEFT] = NULL;
	node->children[RIGHT] = NULL;
}

/*----------------------------GetBalance---------------------------*/
static int GetBalance(avl_node_t *node)
{
    assert(NULL != node);
        
    return (GetHeight(node->children[LEFT]) - GetHeight(node->children[RIGHT]));
}

/*----------------------------ReBalance---------------------------*/
static avl_node_t *ReBalance(avl_node_t *node)
{
	int balance = 0;
	
	assert(NULL != node);
	
	balance = GetBalance(node);
	
	if (1 < balance)
	{
		if (GetBalance(node->children[LEFT]) < 0)
		{
			node->children[LEFT] = Rotate(node->children[LEFT], LEFT);
		}
		node = Rotate(node, RIGHT);
	}
	else if (-1 > balance)
	{
		if (GetBalance(node->children[RIGHT]) > 0)
		{
			node->children[RIGHT] = Rotate(node->children[RIGHT], RIGHT);
		}
		node = Rotate(node, LEFT);
	}
	
	return node;
}

/*----------------------------Rotate---------------------------*/
static avl_node_t *Rotate(avl_node_t *node, direction_t direction)
{
    avl_node_t *pivot = NULL;
    avl_node_t *root = NULL;
    direction_t opp_direction = direction ^ 1;
    
    assert(NULL != node);
    
    pivot = node->children[opp_direction];
    root = pivot->children[direction];
 
    pivot->children[direction] = node;
    node->children[opp_direction] = root;
	
	UpdateHeight(node);
	UpdateHeight(pivot);
   	
    return pivot;
}

/*----------------------------UpdateHeight---------------------------*/
static void UpdateHeight(avl_node_t *node)
{
	assert(NULL != node);
	
	node->height = 1 + MAX(GetHeight(node->children[LEFT]), 
							GetHeight(node->children[RIGHT]));
}

/*----------------------------RemoveNode---------------------------*/
static avl_node_t *RemoveNode(avl_node_t *node, avl_cmp_t cmp)
{
	size_t num_of_children = 0;
	
	num_of_children = GetNumOfChildren(node);
	switch (num_of_children)
	{
		case (0):
		{
			node = RemoveLeaf(node);
			break;
		}
		case (1):
		{
			node = RemoveNodeWith1Child(node);
			break;
		}
		case (2):
		{
			node = RemoveNodeWith2Children(node, cmp);
			break;
		}
		default:
		{
			break;
		}	
	}
	
	return node;
}

/*----------------------------GetNumOfChildren---------------------------*/
static size_t GetNumOfChildren(avl_node_t *node)
{
	assert(NULL != node);
	
	return ((NULL != node->children[LEFT]) + (NULL != node->children[RIGHT]));
}

/*----------------------------RemoveLeaf---------------------------*/
static avl_node_t *RemoveLeaf(avl_node_t *node)
{
	assert(NULL != node);
	
	free(node);
	node = NULL;
	
	return node;
}

/*----------------------------RemoveNodeWith1Child---------------------------*/
static avl_node_t *RemoveNodeWith1Child(avl_node_t *node)
{
	avl_node_t *child = NULL;
	int dir = LEFT;
	
	assert(NULL != node);
	
	dir = (NULL == node->children[LEFT]);
	child = node->children[dir];
	*node = *child;
	
	free(child);
	child = NULL;
	
	return node;
}

/*--------------------------RemoveNodeWith2Children-------------------------*/
static avl_node_t *RemoveNodeWith2Children(avl_node_t *node, avl_cmp_t cmp)
{
	avl_node_t *next = NULL;
	
	assert(NULL != node);
	
	next = GetMinChild(node->children[RIGHT]);
	node->data = next->data;
	node->children[RIGHT] = RecRemove(node->children[RIGHT], node->data, cmp);
	
	return node;
}

/*------------------------------GetMinChild------------------------------*/
static avl_node_t *GetMinChild(avl_node_t *node)
{
	if (NULL == node->children[LEFT])
	{
		return node;
	}
	
	return GetMinChild(node->children[LEFT]);
}

