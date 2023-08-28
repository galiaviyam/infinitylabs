#include <stdio.h>	/* printf */
#include <string.h> /* memset */
#include <stdlib.h> /* malloc */
#include <assert.h>	/* assert */

/*--------------------------------- 1 --------------------------------------*/
static int Check2And6(unsigned char c)
{
	return ((c >> 1) & 1 && (c >> 5) & 1);
}

static int Check2Or6(unsigned char c)
{
	return ((c >> 1) & 1 || (c >> 5) & 1);
}

static unsigned char Swap3And5(unsigned char c)
{
	unsigned char bit_three = 0;
	unsigned char bit_five = 0;
	unsigned char swap_bits = 0;
	unsigned char mask = 0;
	
	bit_three = (c >> 2) & 1;
	bit_five = (c >> 4) & 1;	
	swap_bits = bit_three ^ bit_five;
	mask = (swap_bits << 2) | (swap_bits << 4);
	
	return (c ^ mask);
}

void PrintBin(char value)
{
    int i = 0;

    for (i = 7; i >= 0; i--)
    {
        printf("%d", (value & (1 << i)) >> i);
    }
    printf("\n");
}

void Test1(void)
{
	printf("\n************Check2And6************\n");
	printf("%d: %d\n", 34, Check2And6(34));
	printf("%d: %d\n", 20, Check2And6(20));
	
	printf("\n************Check2Or6*************\n");
	printf("%d: %d\n", 34, Check2Or6(34));
	printf("%d: %d\n", 20, Check2Or6(20));
	printf("%d: %d\n", 50, Check2Or6(50));
		
	printf("\n************Swap3And5*************\n");
	printf("before: ");
	PrintBin((char)164);
	printf("\nafter:  ");
	PrintBin(Swap3And5(164));
	printf("\n");
}
/*--------------------------------- 2 --------------------------------------*/
static void SwapInt(int *a, int *b)
{
	int tmp = 0;
	
	assert(a);
	assert(b);
	
	tmp = *a;
	*a = *b;
	*b = tmp;
}
void Test2(void)
{
	int a = 5, b = 3;
	
	printf("SwapInt %d, %d:\t", a, b);
	SwapInt(&a, &b);
	printf("result %d, %d.\n", a, b);

}
/*--------------------------------- 3 --------------------------------------*/
static void SwapIntPointer(int **a, int **b)
{
	int *tmp = NULL;
	
	assert(a);
	assert(b);
	
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void Test3(void)
{
	int a = 5, b = 3;
	int *a_ptr = NULL, *b_ptr = NULL;
	
	a_ptr = &a;
	b_ptr = &b;
	
	printf("SwapIntPointer\t%p, %p:\n", (void *)a_ptr, (void *)b_ptr);
	SwapIntPointer(&a_ptr, &b_ptr);
	printf("result\t\t%p, %p.\n", (void *)a_ptr, (void *)b_ptr);

}
/*--------------------------------- 4 --------------------------------------*/
static void SwapVoidPointer(void **a, void **b)
{
	void *tmp = NULL;
	
	assert(a);
	assert(b);
	
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void Test4(void)
{
	void *a_ptr = NULL, *b_ptr = (void *)1;
	
	printf("SwapVoidPointer\t%p, %p:\n", a_ptr, b_ptr);
	SwapVoidPointer(&a_ptr, &b_ptr);
	printf("result\t\t%p, %p.\n", a_ptr, b_ptr);

}
/*--------------------------------- 6 --------------------------------------*/
static int *CreateArr(size_t size)
{
	int *arr = (int *)malloc(sizeof(int) * size);
	if (NULL == arr)
	{
		return NULL;
	}
	
	return arr;
}

void Test6(void)
{
	int *arr = CreateArr(10);
	
	printf("CreateArr\t%p\n", (void *)arr);
	arr[9] = 0;

	free(arr);
	arr = NULL;
}
/*--------------------------------- 7 --------------------------------------*/
static int **Create2DArr(size_t rows, size_t cols)
{
	size_t i = 0;
	int *arr = NULL;
	int **res = (int **)malloc((rows * sizeof(int *)) + (cols * rows * sizeof(int)));
	if (NULL == res)
	{
		return NULL;
	}
	
	arr = (int *)&res[rows];
	
	for (i = 0; i < rows; ++i)
	{
		res[i] = arr + (cols * i);
	}

	return res;
}

void Test7(void)
{
	int **arr = Create2DArr(5, 5);
	
	printf("Create2DArr\t%p\n", (void *)arr);
	arr[0][0] = 0;
	arr[4][0] = 0;
	arr[0][4] = 0;
	arr[4][4] = 0;

	free(arr);
	arr = NULL;
}
/*--------------------------------- 8 --------------------------------------*/
static int *ResetArr(int *arr, size_t size)
{
	assert(arr);
	
	memset((void *)arr, 0, size * sizeof(int));
	
	return arr;
}

void Test8(void)
{
	int *arr = CreateArr(5);
	int i = 0;
	
	for (i = 0; i < 5; ++i)
	{
		arr[i] = i;
	}
	
	for (i = 0; i < 5; ++i)
	{
		printf("arr[%d]: %d\n", i, arr[i]);
	}
	
	printf("ResetArr:\n");
	ResetArr(arr, 5);
	
	for (i = 0; i < 5; ++i)
	{
		printf("arr[%d]: %d\n", i, arr[i]);
	}

	free(arr);
	arr = NULL;
}
/*--------------------------------- 9 --------------------------------------*/
static int **Reset2DArr(int **arr, size_t rows, size_t cols)
{
	size_t i = 0;
	
	assert(arr);
	
	for (i = 0; i < rows; ++i)
	{
		arr[i] = ResetArr(arr[i], cols);
	}
	
	return arr;
}

void Test9(void)
{
	int **arr = Create2DArr(3, 3);
	int i = 0, j = 0;
	
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			arr[i][j] = ((i * 3) + j);
		}
	}
	
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			printf("arr[%d][%d]: %d\n", i, j, arr[i][j]);
		}
	}
	
	printf("Reset2DArr:\n");
	Reset2DArr(arr, 3, 3);
	
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			printf("arr[%d][%d]: %d\n", i, j, arr[i][j]);
		}
	}

	free(arr);
	arr = NULL;
}


int main()
{
	printf("Question 1:\n");
	Test1();
	printf("\n");
	printf("Question 2:\n");
	Test2();
	printf("\n");
	printf("Question 3:\n");
	Test3();
	printf("\n");
	printf("Question 4:\n");
	Test4();
	printf("\n");
	printf("Question 6:\n");
	Test6();
	printf("\n");
	printf("Question 7:\n");
	Test7();
	printf("\n");
	printf("Question 8:\n");
	Test8();
	printf("\n");
	printf("Question 9:\n");
	Test9();
	printf("\n");

	return 0;
}

