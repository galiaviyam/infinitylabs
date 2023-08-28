#include <stddef.h>	/*size_t*/
#include <stdlib.h>	/*malloc*/
#include <assert.h>	/*assert*/
#include <stdio.h>	/*printf*/

#include "slist.h"/*header file*/

enum status
{
	SUCCESS = 0,
	FAIL = 1
};

static void TestSlistInsert(slist_t *list, size_t *arr);
static void TestSlistRemove(slist_t *list);
static void TestListFindAndIsEqual(slist_t *list);
static void TestListForEachAndSet(slist_t *list);
static int CompareInt(const void* val, void* cmp);
static int MultipleValByNum(void *val, void *num);
static void TestNumResultEqual(size_t result, size_t expected_result);
static void TestResultNotNull(void *result);
static void TestBoolResult(int result);
static void TestStatusResult(int result);

int main(void)
{
	size_t arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	
	slist_t *sl_list = SlistCreate();
	printf("create: ");
	TestResultNotNull(sl_list);
	
	printf("is empty: ");
	TestBoolResult(SlistIsEmpty(sl_list));
	printf("\n");
	
	TestSlistInsert(sl_list, arr);
	
	printf("is not empty: ");
	TestBoolResult(!SlistIsEmpty(sl_list));
	printf("\n");
	
	TestSlistRemove(sl_list);

	TestListFindAndIsEqual(sl_list);
	
	TestListForEachAndSet(sl_list);
	
	SlistDestroy(sl_list);
	return SUCCESS;
}

static void TestSlistInsert(slist_t *list, size_t *arr)
{
	slist_iter_t iterator = NULL;
	
	size_t i;
	size_t i_max = 5;
	
	printf("insert to end\n");
	for (i = 1; i <= i_max; ++i)
	{
		iterator = SlistEnd(list);
		iterator = SlistInsertBefore(iterator, (arr + i));
		printf("test %lu: ", i);
		TestNumResultEqual(SlistCount(list), i);
	}
	printf("\ninsert to start\n");
	for (i = 1; i <= i_max; ++i)
	{
		iterator = SlistBegin(list);
		iterator = SlistInsertBefore(iterator, (arr + i));
		printf("test %lu: ", i);
		TestNumResultEqual(SlistCount(list), (i_max + i));
	}
	
		
}

static void TestSlistRemove(slist_t *list)
{
	slist_iter_t iterator = NULL;
	size_t i = 0;
	size_t i_max = 3;
	
	printf("remove from start\n");
	for (i = 1; i <= i_max; ++i)
	{
		iterator = SlistBegin(list);
		iterator = SlistRemove(iterator);
		printf("test %lu: ", i);
		TestNumResultEqual(SlistCount(list), 10 - i);
	}
}

static void TestListFindAndIsEqual(slist_t *list)
{
	slist_iter_t iter_search = NULL;
	slist_iter_t iter_from = NULL;
	slist_iter_t iter_to = NULL;
	
	int val = 5;
	
	assert (list);
	
	iter_from = SlistBegin(list);
	iter_to = SlistEnd(list);
	
	iter_search = SlistFind(iter_from, iter_to, &CompareInt, &val);
	printf("\ntest is equal: ");
	TestBoolResult(SlistIterIsEqual(iter_search, iter_search));
	
	printf("test is not equal: ");
	TestBoolResult(!SlistIterIsEqual(iter_from, iter_to));
}

static void TestListForEachAndSet(slist_t *list)
{		
	slist_iter_t iter_search = NULL;
	slist_iter_t iter_from = NULL;
	slist_iter_t iter_to = NULL;
	
	int num = 3;
	int val = 15;
	
	assert (list);
	
	iter_from = SlistBegin(list);
	iter_to = SlistEnd(list);
	
	printf("\nTest ForEach: ");
	TestStatusResult(SlistForEach(iter_from, iter_to, &MultipleValByNum, &num));
	
	iter_search = SlistFind(iter_from, iter_to, &CompareInt, &val);
	printf("test Find: ");
	TestNumResultEqual(*(int *)SlistGetVal(iter_search), val);
	
	printf("\ntest set value: ");
	iter_search = SlistSetVal(iter_search, &num);
	TestNumResultEqual(*(int *)SlistGetVal(iter_search), num);
}

static int CompareInt(const void* val, void* cmp)
{
	return (*(int *)val == *(int *)cmp);
}

static int MultipleValByNum(void *val, void *num)
{
	(*(int *)val) *= (*(int *)num);
	
	return SUCCESS;
}


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

