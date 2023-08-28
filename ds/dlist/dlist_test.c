/****************************************/
/*	 Developer: Gali Aviyam				*/
/*   Project: doubly linked list		*/
/*   Last Modified:	20/12/22			*/
/*	 Reviewer: Ariel Biton				*/
/****************************************/

#include <stddef.h>	/*size_t*/
#include <stdlib.h>	/*malloc*/
#include <assert.h>	/*assert*/
#include <stdio.h>	/*printf*/

#include "dlist.h" /*header file*/

static void TestDlistInsert(dlist_t *list, size_t *arr);
static void TestDlistRemove(dlist_t *list);
static void TestListFindAndIsEqual(dlist_t *list);
static void TestListForEachAndSet(dlist_t *list);
static int CompareInt(const void* val, void* cmp);
static int MultipleValByNum(void *val, void *num);
static void DlistPushBackTest(void);
static void DlistPushFrontTest(void);
static void DlistPopBackTest(void);
static void DlistPopFrontTest(void);
static void CountTest(dlist_t *list, size_t num_of_nodes);
static void DlistMultiFindTest(void);
static void DlistSpliceTest(void);
static void IntegrationTest(void);
static void TestNumResultEqual(size_t result, size_t expected_result);
static void TestResultNotNull(void *result);
static void TestBoolResult(int result);
static void TestStatusResult(int result);
static int IsCharEqual(const void *data, void *param);
static int PrintChars(void *data, void *param);
static int IsIntEqual(const void *data, void *param);

enum status
{
	SUCCESS = 0,
	FAIL = 1
};

enum
{
	FALSE = 0,
	TRUE = 1
};

int main(void)
{
	size_t arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	
	dlist_t *list = DlistCreate();
	IntegrationTest();
	
	printf("create: ");
	TestResultNotNull(list);
	
	printf("is empty: ");
	TestBoolResult(DlistIsEmpty(list));
	printf("\n");
	
	TestDlistInsert(list, arr);
	
	printf("is not empty: ");
	TestBoolResult(!DlistIsEmpty(list));
	printf("\n");
	
	DlistPushBackTest();
	DlistPushFrontTest();
	
	DlistPopBackTest();
	DlistPopFrontTest();
	
	CountTest(list, 10);
	
	TestDlistRemove(list);

	TestListFindAndIsEqual(list);
	
	TestListForEachAndSet(list);
	DlistMultiFindTest();

	DlistSpliceTest();	
	
	DlistDestroy(list);
	
	return SUCCESS;
}

static void TestDlistInsert(dlist_t *list, size_t *arr)
{
	dlist_iter_t iter = NULL;
	
	size_t i = 0;
	size_t i_max = 5;
	
	printf("insert to start\n");
	for (i = 0; i < i_max; ++i)
	{
		iter = DlistBegin(list);
		iter = DlistInsertBefore(iter, (arr + i));
		printf("test %lu: ", i + 1);
		TestNumResultEqual(*(size_t *)DlistGetVal(iter), (i + 1));
	}
	
	printf("\ninsert to end\n");
	for (i = 0; i < i_max; ++i)
	{
		iter = DlistEnd(list);
		iter = DlistInsertBefore(iter, (arr + i));
		printf("test %lu: ", i + 1);
		TestNumResultEqual(*(size_t *)DlistGetVal(iter), (i + 1));
	}		
}

static void TestDlistRemove(dlist_t *list)
{
	dlist_iter_t iterator = NULL;
	size_t i = 0;
	size_t i_max = 3;
	
	printf("\nremove\n");
	for (i = 1; i <= i_max; ++i)
	{
		iterator = DlistBegin(list);
		iterator = DlistRemove(iterator);
		printf("test %lu: ", i);
		TestNumResultEqual(DlistCount(list), 10 - i);
	}
}

static void DlistPushBackTest(void)
{
	dlist_t *list = DlistCreate();
	dlist_iter_t iter = DlistBegin(list);
	int data = 80;
	
	iter = DlistPushBack(list, &data);
	printf("\nPush Back: ");
	TestNumResultEqual(*(int *)DlistGetVal(iter), 80);
	
	DlistDestroy(list);
}

static void DlistPushFrontTest(void)
{
	dlist_t *list = DlistCreate();
	dlist_iter_t iter = DlistBegin(list);
	int data = 90;
	
	iter = DlistPushFront(list, &data);
	printf("\nPush Front: ");
	TestNumResultEqual(*(int *)DlistGetVal(iter), 90);
	
	DlistDestroy(list);
}

static void DlistPopBackTest(void)
{
	dlist_t *list = DlistCreate();
	int data = 70;
	
	DlistPushBack(list, &data);
	printf("\nPop Back: ");
	TestNumResultEqual(*(int *)DlistPopBack(list), 70);
	
	DlistDestroy(list);
}

static void DlistPopFrontTest(void)
{
	dlist_t *list = DlistCreate();
	int data = 70;
	
	DlistPushBack(list, &data);
	printf("\nPop Front: ");
	TestNumResultEqual(*(int *)DlistPopFront(list), 70);
	
	DlistDestroy(list);
}

static void TestListFindAndIsEqual(dlist_t *list)
{
	dlist_iter_t iter_search = NULL;
	dlist_iter_t iter_from = NULL;
	dlist_iter_t iter_to = NULL;
	
	int val = 5;
	
	assert (list);
	
	iter_from = DlistBegin(list);
	iter_to = DlistEnd(list);
	
	iter_search = DlistFind(iter_from, iter_to, &CompareInt, &val);
	printf("\ntest is equal: ");
	TestBoolResult(DlistIterIsEqual(iter_search, iter_search));
	
	printf("test is not equal: ");
	TestBoolResult(!DlistIterIsEqual(iter_from, iter_to));
}

static void TestListForEachAndSet(dlist_t *list)
{		
	dlist_iter_t iter_search = NULL;
	dlist_iter_t iter_from = NULL;
	dlist_iter_t iter_to = NULL;
	
	int num = 3;
	int val = 15;
	
	assert (list);
	
	iter_from = DlistBegin(list);
	iter_to = DlistEnd(list);
	
	printf("\nTest ForEach: ");
	TestStatusResult(DlistForEach(iter_from, iter_to, &MultipleValByNum, &num));
	
	iter_search = DlistFind(iter_from, iter_to, &CompareInt, &val);
	printf("test Find: ");
	TestNumResultEqual(*(int *)DlistGetVal(iter_search), val);
	
	printf("\ntest set value: ");
	iter_search = DlistSetVal(iter_search, &num);
	TestNumResultEqual(*(int *)DlistGetVal(iter_search), num);
}

static void CountTest(dlist_t *list, size_t num_of_nodes)
{
	printf("\ncount: ");
	TestNumResultEqual(DlistCount(list), num_of_nodes);
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

static void DlistMultiFindTest(void)
{
	dlist_t *list = DlistCreate();
	dlist_t *find_list = DlistCreate();
	
	int param = 1;
	int num1 = 1;
	int num2 = 2;
	int num3 = 1;
	int num4 = 4;
	int num5 = 1;
	
	DlistPushBack(list, &num1);
	DlistPushBack(list, &num2);
	DlistPushBack(list, &num3);
	DlistPushBack(list, &num4);
	DlistPushBack(list, &num5);
		
	printf("Test MultiFind\n");
	TestStatusResult(DlistMultiFind(find_list, DlistBegin(list), 
						DlistEnd(list), &CompareInt, &param));
	TestNumResultEqual(DlistCount(find_list), 3);

	DlistDestroy(list);
	DlistDestroy(find_list);
}

static void DlistSpliceTest(void)
{
	dlist_t *list = NULL;
    dlist_iter_t iter = NULL;
    dlist_iter_t iter1 = NULL;
    dlist_iter_t iter2 = NULL;
    dlist_iter_t iter3 = NULL;
    dlist_iter_t iter4 = NULL;
    dlist_iter_t iter5 = NULL;
    int num1 = 5;
    int num2 = 7;
    int num3 = 12;
    int num4 = 18;
    int num5 = 14;

    list = DlistCreate();
    
    iter1 = DlistPushBack(list, &num1);
	iter2 = DlistPushBack(list, &num2);
    iter3 = DlistPushBack(list, &num3);
	iter4 = DlistPushBack(list, &num4);
	iter5 = DlistPushBack(list, &num5);
	(void)iter1;
	
	iter = DlistSplice(iter3, iter5, iter2);
	printf("splice\n");
	TestBoolResult(DlistIterIsEqual(iter4, iter));
	TestBoolResult(DlistIterIsEqual(iter2, DlistNext(iter)));

	DlistDestroy(list);
}

/**************************test helper functions*************************/
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

static int IsCharEqual(const void *data, void *param)
{
	int is_equal = TRUE;

	assert(NULL != data);
	
	if ((*(char *)data) != (*(char *)param))
	{
		is_equal = FALSE;
	}
	
	return is_equal;
}

static int PrintChars(void *data, void *param)
{
	assert(NULL != data);

	printf("%d.%c ", *(int *)param, *(char *)data);
	++*(int *)param;

	return SUCCESS;
}

static int IsIntEqual(const void *data, void *param)
{
	int is_equal = TRUE;

	assert(NULL != data);
	assert(NULL != param);
	
	if ((*(int *)data) != (*(int *)param))
	{
		is_equal = FALSE;
	}
	
	return is_equal;
}

static void IntegrationTest(void)
{
	dlist_t *list = NULL;
	dlist_t *splice_test = NULL;
	dlist_t *multi_find_test = NULL;
	dlist_iter_t iter = NULL;
	dlist_iter_t where = NULL;
	dlist_iter_t from = NULL;
	dlist_iter_t to = NULL;
	char tester[26] = {0};
	int splice_tester[10] = {0,1,2,3,4,5,6,9,9,9};
	size_t i = 0;
	int count = 1;
	int status = SUCCESS;
	
	printf("**********IntegrationTest**********\n");
	
	for(i = 0; i < 26; ++i)
	{	
		tester[i] = 'Z' - (char)i;
	}
	
	list = DlistCreate();
	iter = DlistBegin(list);
	
	for (i = 0; i < 26; ++i)
	{
		iter = DlistInsertBefore(iter, &tester[i]);
	}
	

	printf("*****Print list with ForEach*****\n");

	status += DlistForEach(DlistBegin(list), DlistEnd(list), &PrintChars, &count);
	printf("\n");
	
	iter = DlistBegin(list);
	
	for (i = 0; i < 26; ++i)
	{
		iter = DlistFind(DlistBegin(list), DlistEnd(list), &IsCharEqual, &tester[i]);
		status += ((tester[26 - i - 1]) == *((char *)DlistGetVal(iter)));
	}
	
	splice_test = DlistCreate();
	
	for (i = 0; i < 10; ++i)
	{
		DlistPushBack(splice_test, &splice_tester[i]);
	}
	
	multi_find_test = DlistCreate();
	DlistMultiFind(multi_find_test ,DlistBegin(splice_test),
 		   DlistEnd(splice_test), &IsIntEqual, &splice_tester[9]);
 		   
 	if (3 == DlistCount(multi_find_test))
	{
		printf("MultiFind \033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("MultiFind \033[0;31mFail\033[0m\n");
	}
	
	where = DlistBegin(splice_test);
	where = DlistNext(where);
	where = DlistNext(where);
	
	from = DlistFind(DlistBegin(list), DlistEnd(list), &IsCharEqual, &tester[21]);
	to = DlistFind(DlistBegin(list), DlistEnd(list), &IsCharEqual, &tester[16]);
	
	DlistSplice(from, to, where);
	
	if (15 == DlistCount(splice_test))
	{
		printf("Splice \033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("Splice \033[0;31mFail\033[0m\n");
	}	
	
	if (0 != status)
	{
		printf("\033[0;31mFail in %d tests\033[0m\n", status);
	}
	else
	{
		printf("\033[0;32mPassed all tests!\033[0m\n");
	}
	
	DlistDestroy(multi_find_test);
	DlistDestroy(splice_test);
	DlistDestroy(list);
}

