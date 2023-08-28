/*****************************************/
/*										 */   
/*	 Developer: Gali Aviyam				 */
/*   Project: sorted list		  	 	 */
/*   Last Modified:	20/12/22			 */
/*	 Reviewer: Sveta					 */
/*					 					 */
/*****************************************/

#include <stdio.h>			/* printf */
#include <stdbool.h>		/* bool */
#include <assert.h>			/* assert */

#include "sort_list.h"      /* sorted linked list */

static void TestNumResultEqual(size_t result, size_t expected_result);
static void TestResultNotNull(void *result);
static void TestBoolResult(int result);
static void TestStatusResult(int result);
static int CmpFunc(const void *a, const void *b);
static int MultipleValByNum(void *val, void *num);
static int CompareInt(const void* val, void* cmp);
static int PrintInt(void *data, void *param);
static void TestSortListCreate(void);
static void IntegrationTest1(void);
static void CountTest(sort_list_t *list, size_t num_of_nodes);
static void TestSortListRemove(sort_list_t *list, size_t num_of_nodes);
static void SortListPopBackTest(sort_list_t *list, void *expected_data);
static void SortListPopFrontTest(sort_list_t *list, void *expected_data);
static void TestListForEach(void);
static void TestListFindIf(void);
static void TestListFind(void);
static void IntegrationTest2(void);

enum status
{
	SUCCESS = 0,
	FAIL = 1
};

int main(void)
{
	TestSortListCreate();
	IntegrationTest1();
	TestListForEach();
	TestListFindIf();
	TestListFind();
	IntegrationTest2();
	
	return SUCCESS;
}

static void TestSortListCreate(void)
{
	sort_list_t *list = SortListCreate(CmpFunc);
	
	printf("create: ");
	TestResultNotNull(list);
	
	printf("is empty: ");
	TestBoolResult(SortListIsEmpty(list));
	printf("\n");
	
	SortListDestroy(list);	
}

static void IntegrationTest1(void)
{
	sort_list_t *sort_list = SortListCreate(CmpFunc);
	sort_list_iter_t s_iter = {0};
	
	size_t i = 0;
	
	size_t arr[10] = {10, 5, 9, 4, 2, 6, 8, 7, 3, 1};
	size_t expected[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	
	printf("**********Integration Test 1**********\n");
	printf("-----insert-----\n");
	for (i = 0; i < 10; ++i)
	{
		s_iter = SortListBegin(sort_list);
		s_iter = SortListInsert(sort_list, (arr + i));
	}
	
	s_iter = SortListBegin(sort_list);
	for (i = 1; i <= 10; ++i)
	{
		printf("test %lu: ", i);
		TestNumResultEqual(*(size_t *)SortlistGetVal(s_iter), i);
		s_iter = SortListNext(s_iter);
	}
	
	CountTest(sort_list, 10);
	
	SortListPopFrontTest(sort_list, (void *)&expected[0]);
	SortListPopBackTest(sort_list, (void *)&expected[9]);
	
	TestSortListRemove(sort_list, 8);

	SortListDestroy(sort_list);	
}

static void CountTest(sort_list_t *list, size_t num_of_nodes)
{
	printf("\ncount: ");
	TestNumResultEqual(SortListCount(list), num_of_nodes);
}

static void TestSortListRemove(sort_list_t *list, size_t num_of_nodes)
{
	sort_list_iter_t s_iter = {0};
	size_t i = 0;
	size_t i_max = 3;
	
	printf("\nremove\n");
	for (i = 1; i <= i_max; ++i)
	{
		s_iter = SortListBegin(list);
		s_iter = SortListRemove(s_iter);
		printf("test %lu: ", i);
		TestNumResultEqual(SortListCount(list), num_of_nodes - i);
	}
}

static void SortListPopBackTest(sort_list_t *list, void *expected_data)
{
	printf("\nPop Back: ");
	TestNumResultEqual(*(int *)SortListPopBack(list), *(size_t *)expected_data);
}

static void SortListPopFrontTest(sort_list_t *list, void *expected_data)
{
	printf("\nPop Front: ");
	TestNumResultEqual(*(int *)SortListPopFront(list), *(size_t *)expected_data);
}

static void TestListForEach(void)
{		
	sort_list_t *sort_list = SortListCreate(CmpFunc);
	sort_list_iter_t iter_from = SortListBegin(sort_list);
	sort_list_iter_t iter_to = SortListEnd(sort_list);
	size_t i = 0;
	int num = 3;
	
	size_t arr[10] = {10, 5, 9, 4, 2, 6, 8, 7, 3, 1};
	
	for (i = 0; i < 10; ++i)
	{
		iter_from = SortListInsert(sort_list, (arr + i));
	}
	
	iter_from = SortListBegin(sort_list);
	
	printf("\nTest ForEach: ");
	TestStatusResult(SortListForEach(iter_from, iter_to, &MultipleValByNum, &num));
	
	for (i = 1; i <= 10; ++i)
	{
		printf("test %lu: ", i);
		TestNumResultEqual(*(size_t *)SortlistGetVal(iter_from), i*num);
		iter_from = SortListNext(iter_from);
	}
	
	SortListDestroy(sort_list);	
}

static void TestListFindIf(void)
{
	sort_list_t *sort_list = SortListCreate(CmpFunc);
	sort_list_iter_t iter_from = SortListBegin(sort_list);
	sort_list_iter_t iter_to = SortListEnd(sort_list);
	sort_list_iter_t iter_found = {0};
	
	size_t i = 0;
	int num = 3;
	
	size_t arr[10] = {10, 5, 9, 4, 2, 6, 8, 7, 3, 1};
	
	for (i = 0; i < 10; ++i)
	{
		iter_from = SortListInsert(sort_list, (arr + i));
	}
	
	iter_from = SortListBegin(sort_list);
	
	printf("\nTest FindIf: ");
	iter_found = SortListFindIf(iter_from, iter_to, &CompareInt, &num);
	TestNumResultEqual(*(int *)SortlistGetVal(iter_found), num);
	
	SortListDestroy(sort_list);	
}

static void TestListFind(void)
{
	sort_list_t *sort_list = SortListCreate(CmpFunc);
	sort_list_iter_t iter_from = SortListBegin(sort_list);
	sort_list_iter_t iter_to = SortListEnd(sort_list);
	sort_list_iter_t iter_found = {0};
	
	size_t i = 0;
	int num = 3;
	
	size_t arr[10] = {10, 5, 9, 4, 2, 6, 8, 7, 3, 1};
	
	for (i = 0; i < 10; ++i)
	{
		iter_from = SortListInsert(sort_list, (arr + i));
	}
	
	iter_from = SortListBegin(sort_list);
	
	printf("\nTest Find: ");
	iter_found = SortListFind(sort_list, iter_from, iter_to, &num);
	TestNumResultEqual(*(int *)SortlistGetVal(iter_found), num);
	
	SortListDestroy(sort_list);	
}

static void IntegrationTest2(void)
{
	sort_list_t *even_list = SortListCreate(CmpFunc);
	sort_list_t *odd_list = SortListCreate(CmpFunc);
	int count = 1;
	size_t i = 0;
	int tester[100] = {0};

	printf("**********Integration Test 2**********\n");

	for(i = 0; i < 91; i+=2)
	{	
		tester[i] = i;
	}
	
	for(i = 0; i < 91; i+=2)
	{	
		SortListInsert(even_list, (tester + i));
	}
	
	for(i = 1; i < 100; i+=2)
	{	
		tester[i] = i;
	}
	
	for (i = 1; i < 100; i+=2)
	{
		SortListInsert(odd_list, (tester + i));
	}
	
	printf("-----Print list with ForEach-----\n");
	printf("even list\n");
	SortListForEach(SortListBegin(even_list), SortListEnd(even_list),
							 &PrintInt, &count);
	printf("\n");
	printf("odd list\n");
	SortListForEach(SortListBegin(odd_list), SortListEnd(odd_list),
							 &PrintInt, &count);
	printf("\n");
	printf("------merge lists------\n");
	
	SortListMerge(even_list, odd_list);
	TestBoolResult(SortListIsEmpty(odd_list));
	
	printf("-----Print list with ForEach-----\n");

	SortListForEach(SortListBegin(even_list), SortListEnd(even_list),
							 &PrintInt, &count);
	printf("\n");

	SortListDestroy(even_list);
	SortListDestroy(odd_list);
}

/**************************test helper functions*************************/
static int CmpFunc(const void *a, const void *b)
{
	
	return (*(int *)a - *(int *)b);
}

static int MultipleValByNum(void *val, void *num)
{
	(*(int *)val) *= (*(int *)num);
	
	return SUCCESS;
}

static int CompareInt(const void* val, void* cmp)
{
	return (*(int *)val == *(int *)cmp);
}

static int PrintInt(void *data, void *param)
{
	assert(NULL != data);

	printf("%d ", *(char *)data);
	++*(int *)param;

	return SUCCESS;
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
