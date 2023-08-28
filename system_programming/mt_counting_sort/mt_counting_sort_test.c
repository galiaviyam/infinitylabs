/********************************************/
/*                                          */   
/*   Developer: Gali Aviyam                 */
/*   Project:   Multithreaded Counting Sort */
/*   Date:      12/03/23                    */
/*   Reviewer:  Shauli                      */
/*                                          */
/********************************************/
#include <stdio.h>				/* printf */
#include <string.h>				/* memcpy */
#include <time.h>				/* clock */

#include "mt_counting_sort.h"	/* mt_counting_sort header */

#define SIZE (256)
#define MAX_STRLEN (256)
#define BYTES_IN_DICT (985084)
#define TIMES_TO_COPY (1000)
#define MAX (16384)

typedef enum
{
	SUCCESS = 0,
	FAIL
}status_t;

static void CountingSortTest(size_t num_threads);
static void TestStatusResult(int result);
static void LoadDictionaryTest(size_t num_threads);

int main(void)
{
	size_t i = 0;
	
	for (i = 2; i <= MAX; i *= 2)
	{
		CountingSortTest(i);
	} 
	
	for (i = 2; i <= MAX; i *= 2)
	{
		LoadDictionaryTest(i);
	} 
	
	return 0;
}


static void CountingSortTest(size_t num_threads)
{
	unsigned char arr[SIZE] = {0};
	size_t i = 0;
	int status = SUCCESS;
	time_t start = 0;
	time_t end = 0;
	
	for (i = 0; i < SIZE; ++i)
	{
		arr[i] = '\0' + i;
	} 
	
	start = time(NULL);
	MTCountingSort(arr, SIZE, num_threads);
	end = time(NULL);
	
	for (i = 0; i < (SIZE - 1); ++i)
	{
		status += !(*(arr + i) <= *(arr + i + 1));
	} 
	
	printf("CountingSort %lu threads: ", num_threads);
	TestStatusResult(status);
	printf("time: %.6f\n\n", difftime(end, start));
}

static void LoadDictionaryTest(size_t num_threads)
{
	unsigned char *dict_buff = NULL;
	unsigned char *dict_big_data = NULL;
	FILE *dict_ptr = NULL;
	size_t big_data_size = TIMES_TO_COPY * (BYTES_IN_DICT + 1);
	size_t i = 0;
	int status = SUCCESS;
	time_t start = 0;
	time_t end = 0;
	
	dict_ptr = fopen("/usr/share/dict/words", "r");
	if (NULL == dict_ptr)
	{
		printf("\033[0;31mFAIL\033[0m\n");
		return;
	}
	
	dict_buff = (unsigned char *)malloc((BYTES_IN_DICT + 1) * 
				sizeof(unsigned char));
	if (NULL == dict_buff)
	{
		printf("\033[0;31mFAIL\033[0m\n");
		fclose(dict_ptr);
		dict_ptr = NULL;
	
		return;
	}
	
	dict_big_data = (unsigned char *)calloc(big_data_size, 
					sizeof(unsigned char));
	if (NULL == dict_big_data)
	{
		printf("\033[0;31mFAIL\033[0m\n");
		fclose(dict_ptr);
		dict_ptr = NULL;
		free(dict_buff);
		dict_buff = NULL;
	
		return;
	}
	
	fread(dict_buff, BYTES_IN_DICT, 1, dict_ptr);
	
	*(dict_buff + BYTES_IN_DICT) = '\0';
	
	for (i = 0; i < TIMES_TO_COPY; ++i)
	{
		memcpy((dict_big_data + (TIMES_TO_COPY * i)), dict_buff, BYTES_IN_DICT);
	}
	
	start = time(NULL);
	MTCountingSort(dict_big_data, big_data_size, num_threads);
	end = time(NULL);
	
	for (i = 0; i < (big_data_size - 1); ++i)
	{
		status += !(*(dict_big_data + i) <= *(dict_big_data + i + 1));
	} 
	
	printf("big data: %lu threads: ", num_threads);
	TestStatusResult(status);
	printf("time: %f\n\n", difftime(end, start));
	
	fclose(dict_ptr);
	dict_ptr = NULL;   	
	
	free(dict_buff);
	dict_buff = NULL;
	
	free(dict_big_data);
	dict_big_data = NULL;
}

static void TestStatusResult(int result)
{
	if (SUCCESS == result)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}
