/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Heap               		*/
/*   Date:		06/02/23				*/
/*	 Reviewer:	Gal Ventura				*/
/*										*/
/****************************************/

#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h>	/* size_t */

/*-----------------------------------------------------------------------------
Description:
	a heap is a specialized tree-based data structure which is essentially an 
	almost complete tree that satisfies the heap property: 
		in a max heap, for any given node C, if P is a parent node of C, then 
		the value of P is greater than or equal to the value of C.
		
		In a min heap, the value of P is less than or equal to the value of C.
	
	The node at the "top" of the heap (with no parents) is called the root node.
	
	The heap can be used to efficient implement a priority queue.

main functionalitis: 
	HeapPush(), HeapPop(), HeapPeek().
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
Description:
	the heap datatype.
-----------------------------------------------------------------------------*/
typedef struct heap heap_t;

/*-----------------------------------------------------------------------------
Description:
	A prototype for a function that compares the priority of elements in the 
	heap. 
	
Parameters: heap_data - the data in the heap.
			new_data - the data being added to the heap.
			param - some extra parameter to evaluate the priority.
			
Return Value: 0, negative or positive if the priority of heap_data is 
			equal to, smaller or greater than new_data.
-----------------------------------------------------------------------------*/
typedef int(*heap_cmp_t)(const void *heap_data, const void *new_data, 
																   void *param);

/*-----------------------------------------------------------------------------
Description:
	A prototype for a function that checks if two elements in the heap are equal.
	
Parameters: data - element in the heap.
			param - element to match with.
	
Return Value: 1 if they match, and 0 otherwise.
-----------------------------------------------------------------------------*/
typedef int(*heap_is_match_t)(const void *data, void *param);

/*-----------------------------------------------------------------------------
Description: 
	The HeapCreate function allocates a new heap.  
	Resources for the heap are dynamically allocated, and can be destroyed with 
	HeapDestroy.
	
Parameters:
	cmp - function to compare priority of elements(see heap_cmp_t).
	param - a parameter to use in cmp.
		
Return Value:
	The function returns a handle to the new heap.
	In case of a faliure, the function returns NULL.
	
Complexity: 
	time: O(1) / space: O(1) 
-----------------------------------------------------------------------------*/
heap_t *HeapCreate(heap_cmp_t cmp, void *param);

/*-----------------------------------------------------------------------------
Description:
	The HeapDestroy function destroys all heap's allocated resources. 
	Note! Passing a NULL as the passed argument heap will cause an undefined 
	behavior.
	
Parameters:
	heap - a handle to the heap.

Complexity: 
	time: O(1) / space: O(1) 
-----------------------------------------------------------------------------*/
void HeapDestroy(heap_t *heap);

/*-----------------------------------------------------------------------------
Description: 
	The HeapPush function inserts a new element (the passed argument data) to 
	the heap, while remaining the heap property.
	Note! Passing a NULL as the passed argument heap will cause an undefined 
	behavior.
	
Parameters:
	heap - a handle to the heap.
	data - an element to push.
	
Return Value:
	The function returns a status indicating if the push worked.
	0- success
	1- fail.
	
Complexity: 
	time: Amortized O(logn) / space: Amortized O(n) 
-----------------------------------------------------------------------------*/
int HeapPush(heap_t *heap, void *data); 

/*-----------------------------------------------------------------------------
Description: 
	The HeapPop function removes the top of the heap, while remaining the heap 
	property. 
	Note! Passing an empty heap will cause an undefined behavior. 
	
Parameters:
	heap - a handle to the heap.
	
Return Value:
	The function returns a pointer to the data inside the removed element.
	In case of a failure - the function returns NULL.

Note: failure does not indicates that the element wasn't removed.

Complexity: 
	time: Amortized O(logn) / space: Amortized O(n) 
-----------------------------------------------------------------------------*/
void *HeapPop(heap_t *heap); 

/*-----------------------------------------------------------------------------
Description:
	The HeapPeek function recieves a heap and returns the data of the 
	top of the heap.
	Note! Passing a NULL as the passed argument heap will cause an undefined 
	behavior.
	
Parameters:
	heap - a handle to the heap.
	
Return Value:
	The function returns the data of the top of the heap.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
void *HeapPeek(const heap_t *heap);

/*-----------------------------------------------------------------------------
Description: 
	The HeapRemove function searches for an element matching to the passed 
	argument data and removes it from the heap, while remaining the heap 
	property. 
	
Parameters:
	heap - a handle to the heap.
	data - the element to remove.
	is_match - function to match data with elements in the heap.
	param - a useless argument. can be NULL.
	
Return Value:
	The function returns a pointer to the data inside the removed element.
	In case of a failure - the function returns NULL.

Note: failure does not indicates that the element wasn't removed.

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
void *HeapRemove(heap_t *heap, void *data, heap_is_match_t is_match, 
																   void *param);

/*-----------------------------------------------------------------------------
Description:
	The HeapIsEmpty function checks whether the heap is empty.
	Note! Passing a NULL as the passed argument heap will cause an undefined 
	behavior.
	
Parameters:
	heap - a handle to the heap.
	
Return Value:
	The function returns 1 if the heap is empty. 
	Otherwise it returns 0.
	
Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
int HeapIsEmpty(const heap_t *heap);

/*-----------------------------------------------------------------------------
Description: 
	The HeapSize function returns the number of elements in the heap. 
	Note! Passing a NULL as the passed argument heap will cause an undefined 
	behavior.
	
Parameters:
	heap - a handle to the heap.
	
Return Value:
	The function returns the number of elements in the heap.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
size_t HeapSize(const heap_t *heap);


#endif 	/* __HEAP_H__ */



