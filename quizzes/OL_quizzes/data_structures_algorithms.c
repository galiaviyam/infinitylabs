#include <stdio.h>
#include <assert.h>

static int Find(char *arr, size_t size, char target);

static void CircularRotate(int *arr, size_t size, size_t rotate);
static void ReverseArray(int *arr, size_t start, size_t end);

static void TestBoolResult(int result);
static void PrintArray(int *arr, size_t size);

int main(void)
{
	char arr[] = {'a', 'b', 'c', 'a', 'w', 'r', 'l'};
	int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	
	
	TestBoolResult(Find(arr, 7, 'c'));
	TestBoolResult(Find(arr, 7, 'w'));
	TestBoolResult(!Find(arr, 7, 'e'));
	
	CircularRotate(arr1, 9, 3);
	PrintArray(arr1, 9);
	
	return 0;
}

static int Find(char *arr, size_t size, char c)
{
	size_t i = 0;
	char check = 1;
	
	for (i = 0; i < size; ++i)
	{
		check *= (arr[i] ^ c);
	}
	
	return (0 == check);
}

static void CircularRotate(int *arr, size_t size, size_t rotate)
{ 
	assert(NULL != arr);
	
	ReverseArray(arr, 0, size - 1); 
	ReverseArray(arr, 0, rotate - 1); 
	ReverseArray(arr, rotate, size - 1); 
}

static void ReverseArray(int *arr, size_t start, size_t end)
{ 
	int tmp = 0;
	
	assert(NULL != arr);
	
	while (start < end) 
	{
		tmp = arr[start]; 
		arr[start] = arr[end]; 
		arr[end] = tmp; 
		++start; 
		--end;
	}
}
     
static void PrintArray(int *arr, size_t size)
{ 
	size_t i = 0;
	
	assert(NULL != arr);
	
	for (i = 0; i < size; i++) 
	{
		printf("%d ", arr[i]);
	}
	
	printf("\n");
}

static void TestBoolResult(int result)
{
	if (result)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}

