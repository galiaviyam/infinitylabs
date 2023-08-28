/********************************************/
/*                                          */   
/*   Developer: Gali Aviyam                 */
/*   Project:   Shuffle and sort dictionary */
/*   Date:      12/03/23                    */
/*   Reviewer:  Ariel Biton                 */
/*                                          */
/********************************************/
#include <pthread.h>				/* pthread_create */
#include <string.h>					/* strcmp */
#include <stdlib.h>					/* malloc */
#include <assert.h>					/* assert */

#include "shuffle_n_sort_dict.h"	/* header file */

typedef enum
{
	ERROR = -1,
	SUCCESS,
	FAIL
} status_t;

typedef struct block
{
	unsigned char **block;
	size_t block_size;
} block_t;

static void *ThreadSort(void *arg);
static int MergeSort(unsigned char **arr_to_sort, size_t num_elements);
static void CopyArrays(unsigned char **arr, unsigned char **left, unsigned char 
			**right, size_t num_elements, int mid);
static void Merge(unsigned char **arr ,unsigned char **left, int left_size, 
			unsigned char **right, int right_size) ;
static int CmpFunc(const void *a, const void *b);

int MTMergeSortDictionary(unsigned char **arr, size_t size, size_t threads_num)
{
	size_t i = 0;
	pthread_t *threads = NULL;
	block_t *block = NULL;
	size_t thread_block_size = 0;
	
	assert(NULL != arr);
	
	block = (block_t *)malloc(sizeof(block_t) * threads_num);
	if (NULL == block)
	{
		return ERROR;
	}	
	thread_block_size = size / threads_num;
	
	threads = (pthread_t *)malloc(sizeof(pthread_t) * threads_num);
	if (NULL == threads)
	{
		return ERROR;
	}
	
	for (i = 0; i < threads_num; ++i)
	{
		block[i].block_size = thread_block_size;
		block[i].block = arr + (i * thread_block_size);
		
		while (SUCCESS != pthread_create(&threads[i], NULL, 
					&ThreadSort, &block[i]));
	}
	
	block[i].block_size = thread_block_size + (size % threads_num);
	
	for (i = 0; i < threads_num; ++i)
	{
		pthread_join(threads[i], NULL);
	}
	MergeSort(arr, size);
/*	qsort(arr, size, sizeof(unsigned char *), &CmpFunc);*/
	
  	free(block);
  	block = NULL;
  	
  	free(threads);
  	threads = NULL;
  	
  	return SUCCESS;

}

static void *ThreadSort(void *arg)
{
	block_t *block = NULL;
	
	assert(NULL != arg);
	
	block = (block_t *)arg;
	
	qsort(block->block, block->block_size, sizeof(unsigned char *), &CmpFunc);

	pthread_exit(NULL);
}

static int MergeSort(unsigned char **arr_to_sort, size_t num_elements)
{
	int mid = 0;
	unsigned char **left = NULL;
	unsigned char **right = NULL;
	
	assert(NULL != arr_to_sort);
	
	if (2 > num_elements) 
	{
		return SUCCESS;
	}
	
	mid = num_elements / 2;  
	
	left = (unsigned char **)malloc(mid * sizeof(unsigned char *));
	if (NULL == left)
	{
		return FAIL;
	}
	
	right = (unsigned char **)malloc((num_elements - mid) * 
			sizeof(unsigned char *));
	if (NULL == right)
	{
		return FAIL;
	} 
	
	CopyArrays(arr_to_sort, left, right, num_elements, mid);

	MergeSort(left , mid); 
	MergeSort(right ,num_elements - mid);  
	
	Merge(arr_to_sort, left, mid, right, num_elements - mid);
	
	free(left);
	left = NULL;
	
	free(right);
	right = NULL;
	
	return SUCCESS;
}

static void CopyArrays(unsigned char **arr, unsigned char **left, unsigned char 
			**right, size_t num_elements, int mid)
{
	size_t i = 0;
	
	assert(NULL != arr);
	
	for (i = 0; i < (size_t)mid; ++i) 
	{
		left[i] = arr[i];
	}
	
	for (i = mid; i < num_elements; ++i) 
	{
		right[i - mid] = arr[i];
	}
}

static void Merge(unsigned char **arr ,unsigned char **left, int left_size, 
			unsigned char **right, int right_size) 
{
	int left_idx = 0;
	int right_idx = 0;
	int merged_idx = 0;
	
	assert(NULL != arr);
	assert(NULL != left);
	assert(NULL != right);
	
	while (left_idx < left_size && right_idx < right_size) 
	{
		if (left[left_idx] < right[right_idx]) 
		{
			arr[merged_idx] = left[left_idx];
			++left_idx;
		}
		else 
		{
			arr[merged_idx] = right[right_idx];
			++right_idx;
		}
		++merged_idx;
	}
	
	while (left_idx < left_size)
	{
		arr[merged_idx] = left[left_idx];
		++left_idx;
		++merged_idx;
	} 
	
	while (right_idx < right_size)
	{
		arr[merged_idx] = right[right_idx];
		++right_idx;
		++merged_idx;	
	}
}

static int CmpFunc(const void *a, const void *b)
{
    return (strcmp(*(const char **)a,  *(const char **)b));
}
