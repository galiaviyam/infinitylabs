/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Comparison Sorts		*/
/*   Date:		02/02/23				*/
/*	 Reviewer:	Shauli + Itay			*/
/*										*/
/****************************************/

#include <stdio.h>		/* printf */
#include <stdlib.h>		/* rand qsort*/
#include <time.h>		/* clock */

#include "cmp_sorts.h"	/* header file */

#define SIZE (5000)

typedef enum
{
	SUCCESS = 0,
	FAIL
}status_t;

static void BubbleSortTest(void);
static void SelectionSortTest(void);
static void InsertionSortTest(void);
static void IterBinarySearchTest(void);
static void RecBinarySearchTest(void);
static void MergeSortTest(void);
static void QsortTest(void);
static void TestStatusResult(int result);
static void TestIntResultEqual(int result, int expected_result);
static int Cmpfunc(const void *num1, const void *num2);

int main(void)
{
	BubbleSortTest();
	SelectionSortTest();
	InsertionSortTest();
	IterBinarySearchTest();
	RecBinarySearchTest();
	MergeSortTest();
	QsortTest();
	
	return 0;
}

static void BubbleSortTest(void)
{
	int arr[SIZE] = {0};
	size_t i = 0;
	int status = 0;
	clock_t start = 0;
	clock_t end = 0;
	
	for (i = 0; i < SIZE; ++i)
	{
		arr[i] = rand();
	} 
	
	start = clock();
	BubbleSort(arr, SIZE);
	end = clock();
	
	for (i = 0; i < (SIZE - 1); ++i)
	{
		status += !(*(arr + i) <= *(arr + i + 1));
	} 
	
	printf("BubbleSort: ");
	TestStatusResult(status);
	printf("time: %f\n\n", (double)(end - start) / CLOCKS_PER_SEC);
}

static void SelectionSortTest(void)
{
	int arr[SIZE] = {0};
	size_t i = 0;
	int status = 0;
	clock_t start = 0;
	clock_t end = 0;
	
	for (i = 0; i < SIZE; ++i)
	{
		arr[i] = rand();
	} 
	
	start = clock();
	SelectionSort(arr, SIZE);
	end = clock();
	
	for (i = 0; (SIZE - 1) > i; ++i)
	{
		status += !(*(arr + i) <= *(arr + i + 1));
	}
	
	printf("SelectionSort: ");
	TestStatusResult(status);
	printf("time: %f\n\n", (double)(end - start) / CLOCKS_PER_SEC);
}

static void InsertionSortTest(void)
{
	int arr[SIZE] = {0};
	size_t i = 0;
	int status = 0;
	clock_t start = 0;
	clock_t end = 0;
	
	for (i = 0; SIZE > i; ++i)
	{
		arr[i] = rand();
	} 
	
	start = clock();
	InsertionSort(arr, SIZE);
	end = clock();
	
	for (i = 0; (SIZE - 1) > i; ++i)
	{
		status += !(*(arr + i) <= *(arr + i + 1));
	} 

	printf("InsertionSort: ");
	TestStatusResult(status);
	printf("time: %f\n\n", (double)(end - start) / CLOCKS_PER_SEC);
}

static void IterBinarySearchTest(void)
{
	int arr[SIZE] = {0};
	size_t i = 0;
	int *res = NULL;
	int num_to_find = 666;
	
	for (i = 0; SIZE > i; ++i)
	{
		arr[i] = i;
	} 
	
	printf("IterBinarySearch: ");

	res = IterBinarySearch(arr, SIZE, num_to_find);

	if (NULL != res)
	{	
		TestIntResultEqual(*res, num_to_find);
	}
	else
	{
		printf("\033[0;31mNumber Not Found\033[0m\n");
	}
}

static void RecBinarySearchTest(void)
{
	int arr[SIZE] = {0};
	size_t i = 0;
	int *res = NULL;
	int num_to_find = 666;
	
	for (i = 0; SIZE > i; ++i)
	{
		arr[i] = i;
	} 
	
	printf("RecBinarySearch: ");

	res = RecBinarySearch(arr, SIZE, num_to_find);

	if (NULL != res)
	{	
		TestIntResultEqual(*res, num_to_find);
	}
	else
	{
		printf("\033[0;31mNumber Not Found\033[0m\n");
	}
}

static void MergeSortTest(void)
{
	int arr[SIZE] = {0};
	size_t i = 0;
	int status = 0;
	clock_t start = 0;
	clock_t end = 0;
	
	for (i = 0; SIZE > i; ++i)
	{
		arr[i] = rand();
	} 
	
	start = clock();
	MergeSort(arr, SIZE);
	end = clock();
	
	for (i = 0; i < (SIZE - 1); ++i)
	{
		status += !(*(arr + i) <= *(arr + i + 1));
	} 

	printf("MergeSort: ");
	TestStatusResult(status);
	printf("time: %f\n\n", (double)(end - start) / CLOCKS_PER_SEC);
}


static void QsortTest(void)
{
	int arr[SIZE] = {0};
	size_t i = 0;
	int status = 0;
	clock_t start = 0;
	clock_t end = 0;
	
	srand(time(NULL));
	
	for (i = 0; SIZE > i; ++i)
	{
		arr[i] = rand();
	} 
	
	start = clock();
	Qsort(arr, SIZE, sizeof(int), &Cmpfunc);
	end = clock();
	
	for (i = 0; (SIZE - 1) > i; ++i)
	{
		status += !(*(arr + i) <= *(arr + i + 1));
	} 

	printf("Qsort: ");
	TestStatusResult(status);
	printf("time: %f\n\n", (double)(end - start) / CLOCKS_PER_SEC);
	
	for (i = 0; SIZE > i; ++i)
	{
		arr[i] = rand();
	} 
	
	start = clock();
	qsort(arr, SIZE, sizeof(int), &Cmpfunc);
	end = clock();
	
	printf("GNU qsort time: %f\n\n", (double)(end - start) / CLOCKS_PER_SEC);
}

/*---------------------------------------------------------------------------*/
/*-----------------------------service functions-----------------------------*/
/*---------------------------------------------------------------------------*/
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

static void TestIntResultEqual(int result, int expected_result)
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

static int Cmpfunc(const void *num1, const void *num2) 
{
	return (*(int *)num1 - *(int *)num2);
}
