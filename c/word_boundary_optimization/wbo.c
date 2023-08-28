/*------------------------------------------------------------------*/
/* DEVELOPER: Gali Aviyam                                           */
/* DATE MODIFIED: 25.11.2022                                        */
/* WORKSHEET NAME: word boundary optimization                       */
/* GDB + Valgrind tested                                            */
/* Reviewer: Karin                                                  */
/*------------------------------------------------------------------*/
#include <assert.h> /*assert*/

#include "wbo.h"

#define WORD_SIZE sizeof(size_t)
#define IS_ALIGNED(ptr) !((size_t)ptr & (size_t)(WORD_SIZE - 1))
#define IS_OVERLAPPING(a, b, size) (((char *)a) > ((char *)b)) && \
								(((char *)a) < (((char *)b) + size))
								
void SetWord(size_t *word, int c)
{
	size_t i = 0;
	
	assert(NULL != word);
	
	for (i = 0; i < WORD_SIZE; ++i)
	{
		*(char *)word = c;
	}
}

void *Memset(void *str, int c, size_t n)
{	
	size_t *runner = NULL;	
	size_t word_chunk = 0;
	
	assert(NULL != str);
	
	runner = str;
	
	while (!IS_ALIGNED(runner) && 0 < n)
	{
		*(char *)runner = (char)c;
		
		runner = (size_t *)((char *)runner + 1);
		
		--n;
	}
	
	if (WORD_SIZE <= n)
	{
		SetWord(&word_chunk, c);
	
		while (WORD_SIZE <= n)
		{
			*runner = word_chunk;
			
			++runner;
			
			n -= WORD_SIZE;
		}
	}
	
	while (0 < n)
	{
		*(char *)runner = (char)c;
		
		runner = (size_t *)((char *)runner + 1);
		
		--n;
	}
	
	return str;

}


void *Memcpy(void *dest, const void *src, size_t n)
{
	size_t *dest_word = NULL;
	size_t *src_word = NULL;
	char *dest_byte = NULL;
	char *src_byte = NULL;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	dest_word = (size_t *)dest;
	src_word = (size_t *)src;
	
	while (WORD_SIZE <= n)
	{
		*dest_word = *src_word;
		++dest_word;
		++src_word;
		n -= WORD_SIZE;
	}
	
	src_byte = (char *)src_word;
	dest_byte = (char *)dest_word;
	
	while (0 < n)   
	{
		*dest_byte = *src_byte;
		++dest_byte;
		++src_byte;
		--n;
	}
	
	return dest;
}

void MemRevcpy(char *dest, char *src, size_t *n)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	*dest = *src;
	--dest;
	--src;
	--(*n);
}

void *Memmove(void *dest, const void *src, size_t n)
{
	char *dest_runner = NULL;
	char *src_runner = NULL;
	
	assert(NULL != dest);
	assert(NULL != src);
		/*(char *)dest < (char *)src || (char *)dest > ((char *)src + n)*/
	if (!IS_OVERLAPPING(dest, src, n))
	{
		Memcpy(dest, src, n);
	}
	else
	{
		dest_runner = (char *)dest + n;
		src_runner = (char *)src + n;
		
		while (0 < n)
		{
			MemRevcpy(dest_runner, src_runner, &n);
		}
	}
	return dest;
}
