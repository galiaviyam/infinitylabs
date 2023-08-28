/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Linear Sorts			*/
/*   Date:		16/01/23				*/
/*	 Reviewer:	Aviv					*/
/*										*/
/****************************************/

#include <assert.h>			/* assert */
#include <stdlib.h>			/* calloc */
#include <string.h>			/* memcpy */

#include "linear_sort.h"	/* header file */

typedef enum
{
	SUCCESS = 0,
	FAIL
}status_t;

static int GetMaxValue(int *arr, size_t size);
static int PowerOfTen(size_t exp_of_ten);
static void MakeHistogram(int *arr, size_t size, size_t *hist, size_t hist_size,
			size_t digs_to_sort);
static void CountingSortForRadix(int *arr, size_t size, size_t *hist, size_t hist_size,
							size_t digs_to_sort);
static void InitHistogram(size_t *hist, size_t hist_size);
							
int CountingSort(int *arr, size_t size)
{
	int *histogram = NULL;
	size_t i = 0;
	size_t j = 0;
	int max_val = 0;

	assert(NULL != arr);
	
	max_val = GetMaxValue(arr, size);
	
	histogram = (int *)calloc(max_val + 1, sizeof(int));
	if (NULL == histogram)
	{
		return FAIL;
	}
	
	for (i = 0; i < size; ++i)
	{
		++(histogram[arr[i]]);
	}

	for (i = 0; i < size; ++i)
	{
		if (histogram[j] > 0)
		{
			arr[i] = j;
			--histogram[j];
		}
		else
		{
			++j;
			--i;
		}
	}
	
	free(histogram);
	histogram = NULL;
	
	return SUCCESS;
}

int RadixSort(int *arr, size_t size, size_t exp_of_ten)
{
	int max_val = 0;
	size_t digs_to_sort = 1;
	size_t hist_size = 0;
	size_t *hist = NULL;
	
	assert(NULL != arr);
	
	max_val = GetMaxValue(arr, size);
	
	hist_size = PowerOfTen(exp_of_ten);
	
	hist = (size_t *)malloc((hist_size * sizeof(size_t) + (size * sizeof(int))));
	if (NULL == hist)
	{
		return FAIL;
	}
	
	for (digs_to_sort = 1; 0 < (max_val / digs_to_sort); digs_to_sort *= hist_size)
	{
		InitHistogram(hist, hist_size);
		CountingSortForRadix(arr, size, hist, hist_size, digs_to_sort);
	}
	
	free(hist);
	hist = NULL;
	
	return SUCCESS;
}


static void CountingSortForRadix(int *arr, size_t size, size_t *hist, size_t hist_size,
							size_t digs_to_sort)
{
	int *tmp_arr = NULL;
	int i = 0;
	
	assert(NULL != arr);
	assert(NULL != hist);
	
	tmp_arr = (int *)(hist + hist_size);
	
	MakeHistogram(arr, size, hist, hist_size, digs_to_sort);
	for (i = size - 1; 0 <= i; --i)
	{
		tmp_arr[hist[(arr[i] / digs_to_sort) % hist_size] - 1] = arr[i];
		--hist[(arr[i] / digs_to_sort) % hist_size];
	}
	
	memcpy(arr, tmp_arr, (sizeof(int) * size));
}


static int GetMaxValue(int *arr, size_t size)
{
	size_t i = 0;
	int max_val = 0;
	
	for (i = 0; i < size; ++i)
	{
		if (arr[i] > max_val)
		{
			max_val = arr[i];
		}
	}
	
	return max_val;
}

static int PowerOfTen(size_t exp_of_ten)
{
	size_t base = 10;
	size_t i = 0;
	int res = 1;
	
	for (i = 0; i < exp_of_ten; ++i)
	{
		res *= base;
	}
	
	return res;
}

static void MakeHistogram(int *arr, size_t size, size_t *hist, size_t hist_size,
			size_t digs_to_sort)
{
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		++hist[(arr[i] / digs_to_sort) % hist_size];
	}
	
	for (i = 1; i <= hist_size; ++i)
	{
		hist[i] += hist[i - 1];
	}
}

static void InitHistogram(size_t *hist, size_t hist_size)
{
	size_t i = 0;
	
	assert(NULL != hist);
	
	for (i = 0; i < hist_size; ++i)
	{
		hist[i] = 0;
	}
}
