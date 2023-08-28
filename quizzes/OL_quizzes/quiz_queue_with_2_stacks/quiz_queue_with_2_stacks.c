#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc*/
#include <stdio.h> /*printf*/

#include "stack.h"

typedef struct queue
{
	stack_t *stack_in;
	stack_t *stack_out;
}queue_t;

static void Enqueue(queue_t *queue, void *data);
static void *Dequeue(queue_t *queue);
static queue_t *QueueCreate(size_t capacity);
static void QueueDestroy(queue_t *queue);

int main(void)
{
	int values[4] = {0, 1, 2, 3};
	size_t i = 0;
	size_t capacity = 4;
	queue_t *queue = QueueCreate(capacity);

	for (i = 0; i < capacity; ++i)
	{
		Enqueue(queue, &values[i]);
	}
	
	for (i = 0; i < capacity; ++i)
	{
		if (*(int *)Dequeue(queue) == values[i])
		{
			printf("success\n");
		}
		else
		{
			printf("fail\n");
		}
	}
	
	QueueDestroy(queue);


	return 0;
}

static void Enqueue(queue_t *queue, void *data)
{
	assert(NULL != queue);
	assert(NULL != data);

	StackPush(queue->stack_in, data);
}

static void *Dequeue(queue_t *queue)
{
	void *data = NULL;
	
	while (!StackIsEmpty(queue->stack_in))
	{
		StackPush(queue->stack_out, StackPop(queue->stack_in));
	}
	
	data = StackPop(queue->stack_out);
	
	while (!StackIsEmpty(queue->stack_out))
	{
		StackPush(queue->stack_in, StackPop(queue->stack_out));
	}
	
	return data;
}

static queue_t *QueueCreate(size_t capacity)
{
	queue_t *queue = NULL;
	
	queue = (queue_t *)malloc(sizeof(queue_t));
	if (NULL == queue)
	{
		return NULL;
	}
	
	queue->stack_in = StackCreate(capacity);
	if (NULL == queue->stack_in)
	{
		free(queue);
		queue = NULL;
		return NULL;
	}
	
	queue->stack_out = StackCreate(capacity);
	if (NULL == queue->stack_out)
	{
		StackDestroy(queue->stack_in);
		free(queue);
		queue = NULL;
		return NULL;
	}
	
	return queue;		
}


static void QueueDestroy(queue_t *queue)
{
	assert(NULL != queue);

	StackDestroy(queue->stack_in);
	StackDestroy(queue->stack_out);

	free(queue);
	queue = NULL;
}

