#include <stdio.h>
#include <assert.h>

static int IsSumFound(int *arr, size_t size, int sum, int *result);

int main()
{
	int arr[5] = {2, 4, 7, 12, 14};
	int sum = 21;
	int result[2];
	int success = 0;
	
	success = IsSumFound(arr, 5, sum, result);
	printf("index1 = %d\nindex2 = %d\nres = %d\n", result[0], result[1], success);
	return 0;
}

static int IsSumFound(int *arr, size_t size, int sum, int *result)
{
	int curr_sum = 0;
	int *start = NULL;
	int *end = NULL;
	
	assert(NULL != arr);
	assert(NULL != result);
	assert(0 < size);
	
	start = arr;
	end = arr + size -1;
	
	while (start < end)
	{
		curr_sum = (*start + *end);
		
		if (curr_sum < sum)
		{
			++start;
		}
			
		else if (curr_sum > sum)
		{
			--end;
		}
		
		else
		{
			result = start/4;
			++result;
			result = end/4;
			return 1;
		}
	}
	
	return 0;
}
