/*****************************************/
/*										 */   
/*	 Developer: Gali Aviyam				 */
/*   Project: sorted list		  	 	 */
/*   Last Modified:	21/12/22			 */
/*	 Reviewer: Sveta					 */
/*					 					 */
/*****************************************/

#ifndef __SORTLIST_H__
#define __SORTLIST_H__

#include <stddef.h>		/* size_t */

#include "dlist.h"      /*doubly linked list*/

/****************************************************************************/
/*																			*/
/*	A sorted linked list is a linear data structure containing a set of		*/
/*	sequential accessed links of records called nodes, that are sorted by a */
/*	given order.															*/
/*	Each node contains data for storage and	links for the next and previous */
/*	nodes.																	*/
/*	The last element of the sorted linked list is called end-of-list (EOL).	*/ 
/*																			*/
/****************************************************************************/

typedef struct sort_list sort_list_t;

typedef int (*sort_list_cmp_t)(const void *data1, const void *data2);
typedef int (*sort_list_do_action_t)(void *data, void *param);
typedef int (*sort_list_is_match_t)(const void *data, void *param);

struct sort_list_iter
{
	dlist_iter_t iter;
    #ifndef NDEBUG
	    sort_list_t *list;
    #endif
};

typedef struct sort_list_iter sort_list_iter_t;

/*-----------------------------------------------------------------------------
Description:
	The SortListCreate function allocates a new sorted linked list.  
	Memory for the Sort List is dynamically allocated, and can be freed with
	SortListDestroy.
Parameters:
	cmp - a comparison function to determine the order of the sorted list.
		needs to return an integer less than, equal to, or greater than zero if
	 	data1 is found, respectively, to be less than, to match, or be greater 
	 	than data2.
Return Value:
	The function returns a pointer to the new sorted linked list.
	In case of a faliure, the function returns NULL.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
sort_list_t *SortListCreate(sort_list_cmp_t cmp);

/*-----------------------------------------------------------------------------
Description:
	The SortListDestroy function frees all list's allocated memory. 

Parameters:
	list - pointer to the sorted linked list to be destroyed.

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
void SortListDestroy(sort_list_t *list);

/*-----------------------------------------------------------------------------
Description:
	The SortListInsert function inserts an element to the right place in the 
	sorted linked list. 
	Memory for the element is dynamically allocated, and can be freed with 
	SortListDestroy, SortListRemove, SortListPopBack & SortListPopFront.

Parameters:
	list - pointer to the sorted linked list to insert to.
	data - a void pointer to the data to be inserted.	
	
Return Value:
	The function returns the iterator of the new element.
	In case of a faliure, the function returns an iterator to the end of list.

Complexity: 
	time: O(1), worst: O(n) / space: O(1) 
-----------------------------------------------------------------------------*/
sort_list_iter_t SortListInsert(sort_list_t *list, void *data);

/*-----------------------------------------------------------------------------
Description:
	The SortListRemove function removes the iterator where from the list. 
	Passing an empty list will cause an undefined behavior. 
	Passing an iterator that points to end of list will cause an undefined 
	behavior. 

Parameters:
	iter - iterator to the element to be removed from the list.
	
Return Value:
	The function returns an iterator to the next element in the list.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
sort_list_iter_t SortListRemove(sort_list_iter_t iter);

/*-----------------------------------------------------------------------------
Description:
	The SortListFind function finds the first iterator in the received range 
	that holds the same data as in param. The function uses the cmp comparison 
	function that is passed to the list at creation.

Parameters:
	from - starting iterator for the range to find.
	to - ending iterator for the range to find. "to" is not included in the 
		search.
	param - a pointer to the data to check matching.
	
Return Value:
	The function returns an iterator to the first match.
	In case of not finding, the function returns the iterator "to".

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/	
sort_list_iter_t SortListFind(const sort_list_t *list ,const sort_list_iter_t from,
							 const sort_list_iter_t to, const void *param);
							 
/*-----------------------------------------------------------------------------
Description:
	The SortListFindIf function finds the first iterator in the received range 
	thet holds the same data as in param. The function uses the is_match 
	function to perform the comparison.

Parameters:
	from - starting iterator for the range to find.
	to - ending iterator for the range to find. "to" is not included in the 
		search.
	is_match - pointer to a comparison function.
	param - a pointer to the data to check matching.
	
Return Value:
	The function returns an iterator to the first match.
	In case of not finding, the function returns the iterator "to".

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/									 
sort_list_iter_t SortListFindIf(const sort_list_iter_t from, 
							   const sort_list_iter_t to, 
							   sort_list_is_match_t is_match, void *param);
							    
/*-----------------------------------------------------------------------------
Description:
	The SortListForEach function operates a given function for each element in 
	a range.
	'from' and 'to' that are not from the same list will cause an undfined
	behavior.

Parameters:
	from - starting iterator for the range for operation.
	to - ending iterator for the range for operation. "to" is not included in 
		the search.
	do_action - pointer to a function for the operation.
	param - a pointer to the data for the operating.
	
Return Value:
	The function returns a status code. Success (0) if the do_action function
	succeeds, and Fail, if the do_action function fails.
	
	received function fails in its operation with an iterator
	in the range fail status is returned. Otherwise, success status.

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
int SortListForEach(sort_list_iter_t from, sort_list_iter_t to, 
			        sort_list_do_action_t do_action, void *param);
			        
/*-----------------------------------------------------------------------------
Description:
	The SortListBegin function recieves a list and returns an iterator to the 
	first element of the list. 

Parameters:
	list - pointer to the sorted linked list.
	
Return Value:
	The function returns an iterator to the first element of the list.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
sort_list_iter_t SortListBegin(const sort_list_t *list);

/*-----------------------------------------------------------------------------
Description: 
	The SortListEnd function recieves a sorted list and returns the end of the 
	list.
	 
Parameters:
	list - pointer to the sorted linked list.
	
Return Value:
	The function returns an iterator to the end of the list.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
sort_list_iter_t SortListEnd(const sort_list_t *list);

/*-----------------------------------------------------------------------------
Description:
	The SortListNext function finds the next element of the current iterator. 

Parameters:
	current - an iterator to an element in a list.
	
Return Value:
	 The function returns an iterator to the next element.
	 passing the end of the list will cause an undefined behavior.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
sort_list_iter_t SortListNext(sort_list_iter_t current);

/*-----------------------------------------------------------------------------
Description:
	The SortListPrev function finds the previous element of the current iterator. 

Parameters:
	current - an iterator to an element in the list.
	
Return Value:
	 The function returns an iterator to the previous element.
	 passing the first element of the list will cause an undefined behavior.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
sort_list_iter_t SortListPrev(sort_list_iter_t current);

/*-----------------------------------------------------------------------------
Description:
	The SortlistGetVal function gets the value stored in the given element of 
	the list.

Parameters:
	iter - an iterator to the relevant data.
	
Return Value:
	The function returns a void pointer to the data that is stored in the 
	iterator.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
void *SortlistGetVal(const sort_list_iter_t iter);

/*-----------------------------------------------------------------------------
Description:
	The SortListIterIsEqual function compares between two iterators.
	
Parameters:
	one - an iterator to compare.
	other - an iterator to compare with one.
	
Return Value:
	The function returns 1 if the iterators are the same. Otherwise it returns 0.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
int SortListIterIsEqual(const sort_list_iter_t one, const sort_list_iter_t other);

/*-----------------------------------------------------------------------------
Description: 
	The SortListCount function counts the elements in the list. 
	
Parameters:
	list - a pointer to the sorted linked list.
	
Return Value:
	The function returns the number of elements in the list. 

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
size_t SortListCount(const sort_list_t *list);

/*-----------------------------------------------------------------------------
Description:
	The SortListIsEmpty function checks whether the list is empty.

Parameters:
	list - a pointer to the sorted linked list.
	
Return Value:
	The function returns 1 if the list is empty. Otherwise it returns 0.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
int SortListIsEmpty(const sort_list_t *list);

/*-----------------------------------------------------------------------------
Description:
	The SortListPopFront function removes the node from the beginning of the 
	list. 
	Passing an empty list will cause an undefined behavior.  

Parameters:
	list - pointer to the sorted linked list.
	
Return Value:
	The function returns a pointer to the data inside the removed element.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
void *SortListPopFront(sort_list_t *list);

/*-----------------------------------------------------------------------------
Description:
	The SortListPopBack function removes the node from the end of the list. 
	Passing an empty list will cause an undefined behavior. 

Parameters:
	list - pointer to the sorted linked list.
	
Return Value:
	The function returns a pointer to the data inside the removed element.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
void *SortListPopBack(sort_list_t *list);

/*-----------------------------------------------------------------------------
Description:
	The SortListMerge function combines two sorted list into one sorted list.
	Note: trying to merge two lists with different cmp function will cause and
	undefined behavior.

Parameters:
	dest - a pointer to the sorted linked list.
	src - a pointer to the sorted linked list to be merged into dest.
		after the function is called, src will be empty.

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
void SortListMerge(sort_list_t *dest, sort_list_t *src); 
/*----------------------------------------------------------------------------*/

#endif /* __SORTLIST_H__ */

