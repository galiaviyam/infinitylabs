/*****************************************/
/*   Developer: Gali Aviyam              */
/*   Project: Queue		 	   		     */				         
/*   Date: 12/12/22		            	 */
/*   Reviewer: Vladimir     			 */
/*****************************************/

#include <stddef.h>	/*size_t*/
#include <stdlib.h>	/*malloc*/
#include <assert.h>	/*assert*/
#include <stdio.h>	/*printf*/

#include "slist.h" /*slist library*/
#include "queue.h"/*header file*/

#define ARR_SIZE 6

static void TestQueueEnqueue(queue_t *queue, size_t *arr);
static void TestQueueDequeue(queue_t *queue);
static void TestQueuePeek(queue_t *queue ,int expected_result);
static void TestQueueAppend(void);
static void TestNumResultEqual(size_t result, size_t expected_result);
static void TestResultNotNull(void *result);
static void TestBoolResult(int result);

enum status
{
	SUCCESS = 0,
	FAIL = 1
};


int main(void)
{
	size_t arr[ARR_SIZE] = {1, 2, 3, 4, 5, 6};
	
	queue_t *queue = QueueCreate();
	printf("create: ");
	TestResultNotNull(queue);
	
	printf("is empty: ");
	TestBoolResult(QueueIsEmpty(queue));
	printf("\n");
	TestQueueEnqueue(queue, arr);
	
	printf("is not empty: ");
	TestBoolResult(!QueueIsEmpty(queue));
	printf("\n");
	
	TestQueueDequeue(queue);
	TestQueueAppend();
	
	QueueDestroy(queue);
	return SUCCESS;
}

static void TestQueueEnqueue(queue_t *queue, size_t *arr)
{
	size_t i = 0;
	size_t i_max = 5;
	
	printf("Enqueue\n");
	for (i = 0; i <= i_max; ++i)
	{
		QueueEnqueue(queue, (arr + i));
		printf("test %lu: ", i+1);
		TestNumResultEqual(QueueSize(queue), i+1);
	}
	printf("\npeek: ");
	TestNumResultEqual(*(size_t *)QueuePeek(queue), 1);
	printf("\n");
}

static void TestQueueDequeue(queue_t *queue)
{
	size_t i = 0;
	size_t i_max = 3;
	
	printf("Dequeue\n");
	for (i = 1; i <= i_max; ++i)
	{
		QueueDequeue(queue);
		printf("test %lu: ", i);
		TestNumResultEqual(QueueSize(queue), ARR_SIZE - i);
	}
}

static void TestQueuePeek(queue_t *queue ,int expected_result)
{
	printf("Peek: ");
	TestNumResultEqual(*(int *)QueuePeek(queue), expected_result);
}

static void TestQueueAppend(void)
{
	queue_t *dest_queue = QueueCreate();
	queue_t *src_queue = QueueCreate();
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	
	QueueEnqueue(dest_queue, &num1);
	QueueEnqueue(dest_queue, &num2);
	
	QueueEnqueue(src_queue, &num3);
	QueueEnqueue(src_queue, &num4);
	
	dest_queue = QueueAppend(dest_queue, src_queue);
	
	printf("\ntesting append:\n");
	printf("dest new size result: ");
	TestNumResultEqual(QueueSize(dest_queue), 4);
	
	printf("src empty test result: ");
	TestBoolResult(QueueIsEmpty(src_queue));
	
	QueueDequeue(dest_queue);
	QueueDequeue(dest_queue);
	
	printf("\npeek dest: ");
	TestQueuePeek(dest_queue, 3);
	
	QueueDestroy(src_queue);

	QueueDestroy(dest_queue);
	
}

static void TestBoolResult(int result)
{
	if (result)
	{
		printf("\033[0;32mPASSED\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAILED\033[0m\n");
	}
}

static void TestNumResultEqual(size_t result, size_t expected_result)
{
	if (result == expected_result)
	{
		printf("\033[0;32mPASSED\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAILED\033[0m\n");
	}
}

static void TestResultNotNull(void *result)
{
	if (NULL != result)
	{
		printf("\033[0;32mPASSED\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAILED\033[0m\n");
	}
}
