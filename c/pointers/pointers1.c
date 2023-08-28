#include <stdio.h>
#include <stdlib.h>
#define MAX 5
const int ERROR = -1;

static void Swap(int *a, int *b);
static int *CopyArray(int *arr, size_t size);
static void PrintArray(int *arr, int size);
static void SwapTwoSizeT(size_t *a, size_t *b);
static void SwapTwoPointers(size_t **a, size_t **b);

int main()
{
	int a = 1;
	int b = 2;
	
	int arr[MAX] = {1, 30, 4, 2, 17};
	int *newArr;
	
	size_t num1 = 1, num2 = 2;	
	size_t *num1_p = &num1;
	size_t *num2_p = &num2;
	
	/* swap test */
	printf("\n***********swap************\n");
	
	Swap(&a, &b);
	
	printf("a: %d b: %d\n", a, b);
	
	/* copy array test */
	printf("\n********copy array********\n");



	newArr = CopyArray(arr, MAX);
	
	printf("Original array:\n");
	PrintArray(arr, MAX);
	
	printf("\nNew array:\n");
	PrintArray(newArr, MAX);
	
	free(newArr);
	
	/* swap size_t test */
	
	printf("\n********swap pointers*********\n");
	
	printf("before swap:\na: %ld b: %ld\n", *num1_p, *num2_p);
	
	SwapTwoPointers(&num1_p, &num2_p);
	
	printf("after swap:\na: %ld b: %ld\n", *num1_p, *num2_p);
	
	return 0;
}

static void Swap(int *a, int *b)
{
	int tmp = *a;

	*a = *b;

	*b = tmp;
}

static int *CopyArray(int *arr, size_t size)
{
	size_t i = 0;
	
	int *newArr = malloc(size * sizeof(int));

	if (NULL != newArr)
	{
		for (i = 0; i < size; i++)
		{
			*(newArr + i) = *(arr + i);
		}
	}
	
	return newArr;
}

/* helper */
static void PrintArray(int *arr, int size)
{
    int i;

    for (i = 0; i < size; i++)
    {
        printf("%d\n", *(arr + i));
    }
}

static void SwapTwoSizeT(size_t *a, size_t *b)
{
	size_t tmp = *a;
	
	*a = *b;
	*b = tmp;
}

static void SwapTwoPointers(size_t **a, size_t **b)
{
	SwapTwoSizeT(*a, *b);
}
