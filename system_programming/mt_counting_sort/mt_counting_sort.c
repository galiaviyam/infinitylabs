/********************************************/
/*                                          */   
/*   Developer: Gali Aviyam                 */
/*   Project:   Multithreaded Counting Sort */
/*   Date:      12/03/23                    */
/*   Reviewer:  Shauli                      */
/*                                          */
/********************************************/

#include <stdlib.h>				/* size_t */
#include <assert.h>				/* assert */
#include <pthread.h>			/* pthread_create */
#include <string.h>				/* memcpy */

#include "mt_counting_sort.h"	/* mt_counting_sort header */

#define HIST_SIZE (256)

typedef enum
{
	SUCCESS = 0,
	FAIL
}status_t;

typedef struct chunk
{
	unsigned char *arr;
	size_t *hist;
	size_t chunk_size;
} chunk_t;

static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

static void *CountThread(void *arg);
static void CombineHistograms(size_t *hist);
static void MakeSortedArr(unsigned char *arr ,size_t *hist, 
										unsigned char *sorted_arr, size_t size);

int MTCountingSort(unsigned char *arr, size_t size, size_t threads_num)
{
	size_t *hist = NULL;
	unsigned char *sorted_arr = NULL;
	pthread_t *threads = NULL;
	chunk_t *chunk = NULL; 
	size_t i = 0;
	size_t chunk_size = size / threads_num;
	
	assert(NULL != arr);
	
	if (SUCCESS != pthread_mutex_init(&g_mutex, NULL))
	{
		return FAIL;
	}

	hist = (size_t *)calloc(1, HIST_SIZE * sizeof(size_t) + 
							size * sizeof(unsigned char));
	if (NULL == hist)
	{
		return FAIL;
	}
	
	threads = (pthread_t *)malloc(threads_num * sizeof(pthread_t));
	if (NULL == threads)
	{
		free(hist);
		hist = NULL;
		
		return FAIL;
	}
	
	chunk = (chunk_t *)malloc(threads_num * sizeof(chunk_t));
	if (NULL == chunk)
	{
		free(hist);
		hist = NULL;
		
		free(threads);
		threads = NULL;
		
		return FAIL;
	}

	sorted_arr = (unsigned char *)(hist + HIST_SIZE); 
	
	for (i = 0; i < threads_num - 1; ++i)
	{
		chunk[i].arr = (arr + (i * chunk_size));
		chunk[i].hist = hist;
		chunk[i].chunk_size = chunk_size; 
		if (SUCCESS != pthread_create(&threads[i], NULL, &CountThread, &chunk[i]))
		{
			free(hist);
			hist = NULL;
			
			free(threads);
			threads = NULL;
			
			free(chunk);
			chunk = NULL;
			return FAIL;
		}
	}
	
	chunk[i].arr = (arr + (i * chunk_size));
	chunk[i].hist = hist;
	chunk[i].chunk_size = chunk_size + (size % threads_num);
	
	if (SUCCESS != pthread_create(&threads[i], NULL, &CountThread, &chunk[i]))
	{
		free(hist);
		hist = NULL;
		
		free(threads);
		threads = NULL;
		
		free(chunk);
		chunk = NULL;
		return FAIL;
	}
	
	for (i = 0; i < threads_num; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	CombineHistograms(hist);
	MakeSortedArr(arr ,hist , sorted_arr, size);

	memcpy(arr, sorted_arr, (size * sizeof(unsigned char)));

	free(hist);
	hist = NULL;
	
	free(threads);
	threads = NULL;
	
	free(chunk);
	chunk = NULL;
	
	return SUCCESS;
}

static void *CountThread(void *args)
{
	size_t local_hist[HIST_SIZE] = {0};
	unsigned char *arr = NULL;
	size_t *hist = NULL;	
	size_t chunk_size = 0;
	size_t i = 0;

	assert(NULL != args);
	
	arr = ((chunk_t *)args)->arr;
	hist = ((chunk_t *)args)->hist;
	chunk_size = ((chunk_t *)args)->chunk_size;

	for (i = 0; i < chunk_size; ++i)
	{
		++local_hist[arr[i]];
	}
	
	pthread_mutex_lock(&g_mutex);
	for (i = 0; i < HIST_SIZE; ++i)
	{
		hist[i] += local_hist[i];
	}
	pthread_mutex_unlock(&g_mutex);
	
	pthread_exit(NULL);
}

static void CombineHistograms(size_t *hist)
{
	size_t i = 0;

	assert(NULL != hist);

	for (i = 1; i <= HIST_SIZE; ++i)
	{
		hist[i] += hist[i - 1]; 
	}
}

static void MakeSortedArr(unsigned char *arr ,size_t *hist, 
										unsigned char *sorted_arr, size_t size)
{
	size_t i = 0;

	assert(NULL != arr);
	assert(NULL != hist);
	assert(NULL != sorted_arr);

	for (i = 0; i < size; ++i)
	{
		sorted_arr[hist[arr[i]] - 1] = arr[i];
		--hist[arr[i]];
	}
}
