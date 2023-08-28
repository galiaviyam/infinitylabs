/*
Find the element in an array (excluding) which separates the array into two sub 
arrays with equal sums and return it. 
For example:
Input: 1, 4, 2, 5
Output: 2
Explanation: If 2 is the partition then the sub arrays are:
{1, 4} and {5}
Input: 2, 3, 4, 1, 4, 5
Output: 1
Explanation: If 1 is the partition then the sub arrays are:
{2, 3, 4} and {4, 5}
*/

#include <stdio.h> /* printf */
#include <assert.h> /* assert */

int FindSeperator(int *array, size_t size);

int main()
{
	int arr1[4] = {1,4,2,5};
	int ans1 = 2;
	int arr2[6] = {2,3,4,1,4,5};
	int ans2 = 1;
	int arr3[7] = {0,1,2,17,8,-5};
	int ans3 = 17;
	int arr4[7] = {-5,8,12,2,1,0};
	int ans4 = 12;
	
	printf("Test 1: ");
	if (ans1 == FindSeperator(arr1, 4))
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf("FAIL!\n");
	}
	
	printf("Test 2: ");
	if (ans2 == FindSeperator(arr2, 6))
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf("FAIL!\n");
	}
	
	printf("Test 3: ");
	if (ans3 == FindSeperator(arr3, 7))
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf("FAIL!\n");
	}
	
	printf("Test 4: ");
	if (ans4 == FindSeperator(arr4, 7))
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf("FAIL!\n");
	}
	return 0;
}

int FindSeperator(int *array, size_t size)
{
	int start = 0;
	int end = size - 1;
	int sum_start = 0;
	int sum_end = 0;
	
	assert(NULL != array);
	
	sum_start = *(array + start);
	sum_end = *(array + end);
	
	while (2 < (end - start))
	{
		if (sum_start < sum_end)
		{
			++start;
			sum_start += *(array + start);
		}
		else
		{
			--end;
			sum_end += *(array + end);
		}
	}
	
	return *(array + start + 1);
}

