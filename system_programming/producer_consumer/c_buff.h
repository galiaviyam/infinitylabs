/*****************************************/
/*   Developer: Gali Aviyam              */
/*   Project: Circular Buffer 		     */				         
/*   Date: 13/12/22		            	 */
/*   Reviewer: Moriah	     			 */
/*****************************************/

#include <stddef.h> /*size_t*/
#include <sys/types.h> /*ssize_t*/

#ifndef __C_BUFF_H__
#define __C_BUFF_H__

typedef struct c_buff c_buff_t;

/*---------------------------------------------------------------------------
Description:
The CbuffCreate function creates a circular buffer.

Return Value:
The function returns a pointer to the created circular buffer.
Note: in case of a faliure, the function returns NULL.

Complexity:
	time: O(1)  / space: O(n) 
---------------------------------------------------------------------------*/
c_buff_t *CbuffCreate(size_t capacity);

/*---------------------------------------------------------------------------
Description:
The CbuffDestroy function frees the circular buffer's memory.

Complexity:
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
void CbuffDestroy(c_buff_t *cbuff);

/*---------------------------------------------------------------------------
Description:
The CbuffWrite function writes up to count bytes from src to the buffer cbuff.
trying to write to a full buffer will fail.

Return Value:
The function returns the number of bytes written as size_t.
Note: if the function failed to write, the return value will be 0.

Complexity:
	time: O(n)  / space: O(1) 
---------------------------------------------------------------------------*/
ssize_t CbuffWrite(c_buff_t *cbuff, const void *src, size_t count); 

/*---------------------------------------------------------------------------
Description:
The CbuffRead function reads up to count bytes from the buffer cbuff to dest.
trying to read from an empty buffer will fail.

Return Value:
The function returns the number of bytes read as size_t.
Note: if count is 0, the return value will be 0.

Complexity:
	time: O(n)  / space: O(1) 
---------------------------------------------------------------------------*/
ssize_t CbuffRead(c_buff_t *cbuff, void *dest, size_t count);

/*---------------------------------------------------------------------------
Description:
The CbuffGetFreeSpace function calculates the circular buffer's free space.

Return Value:
The function returns the circular buffer's free space as size_t.

Complexity:
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
size_t CbuffGetFreeSpace(const c_buff_t *cbuff);

/*---------------------------------------------------------------------------
Description:
The CbuffIsEmpty function checks if the passed argument cbuff is empty.

Return Value:
The function returns 1 for true and 0 for false.
	
Complexity: 
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
int CbuffIsEmpty(const c_buff_t *cbuff);

/*---------------------------------------------------------------------------
Description:
The CbuffCapacity function returns the circular buffer's capacity.

Return Value:
The function returns the circular buffer's capacity as size_t.

Complexity:
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
size_t CbuffCapacity(const c_buff_t *cbuff);


#endif /* __C_BUFF_H__ */
