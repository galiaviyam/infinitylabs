/****************************************/
/*   Developer: Gali Aviyam				*/
/*   Project: Priority Queue - Heap		*/				         
/*   Date: 07/02/23						*/
/*   Reviewer: Karin					*/
/*										*/
/****************************************/

#include <stddef.h>			/* size_t */
#include <stdlib.h>			/* malloc */
#include <assert.h>			/* assert */

#include "heap.h"			/*heap*/
#include "Heap_PQ.h"	/* pq header file */

struct ilrd_pq
{
	heap_t *heap;
};

typedef enum
{
	SUCCESS = 0,
	FAIL
}status_t;

static heap_t *PqToHeap(const ilrd_pq_t *queue);
static int CmpHeap(const void *heap_data, const void *new_data, void *param);

/*------------------------------PQCreate-------------------------------*/
ilrd_pq_t *PQCreate(pq_cmp_t cmp)
{
	ilrd_pq_t *queue = NULL;

	queue = (ilrd_pq_t *)malloc(sizeof(ilrd_pq_t));
	if(NULL == queue)
	{
		return NULL;
	}

	queue->heap = HeapCreate(&CmpHeap, *(void **)&cmp);
	if(NULL == queue->heap)
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
	assert(NULL != pq);
	
	HeapDestroy(PqToHeap(pq));
	
	free(pq);
	pq = NULL;
}

/*------------------------------PQEnqueue------------------------------*/
int PQEnqueue(ilrd_pq_t *pq, void *data)
{
	assert(NULL != pq);
	
	return (HeapPush(PqToHeap(pq), data));
}

/*------------------------------PQDequeue------------------------------*/
void *PQDequeue(ilrd_pq_t *pq)
{
	assert(NULL != pq);
	assert(!PQIsEmpty(pq));
	
	return HeapPop(PqToHeap(pq));
}

/*------------------------------PQIsEmpty------------------------------*/
int PQIsEmpty(const ilrd_pq_t *pq)
{
	assert(NULL != pq);
	
	return (HeapIsEmpty(PqToHeap(pq)));
}

/*--------------------------------PQPeek-------------------------------*/
void *PQPeek(const ilrd_pq_t *pq)
{
	assert(NULL != pq);
	
	return (HeapPeek(PqToHeap(pq)));
}

/*--------------------------------PQSize-------------------------------*/
size_t PQSize(const ilrd_pq_t *pq)
{
	assert(NULL != pq);
	
	return (HeapSize(PqToHeap(pq)));
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
	assert(NULL != pq);
	assert(NULL != is_match);	
	
	return (HeapRemove(pq->heap, data, is_match, NULL));
}

/*------------------------------Helpers------------------------------*/

static heap_t *PqToHeap(const ilrd_pq_t *queue)
{
	return (queue->heap);
}

static int CmpHeap(const void *heap_data, const void *new_data, void *param)
{
	assert(NULL != param);
	
	return ((*(pq_cmp_t *)&param)(heap_data, new_data));
}
