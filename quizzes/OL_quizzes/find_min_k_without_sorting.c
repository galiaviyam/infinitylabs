#include <stdio.h>
#include <assert.h>

static int FindMinK(int *arr, size_t size, size_t k);


int main()
{
	int arr[] = {1, 3, 2, 5, 7};
	
	printf("min %dth is: %d\n", 2, FindMinK(arr, 5, 2));
	printf("min %dth is: %d\n", 4, FindMinK(arr, 5, 4));

	return 0;
}

static int FindMinK(int *arr, size_t size, size_t k)
{
	int min = 0;
	int last_min = 0;
	size_t i = 0;
	size_t j = 0;
	
	assert(NULL != arr);
	
	min = *arr;
	
	for (i = 0; i < size; ++i)
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
	}
	
	for (i = 0; i < k; ++i)
	{
		 j = 0;
		 
		while (arr[j] <= min)
		{
			++j;
		}
		
		last_min = min;
		
		min = arr[j];
		
		while (j < size)
		{
			if (arr[j] < min && arr[j] > last_min)
			{
				min = arr[j];
			}
			++j;
		}
	}
	
	return min;
}
