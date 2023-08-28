/****************************************/
/*   Developer: Gali Aviyam				*/
/*   Project: Priority Queue			*/				         
/*   Date: 28/12/22						*/
/*   Reviewer: Karin					*/
/*										*/
/****************************************/

#include <stddef.h>			/* size_t */
#include <stdlib.h>			/* malloc */
#include <assert.h>			/* assert */

#include "sort_list.h"      /*sorted linked list*/
#include "priority_queue.h"	/* pq header file */

struct ilrd_pq
{
	sort_list_t *sort_list;
};

typedef enum
{
	SUCCESS = 0,
	FAIL
}status_t;

static sort_list_cmp_t PqCmpToSortCmp(pq_cmp_t cmp);
static sort_list_t *PqToSortList(const ilrd_pq_t *queue);

/*------------------------------PQCreate-------------------------------*/
ilrd_pq_t *PQCreate(pq_cmp_t cmp)
{
	ilrd_pq_t *queue = NULL;

	queue = (ilrd_pq_t *)malloc(sizeof(ilrd_pq_t));
	if(NULL == queue)
	{
		return NULL;
	}

	queue->sort_list = SortListCreate(PqCmpToSortCmp(cmp));
	if(NULL == queue->sort_list)
	{
		free(queue);
		queue = NULL;
		return NULL;
	}
	
	return queue;
}

/*------------------------------PQDestroy------------------------------*/
void PQDestroy(ilrd_pq_t *pq)
{
	SortListDestroy(PqToSortList(pq));
	
	free(pq);
	pq = NULL;
}

/*------------------------------PQEnqueue------------------------------*/
int PQEnqueue(ilrd_pq_t *pq, void *data)
{
	int status = FAIL;
	sort_list_iter_t iter = {0};
	
	assert(NULL != pq);
	
	iter = SortListInsert(PqToSortList(pq), data);
	
	if (!SortListIterIsEqual(SortListEnd(PqToSortList(pq)), iter))
	{
		status = SUCCESS;
	}
	
	return (status);
}

/*------------------------------PQDequeue------------------------------*/
void *PQDequeue(ilrd_pq_t *pq)
{
	assert(NULL != pq);
	
	return SortListPopFront(PqToSortList(pq));
}

/*------------------------------PQIsEmpty------------------------------*/
int PQIsEmpty(const ilrd_pq_t *pq)
{
	assert(NULL != pq);
	
	return (SortListIsEmpty(PqToSortList(pq)));
}

/*--------------------------------PQPeek-------------------------------*/
void *PQPeek(const ilrd_pq_t *pq)
{
	assert(NULL != pq);
	
	return (SortlistGetVal(SortListBegin(PqToSortList(pq))));
}

/*--------------------------------PQSize-------------------------------*/
size_t PQSize(const ilrd_pq_t *pq)
{
	assert(NULL != pq);
	
	return (SortListCount(PqToSortList(pq)));
}

/*--------------------------------PQClear-------------------------------*/
void PQClear(ilrd_pq_t *pq)
{
	assert(NULL != pq);
	
	while (!PQIsEmpty(pq))
	{
		PQDequeue(pq);
	}
}

/*--------------------------------PQErase------------------------------*/
void *PQErase(ilrd_pq_t *pq, void *data, pq_is_match_t is_match)
{
	sort_list_iter_t found = {0};
	sort_list_iter_t end = {0};
	void *found_data = NULL;
	
	assert(NULL != pq);
	
	end = SortListEnd(PqToSortList(pq));
	found = SortListFindIf(SortListBegin(PqToSortList(pq)), end, is_match, data);
							
	if (!SortListIterIsEqual(found, end))
	{
		found_data = SortlistGetVal(found);
		SortListRemove(found);
	}
	
	return found_data;
}

/*------------------------------Helpers------------------------------*/

static sort_list_cmp_t PqCmpToSortCmp(pq_cmp_t cmp)
{
	return ((sort_list_cmp_t)cmp);
}

static sort_list_t *PqToSortList(const ilrd_pq_t *queue)
{
	return (queue->sort_list);
}

