/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	AVL             		*/
/*   Date:		31/01/23				*/
/*	 Reviewer:	Eliran					*/
/*										*/
/****************************************/
#ifndef __AVL_H__
#define __AVL_H__


#include <sys/types.h>	/* ssize_t, size_t */

/*------------------------------------------------------------------------------
	AVL tree is a self-balancing binary search tree. 
	In an AVL tree, the heights of the two child subtrees of any node differ by 
	at most one.
	if at any time they differ by more than one, rebalancing is done to restore 
	this property.

	The main functionalities are: AVLFind, AVLInsert, and AVLRemove, and all 
	have time complexity of O(log n) in both the average and worst cases.
------------------------------------------------------------------------------*/

typedef struct avl avl_t;

typedef enum traversal_order
{
	PRE = 0,
	IN,
	POST
}order_t;

/*-----------------------------------------------------------------------------
Description: 
	avl_cmp_t is the prototype of the compare function received in AVLCreate.
	This function can't be changed and it will affect the order of the nodes
	in the tree.
-----------------------------------------------------------------------------*/
typedef int (*avl_cmp_t)(const void *data1, const void *data2);

/*-----------------------------------------------------------------------------
Description - 
	avl_callback_t is the prototype of the callback function received in
	AVLForEach. 
	A function that modifies the data in a way that will require to change the 
	order of the data in the tree - will cause an undefined behavior.
-----------------------------------------------------------------------------*/
typedef int (*avl_callback_t)(void *data, void *param);

/*------------------------------------------------------------------------------
Description: 
	The AVLCreate function prepares the required resources and creates a binary 
	search tree.
	The resources must be destroyed manually using the AVLDestroy function.

Parameters:
	cmp - a comparison function to determine the order of the tree.
	needs to return an integer less than, equal to, or greater than zero if
	data1 is found, respectively, to be less than, to match, or be greater 
	than data2.

Return Value:
	The function returns a handle to the new avl tree.
	In case of a faliure, the function returns NULL.

Complexity: 
	time: O(1) / space: O(1) 
------------------------------------------------------------------------------*/
avl_t *AVLCreate(avl_cmp_t cmp);

/*------------------------------------------------------------------------------
Description: 
	The AVLDestroy function destroyes the resources used by the search tree.

Parameters:
	avl - a handle to the avl tree to be destroyed.

Complexity: 
	time: O(n) / space: O(1) 
------------------------------------------------------------------------------*/
void AVLDestroy(avl_t *avl);

/*------------------------------------------------------------------------------
Description: 
	The AVLInsert function inserts a new element to the right place in the 
	avl tree.
	Trying to insert data that already exists, will cause an undefined behavior.
	If the tree is not balanced after the insertion - it will rebalance itself.
	
Parameters:
	avl - a handle to the avl tree.
	data - a void pointer to the data to be added to the avl.
	
Return Value:
	The function returns 1 for success, and 1 for fail.
	
Complexity: 
	time: O(log(n)) / space: O(1) 
------------------------------------------------------------------------------*/
int AVLInsert(avl_t *avl, void *data);

/*------------------------------------------------------------------------------
Description: 
	The AVLRemove function removes data from the AVL.
	If the tree is not balanced after the remove - it will rebalance itself.
	
Parameters:
	avl - a handle to the avl tree.
	data - a void pointer to the data to be removed from the avl.
	
Complexity: 
	time: O(log(n)) / space: O(1) 
------------------------------------------------------------------------------*/
void AVLRemove(avl_t *avl, void *data);

/*------------------------------------------------------------------------------
Description:
	The AVLFind function searches for data in the AVL, and stores it in 
	"found_data" argument.
	
Parameters:
	avl - a handle to the avl tree.
	data - data to be searched in the tree
	found_data - a pointer to store the found data (if found)
	
Return Value:
	The function returns 1 if the data was found. Otherwise it returns 0.

Comment:
	If the data was found - found_data argument will contain the complete data.
	
Complexity: 
	time: O(log(n))  / space: O(1) 
------------------------------------------------------------------------------*/
int AVLFind(const avl_t *avl, const void *data, void **found_data);

/*------------------------------------------------------------------------------
Description: 
	The AVLForEach function traverses the tree in the order received in "order" 
	argument, and calls the callback function received, with param argument.
	
Parameters:
	avl - a handle to the avl tree.
	callback - pointer to a function for the operation.
				(must match the prototype avl_callback_t)
	param - a void pointer to the argument for the operating.
	order - the traversal order. must be one from the traversal_order enum
			(IN, PRE, POST)
	
Return Value:
	The function returns the return value of the callback function.

Comment:
	If callback fails in any operation. AVLForEach stops immediatly and returns
	callback status result.

Complexity:
	time: O(n) / space: O(1) 
------------------------------------------------------------------------------*/
int AVLForEach(avl_t *avl, avl_callback_t callback, void *param, order_t order);

/*------------------------------------------------------------------------------
Description: 
	The AVLGetHeight function gets the height of the tree.
	
Parameters:
	avl - a handle to the avl tree.
	
Return Value:
	The function returns the height of the tree in ssize_t,
	if the tree is empty - the function returns -1.
		
Complexity: 
	time: O(1) / space: O(1) 
------------------------------------------------------------------------------*/
ssize_t AVLGetHeight(const avl_t *avl);

/*------------------------------------------------------------------------------
Description: 
	The AVLCount function counts the elements in the AVL. 
	
Parameters:
	avl - a handle to the avl tree.
	
Return Value:
	The function returns the number of elements in the tree in size_t.
	
Complexity: 
	time: O(n) / space: O(1) 
------------------------------------------------------------------------------*/
size_t AVLCount(const avl_t *avl);

/*------------------------------------------------------------------------------
Description: 
	The AVLIsEmpty function checks whether the AVL is empty.
	
Parameters:
	avl - a handle to the avl tree.
	
Return Value:
	The function returns 1 if the AVL is empty. Otherwise it returns 0.
	
Complexity: 
	time: O(1) / space: O(1) 
------------------------------------------------------------------------------*/
int AVLIsEmpty(const avl_t *avl);

#endif /* __AVL_H__ */

