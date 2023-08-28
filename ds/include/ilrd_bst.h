/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Binary Search tree		*/
/*   Date:		18/01/23				*/
/*	 Reviewer:	Gal						*/
/*										*/
/****************************************/

#ifndef __ILRD_BST_H__
#define __ILRD_BST_H__

#include <stddef.h> /* size_t */

/*------------------------------------------------------------------------------
Binary Search Tree:
	A binary search tree (BST) is a type of data structure that stores a 
	collection of items in a tree-like structure. Each item has a value 
	associated with it, and the items are organized in the tree such that for 
	any given node, all the items in its left subtree have values that are less 
	than its value, and all the items in its right subtree have values that are 
	greater than its value. This allows for efficient searching, insertion, and 
	deletion of items in the tree, as well as efficient traversals of the items 
	in sorted order.

MAIN FUNCTIONALITY: 
	The main functions are Insert, Remove and Find, with the time complexity 
	of avg: O(log(n)) and worst O(n). 
------------------------------------------------------------------------------*/

typedef struct bst bst_t;
typedef struct bst_node bst_node_t;
typedef bst_node_t *bst_iter_t;

/*
Description - 
	bst_cmp_t is the prototype of the compare function received in BSTCreate.
	This function can't be changed and it will affect the order of the nodes
	in the tree.

*/
typedef int (*bst_cmp_t)(const void *data1, const void *data2);

/*
Description - 
	bst_callback_t is the prototype of the callback function received in
	BSTForEach. 
	A function that modifies the data in a way that will require to change the 
	order of the data in the tree - will cause an undefined behavior.

*/
typedef int (*bst_callback_t)(void *data, void *param);

/*-----------------------------------------------------------------------------
Description: 
	The BSTCreate function prepares the required resources and creates a binary 
	search tree.
	The resources must be destroyed manually using the BSTDestroy function.

Parameters:
	cmp - a comparison function to determine the order of the tree.
	needs to return an integer less than, equal to, or greater than zero if
	data1 is found, respectively, to be less than, to match, or be greater 
	than data2.

Return Value:
	The function returns a handler to the new binary search tree.
	In case of a faliure, the function returns NULL.
	
Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
bst_t *BSTCreate(bst_cmp_t cmp);

/*-----------------------------------------------------------------------------
Description: 
	The BSTDestroy function destroyes the resources used by the search tree.

Parameters:
	bst - a handler to the binary search tree to be destroyed.
		
Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
void BSTDestroy(bst_t *bst);
/*-----------------------------------------------------------------------------
Description: 
	The BTSInsert function inserts a new element to the right place in the 
	binary search tree.
	Trying to insert data that already exists, will cause an undefined behavior.
	
Parameters:
	bst - a handler to the binary search tree.
	data - a void pointer to the data to be added to the binary search tree.
	
Return Value:
	The function returns an iterator to the data inserted.
	
Complexity: 
	time: average - O(log(n)) ,worst - O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
bst_iter_t BSTInsert(bst_t *bst, void *data);

/*-----------------------------------------------------------------------------
Description: 
	The BSTRemove function removes the iterator "where" from the BST.
	It is recommended to use the output of BSTFind() as the iterator.
	The function can cause 'where' to become invalid.
	Trying to remove the EOT will cause an undefined behavior
	
Parameters:
	where - iterator of the element to be removed from the BST.
	
Complexity: 
	time: average - O(log(n)) ,worst - O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
void BSTRemove(bst_iter_t where);

/*-----------------------------------------------------------------------------
Description: 
	The BSTFind function iterates the tree in-order and returns the iterator 
	with the desired data.

Parameters: 	
	bst - a handler to the binary search tree.
	data - a void pointer to the data to be searched in the binary search tree.
	
Return Value:
	The function returns an iterator 
	with the desired data.
	If the desired data is not found, it returns the EOT.

Complexity: 
	time: average - O(log(n)) ,worst - O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
bst_iter_t BSTFind(const bst_t *bst, const void *data);

/*-----------------------------------------------------------------------------
Description: 
	The BSTNext function finds the next in-order element to the current iterator 
	received from the user. 
	Passing the EOT as "current" will cause an undefined behavior.

Parameters:	
	current - iterator of an element in the BST.
	
Return Value:
	The function returns the iterator to the next in-order element.
	
Complexity: 
	time: average - O(log(n)) ,worst - O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
bst_iter_t BSTNext(bst_iter_t current);

/*-----------------------------------------------------------------------------
Description: 
	The BSTPrev function finds the previous in-order element of the current 
	iterator received from the user. 
	Passing the output of BSTBegin() as "current" will cause an undefined 
	behavior.
	
Parameters:
	current - iterator of an element in the BST.
	
Return Value:
	The function returns the iterator to the previous in-order element.
	
Complexity: 
	time: average - O(log(n)) , worst - O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
bst_iter_t BSTPrev(bst_iter_t current);

/*-----------------------------------------------------------------------------
Description:
	The BSTIsEqual function compares between two iterators.
	
Parameters:	
	one - an iterator of an element in the BST to compare.
	other - an iterator to compare with one.
	
Return Value:
	The function returns 1 if the iterators are the same. Otherwise it returns 0.
	
Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
int BSTIsEqual(bst_iter_t one, bst_iter_t other);

/*-----------------------------------------------------------------------------
Description: 
	The BSTBegin function finds the beginning of the tree - the iterator with 
	the smallest value in the tree.

Parameters:
	bst - a handler to the binary search tree.
	
Return Value:
	The function returns an iterator to the element which has the smallest value 
	data in the BST.

Complexity: 
	time: average - O(log(n)) ,worst - O(n) / space: O(1) 
-----------------------------------------------------------------------------*/
bst_iter_t BSTBegin(const bst_t *bst);

/*-----------------------------------------------------------------------------
Description: 
	The BSTEnd function finds the end of the tree.
	
Parameters:
	bst - a handler to the binary search tree.
	
Return Value:
	The function returns an iterator to the EOT.
	
Complexity: 
	time: O(1) / space: O(1) 
-----------------------------------------------------------------------------*/
bst_iter_t BSTEnd(const bst_t *bst);

/*-----------------------------------------------------------------------------
Description:
	The BSTForEach function iterates the tree in order, operates a given 
	function 'callback' for each element in a range between from and to.
	passing 'from' and 'to' that are not from the same BST will cause an 
	undfined behavior.

Parameters:
	from - starting iterator for the range for operation.
	to - ending iterator for the range for operation. "to" is not included in 
		the search.
	callback - pointer to a function for the operation.
	param - a void pointer to the data for the operating.
Return Value:
	The function returns 0 if the callback function succeeded on all of the 
	elements in the range.
	Otherwise, it returns 1.
	
Complexity: 
	time: average - O(nlog(n)) ,worst - O(n^2) / space: O(1) 
-----------------------------------------------------------------------------*/
int BSTForEach(bst_iter_t from, bst_iter_t to, bst_callback_t callback,
																	void *param);
																	
/*-----------------------------------------------------------------------------
Description: 
	The BSTCount function counts the elements in the BST. 
	
Parameters:
	bst - a handler to the binary search tree.
	
Return Value:
	The function returns the number of elements in the BST in size_t.
	
Complexity: 
	time: average - O(nlog(n)) ,worst - O(n^2) / space: O(1) 
-----------------------------------------------------------------------------*/
size_t BSTCount(const bst_t *bst);

/*-----------------------------------------------------------------------------
Description: 
	The BSTIsEmpty function checks whether the BST is empty.
	
Parameters:
	bst - a handler to the binary search tree.
	
Return Value:
	The function returns 1 if the BST is empty. Otherwise it returns 0.
	
Complexity: 
	time: O(1) / space: O(1) 
-----------------------------------------------------------------------------*/
int BSTIsEmpty(const bst_t *bst);

/*-----------------------------------------------------------------------------
Description: 
	The BSTGetVal function gets the value stored in the given element of 
	the BST.
	
Parameters:
	iter - iterator of an element in the BST.
	
Return Value:
	The function returns a void pointer to the data that is stored in the 
	iterator.

Complexity: 
	time: O(1) / space: O(1) 
-----------------------------------------------------------------------------*/
void *BSTGetVal(bst_iter_t iter);

#endif /* __ILRD_BST_H__ */

