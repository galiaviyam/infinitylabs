/****************************************/
/*										*/
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Fixed Size Allocator	*/
/*   Date:	04/01/2023					*/
/*	 Reviewer:	Noy Cohen				*/
/*										*/
/****************************************/

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc */

#include "fsa.h"	/* fsa header file */

typedef enum
{
	SUCCESS = 0,
	FAIL
}status_t;

static void TestNumResultEqual(size_t result, size_t expected_result);
static void TestResultNotNull(void *result);
static void TestStatusResult(int result);
static void TestFSARequiredPoolSize(void);
static void TestFSAInit(void);
static void IntegrationTest(void);

int main(void)
{
	TestFSARequiredPoolSize();
	TestFSAInit();
	IntegrationTest();
	return 0;
}

static void TestFSARequiredPoolSize(void)
{
	printf("-----FSARequiredPoolSize-----\n");
	
	printf("Block Alignment Not-Required: ");
	TestNumResultEqual(FSARequiredPoolSize(2, 8), 31);
	printf("Block Alignment Required: ");
	TestNumResultEqual(FSARequiredPoolSize(10, 20), 255);
}

static void TestFSAInit(void)
{
	fsa_t *fsa = NULL;
	void *pool = NULL;

	pool = malloc(FSARequiredPoolSize(10, 20));
	fsa = FSAInit(pool, 10, 20);
	
	printf("----------FSAInit----------\n");
	TestResultNotNull(fsa);
	printf("FSACountFree:");
	TestNumResultEqual(FSACountFree(fsa), 10);
	
	free(pool);
	pool = NULL;
}

static void IntegrationTest(void)
{
	fsa_t *fsa = NULL;
	void *pool = NULL;
	void **address_arr[11] = {NULL};
	size_t i = 0;
	int status = SUCCESS;
	
	pool = malloc(FSARequiredPoolSize(10, 20));
	fsa = FSAInit(pool, 10, 20);
	
	printf("-------FSAAllocate-------\n");
	for (i = 0; i < 10; ++i)
	{
		*(address_arr + i) = FSAAllocate(fsa);
		if (NULL == *(address_arr + i))
		{
			status = FAIL;
		}
	}
	
	TestStatusResult(status);
	printf("FSACountFree:");
	TestNumResultEqual(FSACountFree(fsa), 0);
	printf("Trying to allocate when FSA is full:");
	*(address_arr + 10) = FSAAllocate(fsa);
	if (NULL != *(address_arr + i))
	{
		status = FAIL;
	}
	TestStatusResult(status);
	
	printf("----------FSAFree----------\n");
	for (i = 0; i < 5; ++i)
	{
		FSAFree(fsa, *(address_arr + i*2));
	}

	TestNumResultEqual(FSACountFree(fsa), 5);

	free(pool);
	pool = NULL;
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




