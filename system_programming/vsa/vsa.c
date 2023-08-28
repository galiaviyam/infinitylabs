/****************************************/
/*										*/   
/*	Developer:	Gali Aviyam				*/
/*	Project:	Variable Size Allocator	*/
/*	Date:		08/01/2023				*/
/*	Reviewer:	Eliran Tessler			*/
/*										*/
/****************************************/

#include <assert.h>	/* assert */

#include "vsa.h"	/* vsa header file */

#define	WORD_SIZE sizeof(size_t)
#define MIN_POOL_SIZE (64)
#define START_OF_POOL(vsa) (((char *)vsa) + (sizeof(vsa_t)))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define START_OF_BLOCK(block) (((char *)block) + (sizeof(block_t)))
typedef struct block
{
	size_t block_size_and_meta;
	#ifndef NDEBUG
		vsa_t *vsa;
	#endif
} block_t;

struct vsa
{
	size_t pool_size;
};

typedef enum
{
	TRUE = 1,
	FALSE = 0
}bool_t;

static size_t GetPadding(size_t block_size);
static vsa_t *AlignUp(void *memory_pool);
static size_t AlignPoolSize(size_t pool_size, vsa_t *vsa, void *memory_pool);
static char *GetAddrEndOfPool(vsa_t *vsa);
static block_t *GetBlockHeader(char *block);
static block_t *NextFreeBlock(vsa_t *vsa, block_t *block);
static int IsEndOfPool(vsa_t *vsa, block_t *block);

static void Defrag(vsa_t *vsa, block_t *block);
static block_t *InitBlock(block_t *block, size_t block_size);
static int IsFreeBlock(block_t *block);
static block_t *NextBlock(block_t *block);
static void SetBlockFree(block_t *block);
static void SetBlockNotFree(block_t *block);
static int IsBlockInPool(vsa_t *vsa, char *block);
static size_t GetBlockSize(block_t *block);
static void SetBlockSize(block_t *block, size_t new_size);
static void SplitBlock(block_t *block, size_t block_size);



/*----------------------------------VSAInit----------------------------------*/
vsa_t *VSAInit(void *memory_pool, size_t pool_size)
{
	vsa_t *vsa = NULL;
	block_t *first_block = NULL;
	size_t block_size = 0;
	
	assert(NULL != memory_pool);
	assert(MIN_POOL_SIZE <= pool_size);
	
	vsa = AlignUp(memory_pool);
	pool_size = AlignPoolSize(pool_size, vsa, memory_pool);
	vsa->pool_size = pool_size;
	
	first_block = (block_t *)START_OF_POOL(vsa);
	block_size = pool_size - sizeof(vsa_t) - sizeof(block_t);
	InitBlock(first_block, block_size);
	
	#ifndef NDEBUG
		first_block->vsa = vsa;
	#endif
	
	return vsa;
}

/*--------------------------------VSAAllocate--------------------------------*/
void *VSAAllocate(vsa_t *vsa, size_t block_size)
{
	block_t *block_runner = NULL;
	
	assert(NULL != vsa);
	
	block_size += GetPadding(block_size);
	block_runner = (block_t *)START_OF_POOL(vsa);
	block_runner = NextFreeBlock(vsa, block_runner);
	Defrag(vsa, block_runner);
	
	while (IsBlockInPool(vsa, (char *)block_runner) && 
			GetBlockSize(block_runner) < block_size)
	{
		block_runner = NextBlock(block_runner);
		block_runner = NextFreeBlock(vsa, block_runner);
		Defrag(vsa, block_runner);
	}
	if (!IsBlockInPool(vsa, (char *)block_runner))
	{
		return NULL;
	}
	
	if (GetBlockSize(block_runner) >= (block_size + sizeof(block_t)))
	{
		SplitBlock(block_runner, block_size);
		#ifndef NDEBUG
			block_runner->vsa = vsa;
		#endif
	}
	SetBlockNotFree(block_runner);
	
	return (START_OF_BLOCK(block_runner));
}

/*----------------------------------VSAFree----------------------------------*/
void VSAFree(void *block)
{
	block_t *block_to_free = NULL;
	
	assert(NULL != block);
	
	block_to_free = GetBlockHeader((char *)block);
	assert(IsBlockInPool(block_to_free->vsa, (char *)block_to_free));
	
	SetBlockFree(block_to_free);
}

/*---------------------------VSAGetMaxFreeBlockSize--------------------------*/
size_t VSAGetMaxFreeBlockSize(vsa_t *vsa)
{
	block_t *block_runner = NULL;
	size_t max_size = 0;
	
	assert(NULL != vsa);
	block_runner = (block_t *)START_OF_POOL(vsa);

	while (!IsEndOfPool(vsa, block_runner))
	{
		if (IsFreeBlock(block_runner))
		{
			Defrag(vsa, block_runner);
			max_size = MAX(max_size, GetBlockSize(block_runner));
		}
		
		block_runner = NextBlock(block_runner);
	}

	return max_size;
}

/****************************Service Functions*******************************/

static vsa_t *AlignUp(void *memory_pool)
{
	size_t num_of_bytes = 0;

	assert(NULL != memory_pool);
	
	num_of_bytes = GetPadding((size_t)memory_pool);	
	memory_pool = (char *)memory_pool + num_of_bytes;
	
	return ((vsa_t *)memory_pool);
}

static size_t GetPadding(size_t block_size)
{
	return ((WORD_SIZE - (block_size % WORD_SIZE)) % WORD_SIZE);
}

static block_t *InitBlock(block_t *block, size_t block_size)
{
	SetBlockSize(block, block_size);
	SetBlockFree(block);
	
	return block;
}

static int IsFreeBlock(block_t *block)
{
	assert(NULL != block);
	
	return (0 == ((block->block_size_and_meta) & ((size_t)1)));
}

static block_t *NextBlock(block_t *block)
{
	block_t *next_block = NULL;
	
	assert(NULL != block);
	
	next_block = (block_t *)((char *)block + sizeof(block_t) + 
									GetBlockSize(block));
	
	return next_block;

}

static void SetBlockFree(block_t *block)
{
	assert(NULL != block);

	block->block_size_and_meta = ((((block->block_size_and_meta) >> 1) << 1));
}

static void SetBlockNotFree(block_t *block)
{
	assert(NULL != block);
	
	block->block_size_and_meta = ((block->block_size_and_meta) | ((size_t)1));
}

static size_t GetBlockSize(block_t *block)
{
	assert(NULL != block);
	
	return (((block->block_size_and_meta) >> 1) << 1);
}

static void SetBlockSize(block_t *block, size_t new_size)
{
	assert(NULL != block);
	
	block->block_size_and_meta = new_size;
}

static int IsBlockInPool(vsa_t *vsa, char *block)
{
	assert(NULL != vsa);
	assert(NULL != block);
	
	return ((char *)block < GetAddrEndOfPool(vsa) && ((char *)vsa < block));
}

static int IsEndOfPool(vsa_t *vsa, block_t *block)
{
	assert(NULL != vsa);
	assert(NULL != block);
	
	return ((GetAddrEndOfPool(vsa)) == ((char *)block));
}

static size_t AlignPoolSize(size_t pool_size, vsa_t *vsa, void *memory_pool)
{
	pool_size -= ((char *)vsa - (char *)memory_pool);
	pool_size -= (pool_size % WORD_SIZE);
	return (pool_size);
}

static void SplitBlock(block_t *block, size_t block_size)
{
	block_t *new_block = NULL;
	size_t new_block_size = 0;	

	assert(NULL != block);
	
	new_block_size = GetBlockSize(block) - block_size - sizeof(block_t);
	SetBlockSize(block, block_size);
	new_block = NextBlock(block);
	InitBlock(new_block, new_block_size);
}

static block_t *GetBlockHeader(char *block)
{
	assert(NULL != block);
	
	block -= sizeof(block_t);
	return ((block_t *)block);
}

static void Defrag(vsa_t *vsa, block_t *block)
{
	block_t *next_block = NULL;

	assert(NULL != block);	
	assert(NULL != vsa);
	
	if (!IsEndOfPool(vsa, block))
	{
		next_block = NextBlock(block);

		while ((!IsEndOfPool(vsa, next_block)) && (IsFreeBlock(next_block))) 
		{
			block->block_size_and_meta += (sizeof(block_t) + GetBlockSize(next_block));
			next_block = NextBlock(next_block);
		}
	}
}

static block_t *NextFreeBlock(vsa_t *vsa, block_t *block)
{
	assert(NULL != block);
		
	while (IsBlockInPool(vsa, (char *)block) && !IsFreeBlock(block))
	{
		block = NextBlock(block);
	}
	
	return block;
}

static char *GetAddrEndOfPool(vsa_t *vsa)
{
	return (((char *)vsa) + (vsa->pool_size));
}
