/*****************************************/
/*   Developer: Gali Aviyam              */
/*   Project: Queue		 	   		     */				         
/*   Date: 12/12/22		            	 */
/*   Reviewer: Vladimir     			 */
/*****************************************/

#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "slist.h" /*slist library*/
#include "queue.h"/*header file*/

struct queue
{
	slist_t *queue;
};

queue_t *QueueCreate(void)
{
	queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
	if(NULL == queue)
	{
		return NULL;
	}
	
	queue->queue = SlistCreate();
	if(NULL == queue->queue)
	{
		free(queue);
		queue = NULL;
		return NULL;
	}
	
	return queue;
}

void QueueDestroy(queue_t *queue)
{
	assert(NULL != queue);

	SlistDestroy(queue->queue);
	queue->queue = NULL;
	
	free(queue);
	queue = NULL;
}

int QueueEnqueue(queue_t *queue, void *data)
{
	assert(NULL != queue);
	assert(NULL != data);

	return (NULL != SlistInsertBefore(SlistEnd(queue->queue), data));
}

void QueueDequeue(queue_t *queue)
{
	assert(NULL != queue);
	
	SlistRemove(SlistBegin(queue->queue));
}

void *QueuePeek(const queue_t *queue)
{
	assert(NULL != queue);
	
	return (SlistGetVal(SlistBegin(queue->queue)));
}

int QueueIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);
	
	return SlistIsEmpty(queue->queue);
}

size_t QueueSize(const queue_t *queue)
{
	assert(NULL != queue);
	
	return SlistCount(queue->queue);
}

queue_t *QueueAppend(queue_t *dest, queue_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	dest->queue = SlistAppend(dest->queue, src->queue);
	
	return dest;
}
