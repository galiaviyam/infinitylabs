/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Linear Sorts			*/
/*   Date:		16/01/23				*/
/*	 Reviewer:	Aviv					*/
/*										*/
/****************************************/

#include <stdio.h>			/* printf */
#include <stdlib.h>			/* rand qsort*/
#include <time.h>			/* clock */

#include "linear_sort.h"	/* header file */

#define SIZE (5000)

typedef enum
{
	SUCCESS = 0,
	FAIL
}status_t;

static void CountingSortTest(void);
static void RadixSortTest(void);
static void TestStatusResult(int result);

int main(void)
{
	CountingSortTest();
	RadixSortTest();
	
	return 0;
}

static void CountingSortTest(void)
{
	int arr[SIZE] = {0};
	size_t i = 0;
	int status = 0;
	clock_t start = 0;
	clock_t end = 0;
	
	for (i = 0; i < SIZE; ++i)
	{
		arr[i] = rand() % 101;
	} 
	
	start = clock();
	CountingSort(arr, SIZE);
	end = clock();
	
	for (i = 0; i < (SIZE - 1); ++i)
	{
		status += !(*(arr + i) <= *(arr + i + 1));
	} 
	
	printf("CountingSort: ");
	TestStatusResult(status);
	printf("time: %f\n\n", (double)(end - start) / CLOCKS_PER_SEC);
}

static void RadixSortTest(void)
{
	int arr[SIZE] = {0};
	size_t i = 0;
	int status = 0;
	clock_t start = 0;
	clock_t end = 0;
	
	for (i = 0; i < SIZE; ++i)
	{
		arr[i] = rand() % (10000000 - 1000000) + 1000000;
	} 
	
	start = clock();
	RadixSort(arr, SIZE, 2);
	end = clock();
	
	for (i = 0; i < (SIZE - 1); ++i)
	{
		status += !(*(arr + i) <= *(arr + i + 1));
	} 
	
	printf("RadixSort: ");
	TestStatusResult(status);
	printf("time: %f\n\n", (double)(end - start) / CLOCKS_PER_SEC);
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
