#include <stdio.h>
#include <assert.h>

static int FindMinK(int *arr, size_t size, size_t k);
static void BubbleSort(int *arr, size_t size);
static void Swap(int *num1, int *num2);


int main()
{
	int arr[] = {1, 3, 2, 5, 7};
	
	printf("min %dth is: %d\n", 2, FindMinK(arr, 5, 2));
	printf("min %dth is: %d\n", 4, FindMinK(arr, 5, 4));

	return 0;
}

static int FindMinK(int *arr, size_t size, size_t k)
{
	assert(NULL != arr);
	
	BubbleSort(arr, size);
	
	return (arr[k-1]);
}

static void BubbleSort(int *arr, size_t size)
{
	size_t i = 0;
	size_t j = 0;
	
	assert(NULL != arr);
	
	for (i = 0; i < size - 1; ++i)
	{
		for (j = 0; j < size - i - 1; ++j)
		{
			if (*(arr + j) > *(arr + j + 1))
			{
				Swap((arr + j), (arr + j + 1));
			}
		}
	}
}

static void Swap(int *num1, int *num2)
{
	assert(NULL != num1);
	assert(NULL != num2);
	
	*num1 = *num1 ^ *num2;
	*num2 = *num1 ^ *num2;
	*num1 = *num1 ^ *num2;
}
