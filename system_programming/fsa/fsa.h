/****************************************/
/*										*/
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Fixed Size Allocator	*/
/*   Date:	04/01/2023					*/
/*	 Reviewer:	Noy Cohen				*/
/*										*/
/****************************************/

/************************			DESCRIPTION		***************************/
/*-----------------------------------------------------------------------------
FSA:
	FSA (fixed size allocator) is a memory management tool used to allocate
	blocks of memory that are currently available, and keep track of the 
	available memory blocks. 
	The user needs to allocate a memory pool for the FSA, and initiallize it 
	with the FSAInit function.
	In order to know the right amount of memory to allocate, use the 
	FSARequiredPoolSize function.
-----------------------------------------------------------------------------*/

#ifndef __FSA_H__
#define __FSA_H__

#include <stddef.h> /* size_t */

/*-----------------------------------------------------------------------------
Description: 
	The management struct for the fixed-size allocator.
-----------------------------------------------------------------------------*/
typedef struct fsa fsa_t;

/*-----------------------------------------------------------------------------
Description:
	The FSARequiredPoolSize function calculates the required size for the 
	memory pool. The user must allocate the right amount of memory.
	
Parameters:
	num_of_blocks - the desired number of memory blocks.
	block_size - the desired block size.
	
Return Value:
	the function returns the total size required for the FSA, that is needed to
	allocate in order to use the FSAInit function.
	
Complexity:
	time: o(1), space: o(1) 
-----------------------------------------------------------------------------*/
size_t FSARequiredPoolSize(size_t num_of_blocks, size_t block_size);

/*-----------------------------------------------------------------------------
Description:
	The FSAInit function initiallizes the fixed-size allocator.
	
Parameters:
	memory_pool - A pointer to the user's allocated memory pool. 
	
	num_of_blocks - the desired number of blocks.
	
	block_size - the desired block size.
	
Return Value:
	the function returns a pointer to the the fixed-size allocator.

Comments:
	It is the user's responsibility to allocate the right size. You may
	use the FSARequiredPoolSize function to calculate the required size.
	
Complexity:
	time: o(n), space: o(1) 
-----------------------------------------------------------------------------*/
fsa_t *FSAInit(void *memory_pool, size_t num_of_blocks, size_t block_size);

/*-----------------------------------------------------------------------------
Description:
	The FSAAllocate function allocates a memory block from the fsa.
	
Parameters:
	fsa - A pointer to the fixed-size allocator.
	
Return Value:
	The function returns a pointer to the allocated memory block.
	In case of a faliure or If there is no space left, the function returns 
	NULL.
	
Complexity:
	time: o(1), space: o(1) 
-----------------------------------------------------------------------------*/
void *FSAAllocate(fsa_t *fsa);

/*-----------------------------------------------------------------------------
Description: 
	The FSAFree function frees the allocated memory of the given argument block
	and makes it available for future use.
	
Parameters:
	fsa - A pointer to the fixed-size allocator.
	block - The memory block to free.

Comments:
	passing a block that wasn't allocated by the FSA will cause an 
	undefined behavior.
	
Complexity:
	time: o(1), space: o(1) 
-----------------------------------------------------------------------------*/
void FSAFree(fsa_t *fsa, void *block);

/*-----------------------------------------------------------------------------
Description: 
	The FSACountFree counts the free blocks of memory in the fsa.
	
Parameters:
	fsa - A const pointer to the fixed-size allocator.
	
Return Value:
	The function returns the amount of free blocks of memory in the fsa.
	
Complexity:
	time: o(n), space: o(1) 
-----------------------------------------------------------------------------*/
size_t FSACountFree(const fsa_t *fsa);

#endif /* __FSA_H__ */
