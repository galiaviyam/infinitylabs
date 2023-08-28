#include <stdio.h>

int MaxSubArray(int *arr, size_t size, size_t *start, size_t *end)
{
	int max_sum = 0;
	int current_sum = 0;
	int current_start = 0;
	int current_end = 0;
	size_t i;
	
	for(i = 0; i < size; ++i)
	{
		current_sum += *(arr + i);
		current_end = i;
    
		if (current_sum < 0)
		{
			current_sum = 0;
			current_start = current_end;
		}

		if (max_sum < current_sum)
		{
			max_sum = current_sum;
			*start = current_start;
			*end = current_end;
		}
	}
	return max_sum;  
}

int main()
{
	size_t i = 0;
	int arr1[9] = {-2, 1, -3, 4, -1, 2, 3, -5, 4};
    size_t *start = &i;
    size_t *end = &i;
    
	printf("The given array is :  ");
	for(i = 0; i < 9; ++i)
	{
		printf("%d  ", arr1[i]);
    }

	printf("\nThe largest sum of contiguous subarray is : %d \n", MaxSubArray(arr1, 9, start, end));
	return 0;
}
