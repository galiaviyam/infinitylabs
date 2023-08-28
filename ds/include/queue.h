/*****************************************/
/*   Developer: Gali Aviyam              */
/*   Project: Queue		 	   		     */				         
/*   Date: 12/12/22		            	 */
/*   Reviewer: Vladimir     			 */
/*****************************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h> /* size_t */

typedef struct queue queue_t;
/*---------------------------------------------------------------------------
Description:
The QueueCreate function creates a queue.

Return Value:
The function returns a pointer to the created queue.

Complexity:
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
queue_t *QueueCreate(void);

/*---------------------------------------------------------------------------
Description:
The QueueDestroy function frees the allocated memory of the queue.
Note that passing a NULL will cause an undefined behavior.
	
Complexity:
	time: O(n)  / space: O(1) 
---------------------------------------------------------------------------*/
void QueueDestroy(queue_t *queue);

/*---------------------------------------------------------------------------
Description:
The QueueEnqueue function inserts a member with the passed argument data to the 
queue.

Return Value:
The function returns 0 for Success and 1 for fail.
	
Complexity: 
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
int QueueEnqueue(queue_t *queue, void *data);

/*---------------------------------------------------------------------------
Description:
The QueueDequeue function removes the first member of the queue.
Note that trying to remove from an empty queue will cause an undefined behavior.

Complexity:  
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
void QueueDequeue(queue_t *queue);

/*---------------------------------------------------------------------------
Description:
The QueuePeek functions returns the data of the first member of the queue as a 
void pointer.

Return Value:
The function returns the data of the first member of the queue as a void pointer.
	
Complexity: 
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
void *QueuePeek(const queue_t *queue);

/*---------------------------------------------------------------------------
Description:
The QueueIsEmpty function checks if the passed argument queue is empty.

Return Value:
The function returns 1 for true and 0 for false.
	
Complexity: 
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
int QueueIsEmpty(const queue_t *queue);
    
/*---------------------------------------------------------------------------
Description:
The QueueSize function Counts the number of members in the passed argument
queue.
	
Return Value:
The function returns the number of members in the queue.

Complexity: 
	time: O(n)  / space: O(1) 
---------------------------------------------------------------------------*/
size_t QueueSize(const queue_t *queue);

/*---------------------------------------------------------------------------
Description:
The QueueAppend function concatenates src queue to dest queue and empties the 
src queue.
Note that passing an empty src will cause an undefined behavior.

Return Value:
The function returns a pointer to the queue.

Complexity: 
	time: O(1)  / space: O(1)
---------------------------------------------------------------------------*/
queue_t *QueueAppend(queue_t *dest, queue_t *src);

#endif /* __QUEUE_H__ */
