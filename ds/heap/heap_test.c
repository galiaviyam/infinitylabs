/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Heap               		*/
/*   Date:		06/02/23				*/
/*	 Reviewer:	Karin					*/
/*										*/
/****************************************/

#include <stdio.h>	/* printf */
#include <assert.h>	/* assert */

#include "heap.h"	/* heap header file*/



static void TestCreateDestroy(void);
static void HeapPushPopTest(void);
static void SizeTest(heap_t *heap, size_t expected);
static void PeekTest(heap_t *heap, int expected);
static void HeapRemoveTest(void);


static void TestNumResultEqual(size_t result, size_t expected_result);
static void TestResultNotNull(void *result);
static void TestBoolResult(int result);
static void TestStatusResult(int result);

static int CmpFunc(const void *heap_data, const void *new_data, void *param);
static int IsMatch(const void *data, void *param);

int main(void)
{
	TestCreateDestroy();
	HeapPushPopTest();
	HeapRemoveTest();
	
	return 0;
}


static void TestCreateDestroy(void)
{
	heap_t *heap = NULL;
		
	heap = HeapCreate(&CmpFunc, NULL);
	
	printf("create: ");
	TestResultNotNull(heap);
	
	printf("is empty: ");
	TestBoolResult(HeapIsEmpty(heap));
	printf("size: ");
	TestNumResultEqual(HeapSize(heap), 0);
	
	printf("\n");

	HeapDestroy(heap);
}

static void HeapPushPopTest(void)
{
	heap_t *heap = NULL;
	size_t i = 0;
	int arr[9] = {5, 9, 4, 2, 6, 8, 7, 3, 1};
	
	printf("----------push----------\n");
	
	heap = HeapCreate(&CmpFunc, NULL);
	if (NULL == heap)
	{
		printf("\033[0;31mCREATE FAILED\033[0m\n");
		return;
	}
	
	for (i = 0; i < 9; ++i)
	{
		printf("test %lu:	", i+1);
		TestStatusResult(HeapPush(heap, (arr + i)));
	}	

	SizeTest(heap, 9);
	PeekTest(heap, (int)9);

	printf("----------pop----------\n");
	
	TestNumResultEqual(*(int *)HeapPop(heap), 9);
	SizeTest(heap, 8);
	PeekTest(heap, (int)8);
	
	HeapDestroy(heap);
}

static void HeapRemoveTest(void)
{
	heap_t *heap = NULL;
	size_t i = 0;
	int arr[9] = {5, 9, 4, 2, 6, 8, 7, 3, 1};
	
	printf("----------remove----------\n");
	
	heap = HeapCreate(&CmpFunc, NULL);
	if (NULL == heap)
	{
		printf("\033[0;31mCREATE FAILED\033[0m\n");
		return;
	}
	
	for (i = 0; i < 9; ++i)
	{
		HeapPush(heap, (arr + i));
	}
	
	TestNumResultEqual(*(int *)HeapRemove(heap, (arr + 0), &IsMatch, NULL), 5);
	SizeTest(heap, 8);
	
	HeapDestroy(heap);
}

static void SizeTest(heap_t *heap, size_t expected)
{
	printf("\nsize: ");
	TestNumResultEqual(HeapSize(heap), expected);
}

static void PeekTest(heap_t *heap, int expected)
{
	printf("\npeek: ");
	TestNumResultEqual(*(int *)HeapPeek(heap), expected);
}

/**************************test service functions************************/
static int CmpFunc(const void *heap_data, const void *new_data, void *param)
{
	assert(NULL != heap_data);
	assert(NULL != new_data);
	
	(void)param;
	
	return (*(int *)new_data - *(int *)heap_data);
}

static int IsMatch(const void *data, void *param)
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
