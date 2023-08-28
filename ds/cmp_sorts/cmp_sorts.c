/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Comparison Sorts		*/
/*   Date:		02/02/23				*/
/*	 Reviewer:	Shauli + Itay			*/
/*										*/
/****************************************/

#include <assert.h>		/* assert */
#include <stdlib.h>		/* malloc */
#include <string.h>		/* memcpy */

#include "cmp_sorts.h"	/* header file */

typedef enum
{
	SUCCESS = 0,
	FAIL
}status_t;

static void Swap(int *num1, int *num2);
static int *Merge(int *arr1, size_t size1, int *arr2, size_t size2, 
				int *res_arr, size_t res_size);
static void CopyRemainingElem(int *dest, size_t size_dest, size_t dest_idx, 
								int *src, size_t size_src, size_t src_idx);
static void RecQsort(void *arr, size_t start, size_t end, size_t elem_size, 
					compar_func_t cmp);
static size_t Partition(char *arr, size_t start, size_t end, size_t elem_size, 
						compar_func_t cmp);
static void SwapBytes(char *a, char *b, size_t size);

/*----------------------------------BubbleSort-------------------------------*/
void BubbleSort(int *arr, size_t size)
{
	size_t i = 0;
	size_t j = 0;
	
	assert(NULL != arr);
	
	for (i = 0; i < size - 1; ++i)
	{
		for (j = 0; j < size - i - 1; ++j)
		{
			if (*(arr + j) > *(arr + j + 1))
			{
				Swap((arr + j), (arr + j + 1));
			}
		}
	}
}

/*-------------------------------SelectionSort-------------------------------*/
void SelectionSort(int *arr, size_t size)
{
	size_t i = 0;
	size_t j = 0;
	size_t min_idx = 0;
	
	assert(NULL != arr);
		
	for (i = 0; i < size - 1; ++i)
	{
		min_idx = i;
		for (j = i + 1; j < size; ++j)
		{
			if (*(arr + j) < *(arr + min_idx))
			{
				min_idx = j;
			}
		}
		if (min_idx != i)
		{
			Swap((arr + min_idx), (arr + i));	
		}
	}
}

/*-------------------------------InsertionSort-------------------------------*/
void InsertionSort(int *arr, size_t size)
{
	size_t i = 0;
	int j = 0;
	int first_unsorted = 0;

	assert(NULL != arr);

	for (i = 1; i < size; ++i)
	{
		first_unsorted = arr[i];
			
		for (j = (i - 1); (j >= 0) && (arr[j] > first_unsorted); --j)
		{		
				arr[j + 1] = arr[j]; 			
		}
		arr[j + 1] = first_unsorted;
	}
}

/*-----------------------------IterBinarySearch------------------------------*/
int *IterBinarySearch(int *arr, int arr_size, int element_to_find)
{
	int start = 0;
	int mid = 0;
	int end = 0;
	
	assert(NULL != arr);
	assert(0 <= arr_size);
	
	end = arr_size - 1;
	
	while (start <= end)
	{
		mid = (start + end) / 2;
		
		if (element_to_find == *(arr + mid))
		{
			return (arr + mid);
		}
		else if (element_to_find < *(arr + mid))
		{
			end = mid - 1;
		}
		else
		{
			start = mid + 1;
		}
	}

	return NULL;
}

/*------------------------------RecBinarySearch------------------------------*/
int *RecBinarySearch(int *arr, int arr_size, int element_to_find)
{
	int mid = arr_size / 2;
	
	assert(NULL != arr);
	
	if (element_to_find == *(arr + mid))
	{
		return (arr + mid);
	}
	if (0 == mid)
	{
		return NULL;
	}
	if (element_to_find < *(arr + mid))
	{
		return RecBinarySearch(arr, arr_size - mid, element_to_find);
	}
	else
	{
		return RecBinarySearch((arr + mid), (arr_size - mid), element_to_find);
	}
}

/*---------------------------------MergeSort---------------------------------*/
int MergeSort(int *arr_to_sort, size_t num_elements)
{
	int mid = (num_elements + 1) / 2;
	int *tmp_arr = NULL;
	int status = SUCCESS;
	
	assert(NULL != arr_to_sort);
	
	if (num_elements <= 1)
	{
		return status;
	}
	
	if ((FAIL == MergeSort(arr_to_sort, mid)) 
		|| (FAIL == MergeSort(arr_to_sort + mid, num_elements - mid)))
	{
		return FAIL;
	}
		
	tmp_arr = (int *)malloc(num_elements * sizeof(int));
	if (NULL == tmp_arr)
	{
		return FAIL;
	}
	
	tmp_arr = Merge(arr_to_sort, mid, arr_to_sort + mid, num_elements - mid, 
					tmp_arr, num_elements);
	
	memcpy(arr_to_sort, tmp_arr, num_elements * sizeof(int));
	free(tmp_arr);
	tmp_arr = NULL;
	
	return status;
}

/*-----------------------------------Qsort-----------------------------------*/
void Qsort(void *base, size_t nmemb, size_t size, compar_func_t cmp)
{
	assert(NULL != base);
	assert(NULL != cmp);
	
	RecQsort(base, 0, nmemb * size, size, cmp);
}

/*---------------------------------------------------------------------------*/
/*-----------------------------service functions-----------------------------*/
/*---------------------------------------------------------------------------*/

static void Swap(int *num1, int *num2)
{
	assert(NULL != num1);
	assert(NULL != num2);
	
	*num1 = *num1 ^ *num2;
	*num2 = *num1 ^ *num2;
	*num1 = *num1 ^ *num2;
}

static int *Merge(int *arr1, size_t size1, int *arr2, size_t size2, 
				int *res_arr, size_t res_size)
{
	size_t idx1 = 0;
	size_t idx2 = 0;
	size_t res_idx = 0;
	
	assert(NULL != arr1);
	assert(NULL != arr2);
	assert(NULL != res_arr);
	
	while ((idx1 < size1) && (idx2 < size2) && (res_idx < res_size))
	{
		if (arr1[idx1] <= arr2[idx2])
		{
			res_arr[res_idx] = arr1[idx1];
			++idx1;
		}
		else
		{
			res_arr[res_idx] = arr2[idx2];
			++idx2;
		}
		
		++res_idx;
	}
	
	CopyRemainingElem(res_arr, res_size, res_idx, arr1, size1, idx1);
	CopyRemainingElem(res_arr, res_size, res_idx, arr2, size2, idx2);
	
	return res_arr;
}

static void CopyRemainingElem(int *dest, size_t size_dest, size_t dest_idx, 
								int *src, size_t size_src, size_t src_idx)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	while ((src_idx < size_src) && (dest_idx < size_dest))
	{
		dest[dest_idx] = src[src_idx];
		++src_idx;
		++dest_idx;
	}
}

static void RecQsort(void *arr, size_t start, size_t end, size_t elem_size, 
					compar_func_t cmp)
{
	size_t pivot = 0;
	
	assert(NULL != arr);
	assert(NULL != cmp);
	
	if (start + elem_size >= end)
	{
		return;
	}
	
	pivot = Partition((char *)arr, start, end, elem_size, cmp);
	RecQsort(arr, start, pivot, elem_size, cmp);
	RecQsort(arr, pivot + elem_size, end, elem_size, cmp);
}

static size_t Partition(char *arr, size_t start, size_t end, size_t elem_size, 
						compar_func_t cmp)
{
	char *pivot = NULL;
	size_t i = start - elem_size;
	size_t j = start;
	
	assert(NULL != arr);
	assert(NULL != cmp);
	
	pivot = arr + end - elem_size;
	
	while (j < end - elem_size)
	{
		if (0 < cmp(pivot, arr + j))
		{
			i += elem_size;
			SwapBytes(arr + i, arr + j, elem_size);
		}
		
		j += elem_size;
	}
	
	i += elem_size;
	
	SwapBytes(arr + i, pivot, elem_size);
	
	return i;
}

static void SwapBytes(char *a, char *b, size_t size)
{
	size_t i = 0;
	char tmp = 0;
	
	assert(NULL != a);
	assert(NULL != b);
	
	for (i = 0; i < size; ++i)
	{
		tmp = a[i];
		a[i] = b[i];
		b[i] = tmp;
	}
}
