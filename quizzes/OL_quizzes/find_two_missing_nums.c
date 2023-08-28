#include <stdio.h>
#include <assert.h>


static void FindMissingNumsMath(int *arr, int size);
static void FindMissingNumsXor(int *arr, int size);

int main()
{
	int arr[] = {1, 3, 2, 5, 7};
	
	FindMissingNumsMath(arr, 5);
	FindMissingNumsXor(arr, 5);

	return 0;
}

static void FindMissingNumsMath(int *arr, int size)
{
	int n = size + 2;
	int i = 0;
	int avg = 0;
	int arr_sum = 0;
	int sum_missing = 0;
	int num1 = 0;
	int num2 = 0;
	
	assert(NULL != arr);
	assert(n > 0);

	for (i = 0; i < size; ++i)
	{
		arr_sum += arr[i];
	}
	
	sum_missing = (n * (n + 1) / 2) - arr_sum;
	avg = sum_missing / 2;
	
	arr_sum = 0;
	
	for (i = 0; i < size; ++i)
	{
		if (arr[i] < avg)
		{
			arr_sum += arr[i];
		}
	}
	
	--avg;
	num1 = (avg * (avg + 1) / 2) - arr_sum;
	num2 = sum_missing - num1;
	
	printf("Math:\nnum1 is %d\nnum2 is %d\n", num1, num2);
}

void FindMissingNumsXor(int *arr, int size)
{
	int xor = 0;
	int num1 = 0;
	int num2 = 0;
	int i = 0;
	int mask = 0;
	int n = size + 2;
	
	assert(NULL != arr);
	
	xor = arr[0];
	
	for (i = 1; i < size; ++i)
	{
		xor ^= *(arr + i);
	}
	
	for (i = 1; i <= n; ++i)
	{
		xor ^= i;
	}
	
	mask = xor & ~(xor - 1);
	
	for (i = 0; i < size; ++i)
	{
		if (arr[i] & mask)
        {
            num1 ^= arr[i];
        }
        else
        {
            num2 ^= arr[i]; 
        }
	}
	
	for (i = 1; i <= n; ++i)
	{
		if (i & mask)
		{
			num1 ^= i;
		}
		else
		{
			num2 ^= i;
		}
	}
	printf("Xor:\nnum1 is %d\nnum2 is %d\n", num1, num2);
}

