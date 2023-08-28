/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Linear Sorts			*/
/*   Date:		16/01/23				*/
/*	 Reviewer:	Aviv					*/
/*										*/
/****************************************/

#ifndef __LINEAR_SORT_H__
#define __LINEAR_SORT_H__

/*   Includes   */

#include <stddef.h> /* size_t */


/*******************************************************************
Description
	CountingSort is an integer sorting algorithm. The function recieves an 
	unsorted array and sorts it.
	The sorting algorithm consisits of arithmetic operations to calculate the
	position of each object in the output sequence. 
	
Parameters
	arr - array to sort.
	size - number of elements in the array.

Return Value
	A status code for the function: 0 if the function succeeded, and otherwise
	if failed.
	
Complexity
	Time: best case: O(n) worst case: O(n + k) / Space: O(n + k)

*******************************************************************/
int CountingSort(int *arr, size_t size);

/*******************************************************************
Description
	Radix sort is a non-comparative integer sorting algorithm that sorts data 
	with integer keys by grouping the keys based on their individual digits. 
	The function recieves an unsorted array and sorts it.
	Note! The radix in this implementation for integers is a power of ten.
	
Parameters
	arr - array to sort.
	size - number of elements in the array.
	exp_of_ten - the power of ten for the radix to sort by- determines the 
				 number of digits in each "chunk" of sorting.


Return Value
	A status code for the function: 0 if the function succeeded, and otherwise
	if failed.

Complexity
	Time: O(k*n) / Space: O(n + k)
*******************************************************************/
int RadixSort(int *arr, size_t size, size_t exp_of_ten);


#endif 	/* __LINEAR_SORT_H__ */
