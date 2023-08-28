#include <stdio.h>	/* printf */
#include <assert.h>	/* assert */

static size_t FindElemInSortCircArr(int *arr, size_t start, size_t end, int target);

int main(void)
{
	int arr[6] = {7, 8, 11, 1, 4, 5};
	int target = 11;
	
	printf("Element found at index %lu\n", 
			FindElemInSortCircArr(arr, 0, 6, target));
	return 0;
}

static size_t FindElemInSortCircArr(int *arr, size_t start, size_t end, int target)
{
	size_t mid = 0;
	
	assert(NULL != arr);
	
	mid = (start + end) / 2;
	
	if (arr[mid] == target)
	{
		return mid;
	}
	
	if (arr[start] <= arr[mid])
	{
		if (target >= arr[start] && target <= arr[mid])
		{
			return (FindElemInSortCircArr(arr, start, mid - start, target));
		}
		
		return (FindElemInSortCircArr(arr, mid + start, end, target));
	}
	if (target >= arr[mid] && target <= arr[end])
	{
		return (FindElemInSortCircArr(arr, mid + start, end, target));
	}
	
	return (FindElemInSortCircArr(arr, start, mid - start, target));
}



