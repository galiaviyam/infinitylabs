/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Binary Search tree		*/
/*   Date:		18/01/23				*/
/*	 Reviewer:	Gal						*/
/*										*/
/****************************************/

#include <stdio.h>		/* printf */

#include "ilrd_bst.h"

static void TestNumResultEqual(size_t result, size_t expected_result);
static void TestResultNotNull(void *result);
static void TestBoolResult(int result);
static void TestStatusResult(int result);
static int CmpFunc(const void *a, const void *b);
static int MultipleValByNum(void *val, void *num);
static void TestBSTCreate(void);
static void IntegrationTest(void);
static void CountTest(bst_t *bst, size_t num_of_nodes);
static void BSTPrevTest(void);
static void BSTNextTest(void);
static void BSTRemoveTest(void);
static void TestBSTForEach(void);

enum status
{
	SUCCESS = 0,
	FAIL = 1
};


int main(void)
{
	TestBSTCreate();
	IntegrationTest();
	BSTPrevTest();
	BSTNextTest();
	BSTRemoveTest();
	TestBSTForEach();
	
	return 0 ;
}

static void TestBSTCreate(void)
{
	bst_t *tree = BSTCreate(CmpFunc);
	
	printf("create: ");
	TestResultNotNull(tree);
	
	printf("is empty: ");
	TestBoolResult(BSTIsEmpty(tree));
	printf("\n");
	
	BSTDestroy(tree);	
}

static void IntegrationTest(void)
{
	bst_t *tree = BSTCreate(CmpFunc);
	bst_iter_t iter = {0};
	
	size_t i = 0;
	
	size_t arr[9] = {5, 9, 4, 2, 6, 8, 7, 3, 1};
	size_t expected[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	
	printf("********** Integration Test **********\n");

	for (i = 0; i < 9; ++i)
	{
		iter = BSTInsert(tree, (arr + i));
	}
	
	printf("---------begin---------\n");
	/*the last one inserted is the smallest*/
	TestBoolResult(BSTIsEqual(iter, BSTBegin(tree)));

	printf("-----insert + find-----\n");
	for (i = 0; i < 8; ++i)
	{
		printf("test %lu:	", i+1);
		iter = BSTFind(tree, (expected + i));
		TestNumResultEqual(*(size_t *)BSTGetVal(iter), *(expected + i));
	}
	

	CountTest(tree, 9);

	BSTDestroy(tree);
}

static void CountTest(bst_t *bst, size_t num_of_nodes)
{
	printf("\ncount: ");
	TestNumResultEqual(BSTCount(bst), num_of_nodes);
}

static void BSTNextTest(void)
{
	bst_t *tree = BSTCreate(CmpFunc);
	bst_iter_t iter = {0};
	
	size_t i = 0;
	size_t size = 9;
	size_t arr[9] = {5, 9, 4, 2, 6, 8, 7, 3, 1};
	size_t expected[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	for (i = 0; i < 9; ++i)
	{
		iter = BSTInsert(tree, (arr + i));
	}
	

	printf("---------Next---------\n");
	iter = BSTBegin(tree);

	for (i = 0; i < size - 1; ++i)
	{
		printf("test %lu:	", i + 1);
		iter = BSTNext(iter);
		TestNumResultEqual(*(size_t *)BSTGetVal(iter), *(expected + 1 + i));
	}
	
	BSTDestroy(tree);
}

static void BSTPrevTest(void)
{
	bst_t *tree = BSTCreate(CmpFunc);
	bst_iter_t iter = {0};
	
	size_t i = 0;
	size_t size = 9;
	size_t arr[9] = {5, 9, 4, 2, 6, 8, 7, 3, 1};
	size_t expected[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	for (i = 0; i < 9; ++i)
	{
		iter = BSTInsert(tree, (arr + i));
	}

	printf("---------Prev---------\n");
	iter = BSTEnd(tree);

	for (i = 0; i < size; ++i)
	{
		printf("test %lu:	", i + 1);
		iter = BSTPrev(iter);
		TestNumResultEqual(*(size_t *)BSTGetVal(iter), *(expected + size - 1 - i));
	}
	
	BSTDestroy(tree);
}

static void BSTRemoveTest(void)
{
	bst_t *tree = BSTCreate(CmpFunc);
	bst_iter_t iter = {0};
	
	size_t i = 0;
	
	size_t arr[9] = {5, 9, 4, 2, 6, 8, 7, 3, 1};
	size_t expected[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	for (i = 0; i < 9; ++i)
	{
		iter = BSTInsert(tree, (arr + i));
	}
	
	printf("---------Remove (no children)---------\n");
	iter = BSTFind(tree, (expected + 6));
	BSTRemove(iter);
	TestBoolResult(BSTIsEqual(BSTFind(tree, (expected + 6)), BSTEnd(tree)));
	TestNumResultEqual(*(size_t *)BSTGetVal(BSTFind(tree, (expected + 7))), *(expected + 7));
	
	printf("---------Remove (one child)---------\n");
	iter = BSTFind(tree, (expected + 8));
	BSTRemove(iter);
	TestBoolResult(BSTIsEqual(BSTFind(tree, (expected + 8)), BSTEnd(tree)));
	TestNumResultEqual(*(size_t *)BSTGetVal(BSTFind(tree, (expected + 5))), *(expected + 5));
	
	printf("---------Remove (two children)---------\n");
	iter = BSTFind(tree, (expected + 1));
	BSTRemove(iter);
	TestBoolResult(BSTIsEqual(BSTFind(tree, (expected + 1)), BSTEnd(tree)));
	TestNumResultEqual(*(size_t *)BSTGetVal(BSTFind(tree, (expected + 2))), *(expected + 2));
	TestNumResultEqual(*(size_t *)BSTGetVal(BSTFind(tree, (expected))), *(expected));

	BSTDestroy(tree);
}

static void TestBSTForEach(void)
{
	bst_t *tree = BSTCreate(CmpFunc);
	bst_iter_t iter_from = {0};
	bst_iter_t iter_to = {0};
	size_t i = 0;
	int num = 3;
	
	size_t arr[9] = {5, 9, 4, 2, 6, 8, 7, 3, 1};

	for (i = 0; i < 9; ++i)
	{
		iter_from = BSTInsert(tree, (arr + i));
	}
	
	iter_from = BSTBegin(tree);
	iter_to = BSTEnd(tree);
	
	printf("\n---------ForEach---------\n");
	printf("test ForEach worked: ");
	TestStatusResult(BSTForEach(iter_from, iter_to, &MultipleValByNum, &num));
	
	for (i = 1; i <= 9; ++i)
	{
		printf("test %lu: ", i);
		TestNumResultEqual(*(size_t *)BSTGetVal(iter_from), i*num);
		iter_from = BSTNext(iter_from);
	}
	
	BSTDestroy(tree);	
}
/**************************test service functions*************************/
static int CmpFunc(const void *a, const void *b)
{
	
	return (*(int *)a - *(int *)b);
}

static int MultipleValByNum(void *val, void *num)
{
	(*(int *)val) *= (*(int *)num);
	
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
