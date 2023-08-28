#include <stdio.h>
#include <assert.h>

static void SortZeroAndOneArr(int *arr, size_t size);
static void Swap(int *a, int *b);
static void PrintArr(int *arr, size_t size);


int main(void)
{
	int arr[10] = {1, 1, 0, 1, 0, 1, 0, 0, 1, 0};
	
	printf("arr before sorting:\n");
	PrintArr(arr, 10);
	
	SortZeroAndOneArr(arr, 10);
	
	printf("\narr after sorting:\n");
	PrintArr(arr, 10);
	
	return 0;
}

static void SortZeroAndOneArr(int *arr, size_t size)
{
	size_t start = 0;
	size_t end = size - 1;
	
	assert(NULL != arr);
	
	while (start < end)
	{
		if (1 == *(arr + start))
		{
			Swap((arr + start), (arr + end));
			--end;
		}
		else
		{
			++start;
		}
	}
}

static void Swap(int *a, int *b)
{
	assert(NULL != a);
	assert(NULL != b);
	
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

static void PrintArr(int *arr, size_t size)
{
	size_t i = 0;
	
	assert(NULL != arr);
	
	for (i = 0; i < size; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}
