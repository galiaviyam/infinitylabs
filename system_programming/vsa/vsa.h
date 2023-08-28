/****************************************/
/*										*/   
/*	Developer:	Gali Aviyam				*/
/*	Project:	Variable Size Allocator	*/
/*	Date:		08/01/2023				*/
/*	Reviewer:	Eliran Tessler			*/
/*										*/
/****************************************/

/************************			DESCRIPTION		***************************/
/*-----------------------------------------------------------------------------
VSA:
	VSA (variable size allocator) is a memory management tool used to allocate
	blocks of memory that are currently available, and keep track of the 
	available memory blocks. 
	The user needs to allocate a memory pool for the VSA, and initiallize it 
	with the VSAInit function.
	
	The main function is VSAAllocate. 
-----------------------------------------------------------------------------*/

#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h> /* size_t */

/*-----------------------------------------------------------------------------
Description: 
	The handle for the variable-size allocator.
-----------------------------------------------------------------------------*/
typedef struct vsa vsa_t;

/*-----------------------------------------------------------------------------
Description:
	The VSAInit function initiallizes the variable-size allocator.
	
Parameters:
	memory_pool - A pointer to the user's allocated memory pool. 
	
	pool_size - the size of recieved memory.
	
Return Value:
	the function returns a handle to the the vsa.

Comments:
	The minimum size for the memory pool is 64 bytes.
	It is the user's responsibility to allocate the right size.
	
Complexity:
	time: o(1), space: o(1) 
-----------------------------------------------------------------------------*/
vsa_t *VSAInit(void *memory_pool, size_t pool_size);

/*-----------------------------------------------------------------------------
Description:
	The VSAAllocate function allocates a memory block from the vsa.
	
Parameters:
	vsa - A handle to the fixed-size allocator.
	block_size - the desired block size.
	
Return Value:
	The function returns a pointer to the allocated memory block.
	In case of a faliure or If there is no space left, the function returns 
	NULL.
	
Complexity:
	time: o(n), space: o(1) 
-----------------------------------------------------------------------------*/
void *VSAAllocate(vsa_t *vsa, size_t block_size);

/*-----------------------------------------------------------------------------
Description: 
	The VSAFree function frees the allocated memory of the given argument block
	and makes it available for future use.
	
Parameters:
	block - The memory block to free.

Comments:
	passing a block that wasn't allocated by the VSA or a block that is already 
	freed will cause an undefined behavior.
	
Complexity:
	time: o(1), space: o(1) 
-----------------------------------------------------------------------------*/
void VSAFree(void *block);

/*-----------------------------------------------------------------------------
Description: 
	The VSAGetMaxFreeBlockSize finds the biggest avilable block to allocate.
	If there is external fragmentation, the function performs a defragmentation.
	
Parameters:
	vsa - A const handle to the vsa.
	
Return Value:
	The function returns the size of the biggest free block of memory in the 
	fsa, in size_t.
	
Complexity:
	time: o(n), space: o(1) 
-----------------------------------------------------------------------------*/
size_t VSAGetMaxFreeBlockSize(vsa_t *vsa);


#endif /* __VSA_H__ */
