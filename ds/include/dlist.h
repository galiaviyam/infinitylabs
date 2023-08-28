/****************************************/
/*	 Developer: Gali Aviyam				*/
/*   Project: doubly linked list		*/
/*   Last Modified:	19/12/22			*/
/*	 Reviewer: Ariel Biton				*/
/****************************************/

#ifndef __DLIST_H__
#define __DLIST_H__

#include <stddef.h>		/* size_t */

typedef struct dlist dlist_t;
typedef struct dlist_node *dlist_iter_t;

typedef int (*dlist_do_action_t)(void *data, void *param);
typedef int (*dlist_is_match_t)(const void *data, void *param);

/****************************************************************************/
/*																			*/
/*	A doubly linked list is a data structure where a set of sequential links*/
/*	of records called nodes exist. A node contains data for storage and		*/
/*	links for the next and previous nodes. Hence it is part of linear data	*/
/*	structure. The last element of doubly linked list is end-of-list (EOL).	*/ 
/*																			*/
/****************************************************************************/

/*-----------------------------------------------------------------------------
Description:
	The DlistCreate function allocates a new doubly linked list.  
	
Return Value:
	The function returns a pointer to the new doubly linked list.
	In case of a faliure, the function returns NULL.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_t *DlistCreate(void); 


/*-----------------------------------------------------------------------------
Description:
	The DlistDestroy function frees all list's allocated memory. 

Parameters:
	list - pointer to the doubly linked list to be destroyed

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
void DlistDestroy(dlist_t *list);


/*-----------------------------------------------------------------------------
Description:
	The DlistBegin function recieves a list and returns the first element of 
	the list. 

Parameters:
	list - pointer to the doubly linked list.
	
Return Value:
	The function returns an iterator to the first element of the list.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_iter_t DlistBegin(const dlist_t *list);


/*-----------------------------------------------------------------------------
Description: 
	The DlistEnd function recieves a list and returns the end of the list.
	 
Parameters:
	list - pointer to the doubly linked list.
	
Return Value:
	The function returns an iterator to the end of the list

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_iter_t DlistEnd(const dlist_t *list);


/*-----------------------------------------------------------------------------
Description:
	The DlistNext function finds the next element of the list. 

Parameters:
	current - an iterator to an element in a list.
	
Return Value:
	 The function returns an iterator to the next element.
	 passing the end of the list will cause an undefined behavior.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_iter_t DlistNext(dlist_iter_t current);


/*-----------------------------------------------------------------------------
Description:
	The DlistPrev function finds the previous element of the list. 

Parameters:
	current - an iterator to an element in a list.
	
Return Value:
	 The function returns an iterator to the previous element.
	 passing the first element of the list will cause an undefined behavior.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_iter_t DlistPrev(dlist_iter_t current);


/*-----------------------------------------------------------------------------
Description: 
	The DlistPushFront function inserts a new node at the beginning of the list.
	
Parameters:
	list - pointer to the doubly linked list.
	data - a void pointer to the data to be inserted to the front of list.
	
Return Value:
	The function returns an iterator to the new element.
	In case of a faliure, the function returns an iterator to the last element.

Complexity: 
	time: O(1), worst: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_iter_t DlistPushFront(dlist_t *list, void *data);


/*-----------------------------------------------------------------------------
Description: 
	The DlistPushBack function inserts a new node at the end of the list.
	
Parameters:
	list - pointer to the doubly linked list.
	data - a void pointer to the data to be inserted to the end of list..
	
Return Value:
	The function returns an iterator to the new element.
	In case of a faliure, the function returns an iterator to the last element.

Complexity: 
	time: O(1), worst: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_iter_t DlistPushBack(dlist_t *list, void *data);


/*-----------------------------------------------------------------------------
Description:
	The DlistPopFront function removes the node from the beginning of the list. 
	Passing an empty list will cause an undefined behavior.  

Parameters:
	list - pointer to the doubly linked list.
	
Return Value:
	The function returns a pointer to the data inside the removed element.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
void *DlistPopFront(dlist_t *list);


/*-----------------------------------------------------------------------------
Description:
	The DlistPopBack function removes the node from the end of the list. 
	Passing an empty list will cause an undefined behavior. 

Parameters:
	list - pointer to the doubly linked list.
	
Return Value:
	The function returns a pointer to the data inside the removed element.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
void *DlistPopBack(dlist_t *list);


/*-----------------------------------------------------------------------------
Description:
	The DlistInsertBefore functions inserts a node to the place before the
	recieved iterator.

Parameters:
	where - iterator to the node where the data should be inserted before.
	data - a void pointer to the data to be inserted.	
	
Return Value:
	The function returns an iterator to the new element.
	In case of a faliure, the function returns an iterator to end of list.

Complexity: 
	time: O(1), worst: O(n) / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_iter_t DlistInsertBefore(dlist_iter_t where, void *data);


/*-----------------------------------------------------------------------------
Description:
	The DlistRemove function removes the iterator where from the list. 
	Passing an empty list will cause an undefined behavior. 
	Passing an iterator that points to end of list will cause an undefined 
	behavior. 

Parameters:
	where - iterator to the element to be removed from the list.
	
Return Value:
	The function returns an iterator to the next element in the list.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_iter_t DlistRemove(dlist_iter_t where);


/*-----------------------------------------------------------------------------
Description:
	The DlistFind function finds the first iterator in the received range which 
	holds the same data as in param.

Parameters:
	from - starting iterator for the range to find.
	to - ending iterator for the range to find. "to" is not included in the 
		search.
	is_match - pointer to a conparison function.
	param - a pointer to the data to check matching.
	
Return Value:
	The function returns an iterator to the first match.
	In case of not finding, the function returns the iterator "to".

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_iter_t DlistFind(const dlist_iter_t from, const dlist_iter_t to, 
					   dlist_is_match_t is_match, void *param);
					   

/*-----------------------------------------------------------------------------
Description:
	The DlistMultiFind function finds all the values inside the iterators in a 
	range which hold the same data in param.

Parameters:
	result_list - a list to contain the results of the search.
	from - starting iterator for the range to find.
	to - ending iterator for the range to find. "to" is not included in the 
		search.
	is_match - pointer to a function for comparison.
	param - a pointer to the data to check matching.
	
Return Value:
	The function returns a status code. Success (0) if the value is found, and 
	Fail, if value wasn't found.

Complexity: 
	time: O(n)  / space: O(n) 
-----------------------------------------------------------------------------*/
int DlistMultiFind(dlist_t *result_list ,const dlist_iter_t from,
 		   const dlist_iter_t to, dlist_is_match_t is_match, void *param);


/*-----------------------------------------------------------------------------
Description:
	The DlistForEach function operates a functions for each element in a range. 

Parameters:
	from - starting iterator for the range for operation.
	to - ending iterator for the range for operation. "to" is not included in 
		the search.
	do_action - pointer to a function for operation.
	param - a pointer to the data for operating.
	
Return Value:
	The function returns a status code. Success (0) if the do_action function
	succeeds, and Fail, if the do_action function fails.
	
	received function fails in its operation with an iterator
	in the range fail status is returned. Otherwise, success status.

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
int DlistForEach(dlist_iter_t from, dlist_iter_t to, 
			     dlist_do_action_t do_action, void *param); 


/*-----------------------------------------------------------------------------
Description:
	The DlistSplice function removes the elements between "from" and "to" 
	(including "to") and inserts them to the location before "where" iterator.

Parameters:
	from - starting iterator for the range for splice.
	to - ending iterator for the range for splice, "to" is included in the 
		search.
		Passing the end of list will cause an undefined behavior.
	where - iterator in a list to the location where the spliced list should 
			move to. It can be on both same list as "to" and "from" or a 
			different list.
		
Return Value:
	The function returns an iterator to the element that was originally
	connected to the "to" iter as its next element.

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_iter_t DlistSplice(dlist_iter_t from, dlist_iter_t to,
														    dlist_iter_t where);

/*-----------------------------------------------------------------------------
Description:
	The DlistGetVal function gets the value stored in the given element of the 
	list.

Parameters:
	iter - an iterator to the relevant data.
	
Return Value:
	The function returns a void pointer to the data which stored in the iterator.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
void *DlistGetVal(const dlist_iter_t iter);


/*-----------------------------------------------------------------------------
Description:
	The DlistSetVal function sets the value of the given element of the list.
	
Parameters:
	iter - an iterator to the data that should be modified.
	data - a void pointer of the data which will be stored in the iterator.
	
Return Value:
	The function returns an iterator to the modified element.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
dlist_iter_t DlistSetVal(dlist_iter_t iter, void *data);


/*-----------------------------------------------------------------------------
Description: 
	The DlistCount function counts the elements in the list. 
	
Parameters:
	list - a pointer to the doubly linked list.
	
Return Value:
	The function returns the number of elements in the list. 

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
size_t DlistCount(const dlist_t *list);


/*-----------------------------------------------------------------------------
Description:
	The DlistIterIsEqual function compares between two iterators.
	
Parameters:
	one - an iterator to compare.
	other - an iterator to compare with one.
	
Return Value:
	The function returns 1 if the iterators are the same. Otherwise it returns 0.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
int DlistIterIsEqual(const dlist_iter_t one, const dlist_iter_t other);


/*-----------------------------------------------------------------------------
Description:
	The DlistIsEmpty function checks whether the list is empty.

Parameters:
	list - a pointer to the doubly linked list.
	
Return Value:
	The function returns 1 if the list is empty. Otherwise it returns 0.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
int DlistIsEmpty(const dlist_t *list);

#endif /* __DLIST_H__ */
