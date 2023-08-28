/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Comparison Sorts		*/
/*   Date:		02/02/23				*/
/*	 Reviewer:	Shauli + Itay			*/
/*										*/
/****************************************/

#ifndef __CMP_SORTS_H__
#define __CMP_SORTS_H__

#include <stddef.h> /* size_t */

typedef int (*compar_func_t)(const void *, const void *);

/*------------------------------------------------------------------------------
Description:
	Bubble sort is a simple sorting algorithm that repeatedly steps through the 
	input array element by element, comparing the current element with the one 
	after it, swapping their values if needed. These passes through the array 
	are repeated until no swaps had to be performed during a pass, meaning that 
	the array has become fully sorted.
Parameters:
	arr - the array for comparison sorting
	arr_size - number of elements in the array
	
Complexity: 
	time: O(n^2)  / space: O(1)  
------------------------------------------------------------------------------*/
void BubbleSort(int *arr, size_t size);

/*-----------------------------------------------------------------------------
Description:
	Selection sort is an in-place comparison sorting. The algorithm divides the 
	input array into two parts: a sorted sub-array of elements which is built 
	up from left to right at the front (left) of the array and a sub-array of 
	the remaining unsorted elements that occupy the rest of the array. 
	Initially, the sorted sub-array is empty and the unsorted sub-array is 
	the entire input array. The algorithm proceeds by finding the smallest 
	element in the unsorted sub-array, swapping it with the leftmost unsorted 
	element, and moving the sub-array boundaries one element to the right.

Parameters:
	arr - the array for comparison sorting
	arr_size - number of elements in the array
	
Complexity: 
	time: O(n^2)  / space: O(1)  
------------------------------------------------------------------------------*/
void SelectionSort(int *arr, size_t size);

/*------------------------------------------------------------------------------
Description:
	Insertion sort is a simple sorting algorithm that builds the final sorted 
	array one element at a time. It compares each element in the array with the 
	elements that come before it and inserts it into the proper position in 
	the sorted array. This process is repeated for all elements in the array, 
	resulting in a sorted array.

Parameters:
	arr - the array for comparison sorting
	arr_size - number of elements in the array
	
Complexity: 
	time: O(n^2)  / space: O(1)  
---------------------------------------------------------------------------*/
void InsertionSort(int *arr, size_t size);

/*---------------------------------------------------------------------------
Complexity: 
	time: O(log(n))  / space: O(1) 
---------------------------------------------------------------------------*/
int *IterBinarySearch(int *arr, int arr_size, int element_to_find);

/*---------------------------------------------------------------------------
Complexity: 
	time: O(log(n))  / space: O(1) 
---------------------------------------------------------------------------*/
int *RecBinarySearch(int *arr, int arr_size, int element_to_find);

/*---------------------------------------------------------------------------
Complexity: 
	time: O(nlog(n))  / space: O(n) 
---------------------------------------------------------------------------*/
int MergeSort(int *arr_to_sort, size_t num_elements);

/*---------------------------------------------------------------------------
Complexity: 
	time: 
	average: O(nlog(n)),  worst: O(n^2)
	
	space: 
	average: O(n), best: O(log(n))
---------------------------------------------------------------------------*/
void Qsort(void *base, size_t nmemb, size_t size, compar_func_t cmp);

#endif 	/* __CMP_SORTS_H__ */
