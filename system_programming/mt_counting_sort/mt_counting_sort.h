/********************************************/
/*                                          */   
/*   Developer: Gali Aviyam                 */
/*   Project:   Multithreaded Counting Sort */
/*   Date:      12/03/23                    */
/*   Reviewer:  Shauli                      */
/*                                          */
/********************************************/

#ifndef __MT_COUNTING_SORT__
#define __MT_COUNTING_SORT__

#include <stdlib.h>		/* size_t */

/*******************************************************************
Description
	CountingSort is a numerical sorting algorithm. The function recieves an 
	unsorted array and sorts it.
	The sorting algorithm consisits of arithmetic operations to calculate the
	position of each object in the output sequence, and devide the work of 
	counting into several threads.
	
Parameters
	arr - array to sort.
	size - number of elements in the array.
	threads_num - the number of threads to devide.

Return Value
	A status code for the function: 0 if the function succeeded, and otherwise
	if failed.
	
Complexity
	Time: best case: O(n) worst case: O(n + k) / Space: O(n + k)

*******************************************************************/
int MTCountingSort(unsigned char *arr, size_t size, size_t threads_num);

#endif /* __MT_COUNTING_SORT__ */
