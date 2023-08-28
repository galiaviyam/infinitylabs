/********************************************/
/*                                          */   
/*   Developer: Gali Aviyam                 */
/*   Project:   Shuffle and sort dictionary */
/*   Date:      12/03/23                    */
/*   Reviewer:  Ariel Biton                 */
/*                                          */
/********************************************/

#define _GNU_SOURCE					/* clock_gettime */

#include <stdio.h>					/* printf */
#include <time.h>					/* clock_gettime */
#include <string.h>					/* strtok */
#include <stdlib.h>					/* malloc */

#include "shuffle_n_sort_dict.h"	/* header file */

#define MAX_STRLEN (256)
#define BYTES_IN_DICT (985084)
#define WORDS_IN_DICT (104334)
#define TIMES_TO_COPY (7)
#define MAX (16384)
#define MAX_THREADS (1624)
static void DictionaryTest(void);
static void ShuffleBigData(unsigned char **big_data);
static void ThreadSort(unsigned char **big_data);
static int RandCmpfunc(const void *ptr1, const void *ptr2);
static void TestStatusResult(int result);

typedef enum
{
	SUCCESS = 0,
	FAIL
}status_t;

int main(void)
{
	DictionaryTest();
	
	return 0;
}

static void DictionaryTest(void)
{
	size_t i = 0;
	FILE *dict_ptr = NULL;
	unsigned char buffer[BYTES_IN_DICT + 1] = {0};
	unsigned char *ptr_arr[WORDS_IN_DICT + 1] = {0};
	unsigned char *big_data[WORDS_IN_DICT * (TIMES_TO_COPY)] = {0};
	
	dict_ptr = fopen("/usr/share/dict/words", "r");
	if (NULL == dict_ptr)
	{
		perror("Failed to open dictionary");
		return;
	}
	
	fread(buffer, BYTES_IN_DICT, 1, dict_ptr);
	
	ptr_arr[i] = (unsigned char *)strtok((char *)buffer, "\n");
	
	while (NULL != ptr_arr[i])
	{
		++i;
		ptr_arr[i] = (unsigned char *)strtok(NULL, "\n");
	}
	
	for (i = 0; i < TIMES_TO_COPY; ++i)
	{
		memcpy(big_data + (WORDS_IN_DICT * i), ptr_arr, 
				WORDS_IN_DICT * sizeof(unsigned char *));
	}
	
	ShuffleBigData(big_data);
	
	ThreadSort(big_data);
	
	fclose(dict_ptr);
	dict_ptr = NULL; 

}
static void ShuffleBigData(unsigned char **big_data)
{
    qsort(big_data, (WORDS_IN_DICT * TIMES_TO_COPY), 
    		sizeof(unsigned char *), &RandCmpfunc);
}

static void ThreadSort(unsigned char **big_data)
{
	size_t i = 0;
	size_t j = 1;
	int status = 0;
	struct timespec start;
	struct timespec end;
	double duration = 0;
	
	printf("\n\nAfter Thread Sorting:\n\n");
	for (j = 1; j < (MAX_THREADS); j *= 2)
	{	
		printf("\n\nNum Of Threads: %lu\n", j);
		
		clock_gettime(CLOCK_MONOTONIC, &start);
		        
		MTMergeSortDictionary(big_data, (WORDS_IN_DICT * TIMES_TO_COPY), j);
		
		clock_gettime(CLOCK_MONOTONIC, &end);
	
	   for (i = 0; i < ((TIMES_TO_COPY * WORDS_IN_DICT) - 1) && status; ++i)
        {
            status = (0 >= strcmp((char *)big_data[i] ,(char *)big_data[i + 1]));
        }
		
	 	duration = (end.tv_sec - start.tv_sec);
	   	duration += (end.tv_nsec - start.tv_nsec) / 1000000000.0;
	   	printf("time taken: %.4f seconds\n", duration);
	
		TestStatusResult(status);
	}
}

static int RandCmpfunc(const void *ptr1, const void *ptr2) 
{
	(void)ptr1;
	(void)ptr2;
	
	return ((rand()%2)*2 - 1);
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
