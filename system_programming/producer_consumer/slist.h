/*****************************************/
/*   Developer: Gali Aviyam	           	 */
/*   Project: Singly Linked list         */				         
/*   Date: 04/12/22	                	 */
/*   Reviewer: Shauli                    */
/*****************************************/
#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>		/* size_t */

typedef struct slist slist_t;
typedef struct slist_node *slist_iter_t;

typedef int (*slist_do_action_t)(void *data, void *param);
typedef int (*slist_is_match_t)(const void *data, void *param);

/*---------------------------------------------------------------------------
Description:
The SlistCreate function creates a singly linked list.

Return Value:
The function returns a pointer to the created singly linked list.

Complexity:
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
slist_t *SlistCreate(void); 

/*---------------------------------------------------------------------------
Description:
The SlistDestroy function frees the allocated memory of the singly linked list
and it's iterators.
Note that passing a NULL will cause an undefined behavior.
	
Complexity:
	time: O(n)  / space: O(1) 
---------------------------------------------------------------------------*/
void SlistDestroy(slist_t *list);

/*---------------------------------------------------------------------------
Description:
The SlistInsertBefore function creates a list iterator with the passed argument
data, and inserts it to the singly linked list before the passed argument where.
Note that for the first insert it is needed to pass an iter by receiving it
from the SlistBegin function.

Return Value:
The function returns the new created iterator that contains the passed argument
data.
	
Complexity: 
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
slist_iter_t SlistInsertBefore(slist_iter_t where, void *data);

/*---------------------------------------------------------------------------
Description:
The SlistRemove function removes the passed argument where from the singly 
linked list.
Note that trying to remove the last iterator will cause an undefined behavior.

Return Value:
The function returns the iterator after the removed one in the list.
	
Complexity:  
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
slist_iter_t SlistRemove(slist_iter_t where);

/*---------------------------------------------------------------------------
Description:
The SlistFind function finds in which iterator between 
the passed arguments from and to the passed argument data is located, using the 
passed argument function pointer is_match.

Return Value:
The function returns the iterator in which data is matches to the passed one.
if there isn't one, the functions returns to. 

Complexity:
	time: O(n)  / space: O(1) 
---------------------------------------------------------------------------*/
slist_iter_t SlistFind(const slist_iter_t from, const slist_iter_t to, 
					   slist_is_match_t is_match, void *param);
					   
/*---------------------------------------------------------------------------
Description:
The SlistForEach function runs through the list between the passed arguments 
from and to, and performs the do_action function, which is passed as an 
argument.

Return Value:
The function returns a SUCCESS ir FAIL status for the action on every iterator 
in range.

Complexity:
	time: O(n)  / space: O(1) 
---------------------------------------------------------------------------*/
int SlistForEach(slist_iter_t from, slist_iter_t to, 
			     slist_do_action_t do_action, void *param); 

/*---------------------------------------------------------------------------
Description:
The SlistGetVal functions finds the value that is placed in the passed argument 
iter.

Return Value:
The function returns the data within the specified iter.
	
Complexity: 
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
void *SlistGetVal(const slist_iter_t iter);

/*---------------------------------------------------------------------------
Description:
The SlistSetVal function sets the value of the passed argument iter to the 
value of the passed argument data.

Return Value:
The function returns the iter after changing it's value.
	
Complexity:
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
slist_iter_t SlistSetVal(slist_iter_t iter, void *data);

/*---------------------------------------------------------------------------
Description:
The SlistCount function Counts the number of iterators in the passed argument list.
	
Return Value:
The function returns the number of iterators in the list.

Complexity: 
	time: O(n)  / space: O(1) 
---------------------------------------------------------------------------*/
size_t SlistCount(const slist_t *list);

/*---------------------------------------------------------------------------
Description:
The SlistIterIsEqual function checks if two passed iterators are the same.

Return Value:
The function returns 1 for true and 0 for false.
	
Complexity: 
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
int SlistIterIsEqual(const slist_iter_t one, const slist_iter_t other);

/*---------------------------------------------------------------------------
Description:
The SlistIsEmpty function checks if the passed argument list is empty.

Return Value:
The function returns 1 for true and 0 for false.
	
Complexity: 
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
int SlistIsEmpty(const slist_t *list);

/*---------------------------------------------------------------------------
Description:
The SlistBegin function returns the first iterator of the passed argument list.

Return Value:
The function returns the first iterator of the passed argument list.

Complexity: 
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/
slist_iter_t SlistBegin(const slist_t *list);

/*---------------------------------------------------------------------------
Description:
The SlistEnd function returns the last iterator of the passed argument list.

Return Value:
The function returns the last iterator of the passed argument list.

Complexity: 
	time: O(1)  / space: O(1)
---------------------------------------------------------------------------*/
slist_iter_t SlistEnd(const slist_t *list);

/*---------------------------------------------------------------------------
Description:
The SlistAppend function concatenates src list to dest list and empties the src
list.

Return Value:
The function returns a pointer to the list.

Complexity: 
	time: O(1)  / space: O(1)
---------------------------------------------------------------------------*/
slist_t *SlistAppend(slist_t *dest, slist_t *src);

#endif /* __SLIST_H__ */
