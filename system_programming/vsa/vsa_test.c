/****************************************/
/*										*/   
/*	Developer:	Gali Aviyam				*/
/*	Project:	Variable Size Allocator	*/
/*	Date:		08/01/2023				*/
/*	Reviewer:	Eliran Tessler			*/
/*										*/
/****************************************/

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc */
#include <limits.h>	/* CHAR_BIT */

#include "vsa.h"	/* vsa header file */

#define IS_ALIGNED(adress) ((0 == (((size_t)adress) & (CHAR_BIT - 1))))

typedef enum
{
	SUCCESS = 0,
	FAIL
}status_t;

static void TestNumResultEqual(size_t result, size_t expected_result);
static void TestResultNotNull(void *result);
static void TestResultIsNull(void *result);
static void TestVSAInit(void);
static void VSAAllocateTest(void);
static void VSAFreeTest(void);
static void VSAGetMaxFreeBlockSizeTest(void);
static void IntegrationTest(void);

int main(void)
{
	TestVSAInit();
	VSAAllocateTest();
	VSAFreeTest();
	VSAGetMaxFreeBlockSizeTest();
	IntegrationTest();
	
	return 0;
}

static void TestVSAInit(void)
{
	vsa_t *vsa = NULL;
	void *pool = NULL;
	size_t pool_size = 64;
	
	pool = malloc(pool_size);
	vsa = VSAInit(pool, pool_size);
	
	printf("\n----------VSAInit----------\n");
	TestResultNotNull(vsa);
	
	free(pool);
	pool = NULL;
}

static void VSAAllocateTest(void)
{
	void *pool = NULL;
	size_t pool_size = 256;
	vsa_t *vsa = NULL;
	void *block = NULL;
	
	pool = malloc(pool_size);
	
	vsa = VSAInit(pool, pool_size);
	
	printf("\n---------VSAAllocate--------\n");
	block = VSAAllocate(vsa, 128);
	*(size_t *)block = 1234;
	
	printf("if vlg passed: \033[0;32mPASS\033[0m\n");
	free(pool);
}

static void VSAFreeTest(void)
{
	void *pool = NULL;
	size_t pool_size = 256;
	vsa_t *vsa = NULL;
	void *block = 0;
	
	pool = malloc(pool_size);
	
	vsa = VSAInit(pool, pool_size);
	
	block = VSAAllocate(vsa, 128);
	*(size_t *)block = 1234;
	printf("\n-----------VSAFree---------\n");
	VSAFree(block);
	
	printf("if vlg passed: \033[0;32mPASS\033[0m\n");
	free(pool);
}

static void VSAGetMaxFreeBlockSizeTest(void)
{
	void *pool = NULL;
	size_t pool_size = 256;
	vsa_t *vsa = NULL;
	
	pool = malloc(pool_size);
	
	vsa = VSAInit(pool, pool_size);
	
	printf("\n---VSAGetMaxFreeBlockSize---\n");	
	TestNumResultEqual(232, VSAGetMaxFreeBlockSize(vsa));
	
	free(pool);
}

static void IntegrationTest(void)
{
	vsa_t *vsa = NULL;
	size_t pool_size = 216;
	void *memory_pool = (void *)malloc(pool_size);
	void *block_to_free = NULL;
	void *block = NULL;
	
	printf("----Integration Test----\n");
	vsa = VSAInit(memory_pool, pool_size);
	printf("init: ");
	TestNumResultEqual(0, (size_t)vsa % 8);
	printf("allocate 1: ");
	TestNumResultEqual(24, ((char *)VSAAllocate(vsa, 8) - (char *)vsa));
	
	printf("allocate 2: ");
	TestNumResultEqual(48, ((char *)VSAAllocate(vsa, 16) - (char *)vsa));
	
	printf("allocate 3: ");
	block_to_free = VSAAllocate(vsa, 16);
	TestNumResultEqual(80, ((char *)block_to_free - (char *)vsa));
	
	printf("allocate 4: ");
	block = VSAAllocate(vsa, 16);
	TestNumResultEqual(112, ((char *)block - (char *)vsa));
	
	printf("allocate 5: ");
	TestNumResultEqual(144, ((char *)VSAAllocate(vsa, 72) - (char *)vsa));
	
	VSAFree(block_to_free);
	
	printf("max: ");
	TestNumResultEqual(16, VSAGetMaxFreeBlockSize(vsa));
	
	printf("allocate 6: ");
	TestNumResultEqual(80, ((char *)VSAAllocate(vsa, 16) - (char *)vsa));

	printf("allocate 7: ");
	TestResultIsNull(VSAAllocate(vsa, 200));
	
	free(memory_pool);
}

/**************************test utility functions************************/
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

static void TestResultIsNull(void *result)
{
	if (NULL == result)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}
