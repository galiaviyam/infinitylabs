/*****************************************/
/*   Developer: Gali Aviyam	           	 */
/*   Project: Singly Linked list         */				         
/*   Date: 04/12/22	                	 */
/*   Reviewer: Shauli                    */
/*****************************************/

#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "slist.h"/*header file*/

typedef struct slist_node
{
	void *data;
	struct slist_node *next;
}slist_node_t;

struct slist
{
	slist_node_t *head;
	slist_node_t *end;
};

typedef enum
{
	SUCCESS = 0,
	FAIL
} status_t;

slist_t *SlistCreate(void)
{
	slist_node_t *dummy = NULL;
	slist_t *list = (slist_t *)malloc(sizeof(slist_t));
	if (NULL == list)
	{
		return NULL;
	}
	
	dummy = (slist_node_t *)malloc(sizeof(slist_node_t));
	if (NULL == dummy)
	{
		free(list);
		list = NULL;
		
		return NULL;
	}
	
	dummy->data = list;
	dummy->next = NULL;
	
	list->head = dummy;
	list->end = dummy;
	
	return list;
}

void SlistDestroy(slist_t *list)
{
	slist_iter_t curr = NULL;
	slist_iter_t next = NULL;
	
	assert(NULL != list);
	
	curr = SlistBegin(list);
	
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	free(list);
	list = NULL;
}

slist_iter_t SlistInsertBefore(slist_iter_t where, void *data)
{
	slist_node_t *new = NULL;
	
	assert(NULL != where);
	assert(NULL != data);
	
	new = (slist_node_t *)malloc(sizeof(slist_node_t));
	if (NULL == new)
	{
		return NULL;
	}
	
	new->data = where->data;
	new->next = where->next;
	
	if (NULL == where->next)
	{
		((slist_t *)(where->data))->end = new;
	}
	
	where->data = data;
	where->next = new;
		
	return where;
}

slist_iter_t SlistRemove(slist_iter_t where)
{
	slist_node_t *tmp = NULL;
	
	assert(NULL != where);
	
	tmp = where->next;
	
	where->data = tmp->data;
	where->next = tmp->next;
	
	if (NULL == where->next)
	{
		((slist_t *)(where->data))->end = where;
	}

	free(tmp);
	tmp = NULL;
	
	return where;
}

slist_iter_t SlistFind(const slist_iter_t from, const slist_iter_t to, 
					   slist_is_match_t is_match, void *param)
{
	slist_iter_t runner = NULL;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != is_match);
	assert(NULL != param);
	
	runner = from;
	
	while (runner != to && !is_match(runner->data, param))
	{
		runner = runner->next;
	}
	
	return runner;
}

int SlistForEach(slist_iter_t from, slist_iter_t to, 
			     slist_do_action_t do_action, void *param)
{
	slist_iter_t runner = NULL;
	status_t status = SUCCESS;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != do_action);
	assert(NULL != param);
	
	runner = from;
	
	while (SUCCESS == status && runner != to)
	{
		status = do_action(runner->data, param);
		runner = runner->next;
	}
	
	return status;
}

void *SlistGetVal(const slist_iter_t iter)
{
	assert(NULL != iter);
	
	return (iter->data);
}

slist_iter_t SlistSetVal(slist_iter_t iter, void *data)
{
	assert(NULL != iter);
	assert(NULL != data);
	
	iter->data = data;
	
	return iter;
}

size_t SlistCount(const slist_t *list)
{
	size_t count = 0;
	slist_iter_t runner = NULL;
	assert(NULL != list);
	runner = SlistBegin(list);
	
	while (SlistEnd(list) != runner)
	{
		++count;
		runner = runner->next;
	}
	
	return count;
}

int SlistIterIsEqual(const slist_iter_t one, const slist_iter_t other)
{
	assert(NULL != one);
	assert(NULL != other);
	
	return(one == other);
}

int SlistIsEmpty(const slist_t *list)
{
	assert(NULL != list);
	
	return (list->head == list->end);
}

slist_iter_t SlistBegin(const slist_t *list)
{
	assert(NULL != list);
	
	return (list->head);
}

slist_iter_t SlistEnd(const slist_t *list)
{
	assert(NULL != list);
	
	return (list->end);
}

slist_t *SlistAppend(slist_t *dest, slist_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	dest->end->data = src->head->data;
	dest->end->next = src->head->next;

	dest->end = src->end;

	src->head->data = src;
	src->head->next = NULL;

	src->end = src->head;
	
	return dest; 
}
