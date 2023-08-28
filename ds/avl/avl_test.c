/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	AVL             		*/
/*   Date:		31/01/23				*/
/*	 Reviewer:	Eliran					*/
/*										*/
/****************************************/

#include <stdio.h>	/* printf */

#include "avl.h"	/* avl header file */

enum status
{
	SUCCESS = 0,
	FAIL = 1
};

static void TestNumResultEqual(size_t result, size_t expected_result);
static void TestResultNotNull(void *result);
static void TestBoolResult(int result);
static void TestStatusResult(int result);

static int CmpFunc(const void *a, const void *b);
static int MultipleValByNum(void *val, void *num);
static void TestAVLCreateDestroy(void);
static void TestInsert(void);
static void TestFind(void);
static void CountTest(avl_t *avl, size_t num_of_nodes);
static void RemoveTest(void);
static void TestForEach(void);
static void TestForEachPRE(void);
static void TestForEachIN(void);
static void TestForEachPOST(void);
static void TestBalance(void);

int main(void)
{
	TestAVLCreateDestroy();
	TestInsert();
	TestFind();
	RemoveTest();
	TestForEach();
	TestBalance();
	
	return 0 ;
}

static void TestAVLCreateDestroy(void)
{
	avl_t *avl = AVLCreate(&CmpFunc);
	
	printf("create: ");
	TestResultNotNull(avl);
	
	printf("is empty: ");
	TestBoolResult(AVLIsEmpty(avl));
	
	printf("height: ");
	
	TestNumResultEqual(AVLGetHeight(avl), -1);
	printf("\n");

	AVLDestroy(avl);	
}

static void TestInsert(void)
{
	avl_t *avl = AVLCreate(CmpFunc);
	size_t i = 0;
	
	size_t arr[9] = {5, 9, 4, 2, 6, 8, 7, 3, 1};
	
	printf("----------insert----------\n");

	for (i = 0; i < 9; ++i)
	{
		printf("Insert test %lu:	", i+1);
		TestStatusResult(AVLInsert(avl, (arr + i)));
	}	

	CountTest(avl, 9);
	
	AVLDestroy(avl);
}

static void TestFind(void)
{
	avl_t *avl = AVLCreate(CmpFunc);
	void *found_data = NULL;
	size_t i = 0;
	
	size_t arr[9] = {5, 9, 4, 2, 6, 8, 7, 3, 1};
	size_t expected[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	for (i = 0; i < 9; ++i)
	{
		AVLInsert(avl, (arr + i));
	}

	printf("----------find----------\n");
	for (i = 0; i < 8; ++i)
	{
		printf("Find test %lu:	", i+1);
		TestBoolResult(AVLFind(avl, (expected + i), &found_data));
	}

	AVLDestroy(avl);
}

static void CountTest(avl_t *avl, size_t num_of_nodes)
{
	printf("\ncount: ");
	TestNumResultEqual(AVLCount(avl), num_of_nodes);
}

static void RemoveTest(void)
{
	avl_t *avl = AVLCreate(CmpFunc);
	void *found_data = NULL;
	size_t i = 0;
	
	size_t arr[9] = {5, 9, 4, 2, 6, 8, 7, 3, 1};
	size_t expected[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	size_t after_remove[6] = {1, 3, 4, 5, 6, 8};
	
	for (i = 0; i < 9; ++i)
	{
		AVLInsert(avl, (arr + i));
	}
	
	printf("---------Remove (no children)---------\n");
	AVLRemove(avl, (expected + 6));
	TestBoolResult(!AVLFind(avl, (expected + 6), &found_data));
	
	printf("---------Remove (one child)---------\n");
	AVLRemove(avl, (expected + 8));
	TestBoolResult(!AVLFind(avl, (expected + 8), &found_data));
	
	printf("---------Remove (two children)---------\n");
	AVLRemove(avl, (expected + 1));
	TestBoolResult(!AVLFind(avl, (expected + 1), &found_data));
	
	for (i = 0; i < 6; ++i)
	{
		TestBoolResult(AVLFind(avl, (after_remove + i), &found_data));
	}
	
	AVLDestroy(avl);
}

static void TestForEach(void)
{
	printf("\n---------ForEach---------\n");
	
	TestForEachPRE();
	TestForEachIN();
	TestForEachPOST();
}

static void TestForEachPRE(void)
{
	avl_t *avl = AVLCreate(CmpFunc);
	size_t i = 0;
	int num = 3;
	size_t arr[9] = {5, 9, 4, 2, 6, 8, 7, 3, 1};
	
	for (i = 0; i < 9; ++i)
	{
		AVLInsert(avl, (arr + i));
	}
	
	printf("test ForEach PRE: ");
	TestStatusResult(AVLForEach(avl, &MultipleValByNum, &num, PRE));
	
	AVLDestroy(avl);
}

static void TestForEachIN(void)
{
	avl_t *avl = AVLCreate(CmpFunc);
	size_t i = 0;
	int num = 3;
	size_t arr[9] = {5, 9, 4, 2, 6, 8, 7, 3, 1};
	
	for (i = 0; i < 9; ++i)
	{
		AVLInsert(avl, (arr + i));
	}
	
	printf("test ForEach IN: ");
	TestStatusResult(AVLForEach(avl, &MultipleValByNum, &num, IN));
	
	AVLDestroy(avl);
}

static void TestForEachPOST(void)
{
	avl_t *avl = AVLCreate(CmpFunc);
	size_t i = 0;
	int num = 3;
	size_t arr[9] = {5, 9, 4, 2, 6, 8, 7, 3, 1};
	
	for (i = 0; i < 9; ++i)
	{
		AVLInsert(avl, (arr + i));
	}
	
	printf("test ForEach POST: ");
	TestStatusResult(AVLForEach(avl, &MultipleValByNum, &num, POST));
	
	AVLDestroy(avl);
}

static void TestBalance(void)
{
	avl_t *avl = NULL;
	int status = FAIL;
	int unbalanced[] = {10, 7, 13, 3 , 5, 11, 15, 14, 4, 6, 8, 9, 2, 12, 16};
	size_t size = sizeof(unbalanced)/sizeof(int);
	size_t i = 0;
	
	printf("\n---------Balance---------\n");
	
	avl = AVLCreate(&CmpFunc);
	if (NULL == avl)	
	{
		printf("FAIL\n");
	}
	
	if (-1 == AVLGetHeight(avl))
	{
		status = SUCCESS;
	}
	
	for (i = 0; i < size; ++i)
	{
		status += AVLInsert(avl, &unbalanced[i]);
	}
	
	TestBoolResult(!status && 4 == AVLGetHeight(avl));
	
	AVLDestroy(avl);
	avl = NULL;
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
