/****************************************/
/*   Developer: Gali Aviyam				*/
/*   Project: Priority Queue			*/				         
/*   Date: 28/12/22						*/
/*   Reviewer: Karin					*/
/*										*/
/****************************************/

#include <stdio.h>			/* printf */
#include <stdbool.h>		/* bool */
#include <assert.h>			/* assert */

#include "priority_queue.h" /* pq header file */


static void TestNumResultEqual(size_t result, size_t expected_result);
static void TestResultNotNull(void *result);
static void TestBoolResult(int result);
static void TestStatusResult(int result);
static int CmpFunc(const void *a, const void *b);
static int IntIsEqual(const void *data, void *param);
static void TestPQCreate(void);
static void IntegrationTest(void);
static void TestPQSize(ilrd_pq_t *pq, size_t num_of_elems);
static void TestPQDequeue(ilrd_pq_t *pq, void *expected_data);
static void TestPQPeek(ilrd_pq_t *pq, void *expected_data);
static void TestPQClear(ilrd_pq_t *pq);
static void TestPQErase(ilrd_pq_t *pq, void *data, size_t num_of_nodes);
						
enum status
{
	SUCCESS = 0,
	FAIL = 1
};

int main(void)
{
	TestPQCreate();
	IntegrationTest();

	return SUCCESS;
}

static void TestPQCreate(void)
{
	ilrd_pq_t *pqueue = PQCreate(CmpFunc);
	
	printf("create: ");
	TestResultNotNull(pqueue);
	
	printf("is empty: ");
	TestBoolResult(PQIsEmpty(pqueue));
	printf("\n");
	
	PQDestroy(pqueue);	
}

static void IntegrationTest(void)
{
	ilrd_pq_t *pqueue = PQCreate(&CmpFunc);
	size_t i = 0;
	int arr[10] = {10, 5, 9, 4, 2, 6, 8, 7, 3, 1};
	int expected[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	
	printf("**********Integration Test**********\n");
	printf("-----PQEnqueue-----\n");
	for (i = 0; i < 10; ++i)
	{
		printf("test %lu: ", i + 1);
		TestStatusResult(PQEnqueue(pqueue, (arr + i)));
	}
	
	TestPQSize(pqueue, 10);
	TestPQDequeue(pqueue, (void *)&expected[0]);
	TestPQPeek(pqueue, (void *)&expected[1]);
	TestPQErase(pqueue, (void *)&expected[1], 9);
	

	TestPQClear(pqueue);
	printf("\n");
	PQDestroy(pqueue);	
}

static void TestPQSize(ilrd_pq_t *pq, size_t num_of_elems)
{
	printf("\nsize: ");
	TestNumResultEqual(PQSize(pq), num_of_elems);
}

static void TestPQDequeue(ilrd_pq_t *pq, void *expected_data)
{
	printf("\nPQDequeue: ");
	TestNumResultEqual(*(int *)PQDequeue(pq), *(int *)expected_data);
}

static void TestPQPeek(ilrd_pq_t *pq, void *expected_data)
{
	printf("\nPQPeek: ");
	TestNumResultEqual(*(int *)PQPeek(pq), *(int *)expected_data);
}

static void TestPQClear(ilrd_pq_t *pq)
{
	printf("\nPQClear: ");
	PQClear(pq);
	TestBoolResult(PQIsEmpty(pq));
}

static void TestPQErase(ilrd_pq_t *pq, void *data, size_t num_of_nodes)
{
	printf("\nPQErase: ");
	TestNumResultEqual(*(int *)PQErase(pq, data, &IntIsEqual), *(int *)data);
						
	TestNumResultEqual(PQSize(pq), num_of_nodes - 1);
}

/**************************test helper functions*************************/
static int CmpFunc(const void *a, const void *b)
{
	
	return (*(int *)a - *(int *)b);
}

static int IntIsEqual(const void *data, void *param)
{
	assert(NULL != data);
	assert(NULL != param);
	
	return (*(int *)data == *(int *)param);
}

/**************************test utility functions************************/
static void TestStatusResult(int result)
{
	if (result == SUCCESS)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}

static void TestBoolResult(int result)
{
	if (result)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}

static void TestNumResultEqual(size_t result, size_t expected_result)
{
	if (result == expected_result)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}

static void TestResultNotNull(void *result)
{
	if (NULL != result)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}
