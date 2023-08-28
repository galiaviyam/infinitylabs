/****************************************/
/*   Developer: Gali Aviyam				*/
/*   Project: Priority Queue			*/				         
/*   Date: 28/12/22						*/
/*   Reviewer: Karin					*/
/*										*/
/****************************************/

#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <stddef.h>	/* size_t */

/*----------------------------------------------------------------------------

Priority Queue is an data structure that is similar to a queue,
and every element has some priority value associated with it. The priority of 
the elements in a priority queue determines the order in which elements are 
served (i.e., the order in which they are removed).

Policy: Accordin to set priority, and if in any case the elements have same 
priority, they are served as per their ordering in the queue.

-----------------------------------------------------------------------------*/

/* A handle to a priority queue. */
typedef struct ilrd_pq ilrd_pq_t;

/* A pointer to a comparison function received by the user that compares the 
priority value of two elements and will be used in PQCreate. */
typedef int(*pq_cmp_t)(const void *data1, const void *data2);

/* A pointer to a boolean function that checks for a match between two 
parameters: data and param, and returns 1 if true, and 0 if false. 
The function is used in function PQErase inorder to find which element is to be 
remove from the queue. */
typedef int(*pq_is_match_t)(const void *data, void *param);

/*-----------------------------------------------------------------------------
Description:
	The PQCreate function allocates a new priority queue.  
	Resources for the priority queue are dynamically allocated, and can be 
	destroyed with PQDestroy.
Parameters:
	cmp - a comparison function to determine the priority of the priority queue.
		needs to return an integer less than, equal to, or greater than zero if
	 	data1 is found, respectively, to be less than, to match, or be greater 
	 	than data2.
Return Value:
	The function returns a handle to the new priority queue.
	In case of a faliure, the function returns NULL.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
ilrd_pq_t *PQCreate(pq_cmp_t cmp);

/*-----------------------------------------------------------------------------
Description:
	The PQDestroy function frees all priority queue's allocated memory. 
	Note! Passing a NULL as the passed argument pq will cause an undefined 
	behavior.
Parameters:
	pq - a handle to the priority queue to be destroyed.

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
void PQDestroy(ilrd_pq_t *pq);

/*---------------------------------------------------------------------------
Description:
	The PQEnqueue function inserts a new element (the passed argument data) to 
	the priority queue and will be assigned a priority value.
	Note! Passing a NULL as the passed argument pq will cause an undefined 
	behavior.

Parameters:
	pq - a handle to the priority queue.
	data - value to be inserted.
	
Return Value:
	The function returns a status indicating if the insert worked.
	0- success
	1- fail.

Complexity: 
	time: O(n)  / space: O(1) 
---------------------------------------------------------------------------*/

int PQEnqueue(ilrd_pq_t *pq, void *data);

/*-----------------------------------------------------------------------------
Description:
	The PQDequeue function removes the first element of the priority queue - the
	element with the highest priority. 
	Note! Passing an empty priority queue will cause an undefined behavior.  

Parameters:
	pq - a handle to the priority queue.
	
Return Value:
	The function returns a pointer to the data inside the removed element.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
void *PQDequeue(ilrd_pq_t *pq); 

/*-----------------------------------------------------------------------------
Description:
	The PQIsEmpty function checks whether the priority queue is empty.
	Note! Passing a NULL as the passed argument pq will cause an undefined 
	behavior.
	
Parameters:
	pq - a handle to the priority queue.
	
Return Value:
	The function returns 1 if the priority queue is empty. 
	Otherwise it returns 0.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
int PQIsEmpty(const ilrd_pq_t *pq);

/*-----------------------------------------------------------------------------
Description:
	The PQPeek function recieves a priority queue and returns the data of the 
	first element of the queue - the element with the highest priority. 
	Note! Passing a NULL as the passed argument pq will cause an undefined 
	behavior.

Parameters:
	pq - a handle to the priority queue.
	
Return Value:
	The function returns the data of the first element of the queue - the 
	element with the highest priority.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
void *PQPeek(const ilrd_pq_t *pq); 

/*-----------------------------------------------------------------------------
Description: 
	The PQSize function counts the elements in the priority queue. 
	Note! Passing a NULL as the passed argument pq will cause an undefined 
	behavior.

Parameters:
	pq - a handle to the priority queue.
	
Return Value:
	The function returns the number of elements in the priority queue. 

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
size_t PQSize(const ilrd_pq_t *pq);

/*---------------------------------------------------------------------------
Description:
	The PQClear function empties the queue.
	Note! Passing a NULL as the passed argument pq will cause an undefined 
	behavior.

Parameters:
	pq - a handle to the priority queue.

Complexity: 
	time: O(n)  / space: O(1) 
---------------------------------------------------------------------------*/ 
void PQClear(ilrd_pq_t *pq); 

/*---------------------------------------------------------------------------
Description:
	The PQErase function removes the requested element passed to the function 
	by the argument data from the queue.
	Note! Passing a NULL as the passed argument pq will cause an undefined 
	behavior.

Return Value:
	On success, the data removed is returned. 
	On fail, NULL is returned. 

Complexity:
	time: o(n), space: o(1) 
---------------------------------------------------------------------------*/ 
void *PQErase(ilrd_pq_t *pq, void *data, pq_is_match_t is_match);

#endif 	/* __PRIORITY_QUEUE_H__ */
