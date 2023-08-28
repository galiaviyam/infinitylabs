/****************************************/
/*										*/
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Fixed Size Allocator	*/
/*   Date:		04/01/2023				*/
/*	 Reviewer:	Noy Cohen				*/
/*										*/
/****************************************/

#include <assert.h>	/* assert */

#include "fsa.h"	/* fsa header file */

#define	WORD_SIZE sizeof(size_t)
#define	OFFSET(a) ((a) & (WORD_SIZE - 1))
#define WORST_CASE_STRUCT_PADDING ((WORD_SIZE) - (1))
#define FIRST_FREE(fsa) (fsa->first_free)

struct fsa
{
	size_t first_free;
};

static size_t RoundUpBlock(size_t block_size);
static fsa_t *AlignedAddress(void *memory_pool);
static void InitBlocks(fsa_t *fsa, size_t num_of_blocks, size_t block_size);
static void *GetBlockByOffset(fsa_t *fsa);
static void UpdateNextFreeBlock(fsa_t *fsa, size_t block);

/*---------------------------FSARequiredPoolSize-----------------------------*/
size_t FSARequiredPoolSize(size_t num_of_blocks, size_t block_size)
{
	assert(0 < num_of_blocks);
	assert(0 < block_size);
	
	block_size = RoundUpBlock(block_size);

	return ((block_size * num_of_blocks) + sizeof(fsa_t) + 
			WORST_CASE_STRUCT_PADDING);
}

/*----------------------------------FSAInit----------------------------------*/
fsa_t *FSAInit(void *memory_pool, size_t num_of_blocks, size_t block_size)
{
	fsa_t *fsa = NULL;
	
	assert(NULL != memory_pool);
	assert(0 < num_of_blocks);
	assert(0 < block_size);
	
	block_size = RoundUpBlock(block_size);
	fsa = AlignedAddress(memory_pool);
	
	InitBlocks(fsa, num_of_blocks, block_size);
	
	return fsa;
}

/*--------------------------------FSAAllocate--------------------------------*/
void *FSAAllocate(fsa_t *fsa)
{
	void *block = NULL;
	
	assert(NULL != fsa);
	
	if (0 != FIRST_FREE(fsa))
	{
		block = GetBlockByOffset(fsa);
		UpdateNextFreeBlock(fsa, *(size_t *)block);
	}
	
	return block;
}

/*----------------------------------FSAFree----------------------------------*/
void FSAFree(fsa_t *fsa, void *block)
{
	assert(NULL != fsa);
	assert(NULL != block);
	
	*(size_t *)block = fsa->first_free;
	fsa->first_free = (char *)block - (char *)fsa;
}

/*--------------------------------FSACountFree-------------------------------*/
size_t FSACountFree(const fsa_t *fsa)
{
	size_t count = 0;
	size_t offset_runner = 0;
	
	assert(NULL != fsa);
	
	offset_runner = fsa->first_free;
	
	while (0 != offset_runner)
	{
		offset_runner = *(size_t *)((const char *)fsa + offset_runner);
		++count;
	}
	
	return count;
}

/*****************************Service Functions*******************************/
static size_t RoundUpBlock(size_t block_size)
{	
	block_size = block_size + (WORD_SIZE - OFFSET(block_size)) * 
								(OFFSET(block_size) != 0);
	return (block_size);
}

static fsa_t *AlignedAddress(void *memory_pool)
{
	fsa_t *fsa = NULL;
	
	assert(NULL != memory_pool);
	
	fsa = (fsa_t *)((char *)memory_pool + ((WORD_SIZE - ((size_t)memory_pool & 
					(WORD_SIZE - 1))) & (WORD_SIZE - 1)));
	
	return fsa;
}

static void InitBlocks(fsa_t *fsa, size_t num_of_blocks, size_t block_size)
{
	size_t offset = 0;
	char *runner = NULL;
	size_t i = 0;
	
	assert(NULL != fsa);
	
	offset = sizeof(fsa_t);
	fsa->first_free = offset;
	
	for (i = 0; i < num_of_blocks; ++i)
	{
		runner = (char *)fsa + offset;
		offset += block_size;
		*(size_t *)runner = offset;
	}
	*(size_t *)runner = 0;
}

static void UpdateNextFreeBlock(fsa_t *fsa, size_t block)
{
	fsa->first_free = block;
}

static void *GetBlockByOffset(fsa_t *fsa)
{
	return ((char *)fsa + fsa->first_free);
}
