/****************************************/
/*	 Developer: Gali Aviyam				*/
/*   Project: doubly linked list		*/
/*   Last Modified:	19/12/22			*/
/*	 Reviewer: Ariel Biton				*/
/****************************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdbool.h> /* bool */
#include "dlist.h" /* header file */

#define IS_DUMMY(node) (NULL == ((node)->next) || (NULL == (node)->prev))

typedef struct dlist_node
{
	void *data;
	struct dlist_node *prev;
	struct dlist_node *next;
}dlist_node_t;

struct dlist
{
	dlist_node_t head;
	dlist_node_t tail;
};

enum status
{
	SUCCESS = 0,
	FAIL
};

static void InitNode(dlist_node_t *current, dlist_node_t *next, 
												dlist_node_t *prev, void *data);
												
static void ConnectNodes(dlist_node_t *node1, dlist_node_t *node2);
static dlist_node_t *FindDummy(dlist_node_t *where);
static dlist_iter_t NodeToIter(dlist_node_t *node);
static dlist_node_t *IterToNode(dlist_iter_t iter);
static void RemoveHelper(dlist_node_t *to_remove);
static int CountNodes(void *data, void *param);

/*------------------------------DlistCreate-----------------------------------*/
dlist_t *DlistCreate(void)
{
	dlist_t *list = (dlist_t *)malloc(sizeof(dlist_t));
	if (NULL == list)
	{
		return NULL;
	}

	InitNode(&(list->head), &(list->tail), NULL, list);
	InitNode(&(list->tail), NULL, &(list->head), list);
	
	return list;
}

/*------------------------------DlistDestroy---------------------------------*/
void DlistDestroy(dlist_t *list)
{	
	assert(NULL != list);
	
	while (!DlistIsEmpty(list))
	{
		DlistRemove(DlistBegin(list));
	}
	
	free(list);
	list = NULL;
}

/*------------------------------DlistBegin---------------------------------*/
dlist_iter_t DlistBegin(const dlist_t *list)
{
	assert(NULL != list);
	
	return (DlistNext(NodeToIter((dlist_node_t *)&list->head)));
}

/*------------------------------DlistEnd---------------------------------*/
dlist_iter_t DlistEnd(const dlist_t *list)
{
	assert(NULL != list);
	
	return (NodeToIter((dlist_node_t *)&list->tail));
}

/*------------------------------DlistNext---------------------------------*/
dlist_iter_t DlistNext(dlist_iter_t current)
{
	assert(NULL != current);
	return (NodeToIter(IterToNode(current)->next));
}

/*------------------------------DlistPrev---------------------------------*/
dlist_iter_t DlistPrev(dlist_iter_t current)
{
	assert(NULL != current);
	return (NodeToIter(IterToNode(current)->prev));
}

/*------------------------------DlistPushFront--------------------------------*/
dlist_iter_t DlistPushFront(dlist_t *list, void *data)
{
	assert(NULL != list);
	assert(NULL != data);
	
	return ((dlist_iter_t)DlistInsertBefore(DlistBegin(list), data));
}

/*------------------------------DlistPushBack---------------------------------*/
dlist_iter_t DlistPushBack(dlist_t *list, void *data)
{
	assert(NULL != list);
	assert(NULL != data);
	
	return ((dlist_iter_t)DlistInsertBefore(DlistEnd(list), data));
}

/*------------------------------DlistPopFront---------------------------------*/
void *DlistPopFront(dlist_t *list)
{
	void *data = NULL;
	dlist_iter_t begin = NULL;
	
	assert(NULL != list);
	
	begin = DlistBegin(list);
	
	data = DlistGetVal(begin);
	
	DlistRemove(begin);
	
	return data;
}

/*------------------------------DlistPopBack---------------------------------*/
void *DlistPopBack(dlist_t *list)
{
	void *data = NULL;
	dlist_iter_t end = NULL;

	assert(NULL != list);
	
	end = DlistEnd(list);
	
	data = DlistGetVal(DlistPrev(end));
	
	DlistRemove(DlistPrev(end));
	
	return data;
}

/*------------------------------DlistInsertBefore-----------------------------*/
dlist_iter_t DlistInsertBefore(dlist_iter_t where, void *data)
{
	dlist_node_t *new_node = NULL;
	
	assert(NULL != where);
	assert(NULL != data);
	
	new_node = (dlist_node_t *)malloc(sizeof(dlist_node_t));
	if (NULL == new_node)
	{
		return ((dlist_iter_t)FindDummy(where));
	}
	
	InitNode(new_node, IterToNode(where), IterToNode(DlistPrev(where)), data);

	ConnectNodes(IterToNode(DlistPrev(where)), new_node);
	ConnectNodes(new_node, IterToNode(where));

	return (NodeToIter(new_node));
}

/*------------------------------DlistRemove---------------------------------*/
dlist_iter_t DlistRemove(dlist_iter_t where)
{
	dlist_iter_t new = NULL;
	
	assert(NULL != where);
	
	new = DlistNext(where);
	
	RemoveHelper(IterToNode(where));
	
	return NodeToIter(new);
}

/*---------------------------------DlistFind--------------------------------*/
dlist_iter_t DlistFind(const dlist_iter_t from, const dlist_iter_t to, 
					   dlist_is_match_t is_match, void *param)
{
	dlist_iter_t runner = NULL;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != is_match);
	
	runner = from;
	
	while (!DlistIterIsEqual(runner, to) && !is_match(runner->data, param))
	{
		runner = DlistNext(runner);
	}
	
	return runner;
}					   

/*---------------------------------DlistMultiFind-----------------------------*/
int DlistMultiFind(dlist_t *result_list ,const dlist_iter_t from,
 		   const dlist_iter_t to, dlist_is_match_t is_match, void *param)
{
	int status = FAIL;
	dlist_node_t *runner = NULL;
	 
	assert(NULL != result_list);
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != is_match);
	
	runner = IterToNode(from);
	
	while (!DlistIterIsEqual(runner, to))
	{
		if (is_match(runner->data, param))
		{
			DlistPushFront(result_list, runner->data);
			status = SUCCESS;
		}	
		
		runner = DlistNext(runner);
	}
	
	return status;
}

/*---------------------------------DlistForEach------------------------------*/
int DlistForEach(dlist_iter_t from, dlist_iter_t to, 
			     dlist_do_action_t do_action, void *param)
{
	int status = SUCCESS;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != do_action);
		
	while (SUCCESS == status && !DlistIterIsEqual(from, to))
	{
		status = do_action(from->data, param);
		from = DlistNext(from);
	}
	
	return status;
}

/*---------------------------------DlistSplice-----------------------------*/
dlist_iter_t DlistSplice(dlist_iter_t from, dlist_iter_t to,
														    dlist_iter_t where)
{
	dlist_node_t *to_prev = NULL;
	dlist_node_t *from_node = NULL;
	dlist_node_t *where_node = NULL;
	
	assert (NULL != from);
	assert (NULL != to);
	assert (NULL != where);
	
	to_prev = DlistPrev(to);
	from_node = IterToNode(from);
	where_node = IterToNode(where);
		
	ConnectNodes(from_node->prev, to);
	ConnectNodes(where_node->prev, from_node);
	ConnectNodes(to_prev, where_node);
	
	return to_prev;
}

/*---------------------------------DlistGetVal--------------------------------*/
void *DlistGetVal(const dlist_iter_t iter)
{
	assert(NULL != iter);
	
	return (IterToNode(iter)->data);
}

/*---------------------------------DlistSetVal--------------------------------*/
dlist_iter_t DlistSetVal(dlist_iter_t iter, void *data)
{
	assert(NULL != iter);
	assert(NULL != data);
	
	IterToNode(iter)->data = data;
	
	return iter;
}

/*---------------------------------DlistCount---------------------------------*/
size_t DlistCount(const dlist_t *list)
{
	int count = 0;
	assert(NULL != list);
	
	DlistForEach(DlistBegin(list), DlistEnd(list), CountNodes, &count);
	return count;
}


/*------------------------------DlistIterIsEqual------------------------------*/
int DlistIterIsEqual(const dlist_iter_t one, const dlist_iter_t other)
{
	assert(NULL != one);
	assert(NULL != other);
	
	return(one == other);
}

/*------------------------------DlistIsEmpty---------------------------------*/
int DlistIsEmpty(const dlist_t *list)
{
	assert(NULL != list);
	
	return (IS_DUMMY(list->head.next));
}

/*----------------------------Helper functions--------------------------------*/
static dlist_iter_t NodeToIter(dlist_node_t *node)
{
	dlist_iter_t iter = node;
	return iter;
}

static dlist_node_t *IterToNode(dlist_iter_t iter)
{
	dlist_node_t *node = iter;
	return node;
}

static dlist_node_t *FindDummy(dlist_node_t *where)
{
	assert(NULL != where);
	
	while (NULL != where->data)
	{
		where = DlistNext(where);
	}
	
	return where;
}

static void InitNode(dlist_node_t *current, dlist_node_t *next, 
												dlist_node_t *prev, void *data)
{
	current->next = next;
	current->prev = prev;
	current->data = data;
}

static void ConnectNodes(dlist_node_t *node1, dlist_node_t *node2)
{
	node1->next = node2;
	node2->prev = node1;
}

static void RemoveHelper(dlist_node_t *to_remove)
{
	ConnectNodes(to_remove->prev, to_remove->next);

	free(to_remove);
	to_remove = NULL;
}

static int CountNodes(void *data, void *param)
{
	(void)data;
	*(int *)param += 1;
	
	return SUCCESS;
}
