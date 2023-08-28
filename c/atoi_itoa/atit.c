/********************************************************************/
/* DEVELOPER:      Gali Aviyam                                      */
/* DATE MODIFIED:  4.12.2022                                        */
/* WORKSHEET NAME: ATOI ITOA                                        */
/* Reviewer:       Karin                                            */
/********************************************************************/
#include "atit.h"
#include <stddef.h> /*NULL*/
#include <assert.h> /*assert*/
#include <stdio.h> /*printf*/
#define ASCII 256

void Reverse(char *str, size_t length);
void Swap(char *x, char *y);
void InitArr(char *arr, int *arr_lut, size_t arr_size);

/****************Functions*****************/
char *ItoaBase10(int num, char *str)
{
	return ItoaAnyBase(num, str, 10);
}

char *ItoaAnyBase(int num, char *str, int base)
{
	int i = 0;
	int rem = 0;
	int negative = 0;
	
	if (0 == num)
	{
		*(str + i) = '0';
		++i;
		*(str + i) = '\0';
		
		return str;
	}
	
	if (0 > num && 10 == base)
	{
		negative = 1;
		num = -num;
	}
	
	while (0 != num)
	{
		rem = num % base;
		
		*(str + i) = rem + '0';
		++i;
		num = num/base;
	}
	if (negative)
	{
		*(str + i) = '-';
		++i;
	}
	
	*(str + i) = '\0';
	
	Reverse(str, i);

	return str;
}

int Atoi(const char *str, int base)
{
	int digit = 0;
	int result = 0;
	int sign = 1;
	char *runner = NULL;
	
	assert(NULL != str);
	
	runner = (char *)str;
	
	if ('-' == *runner)
	{
		sign = (-1);
		++runner;
	}
		
	while ('\0' != *runner)
	{
		digit = *runner - '0';
		result = result * base + digit;
		++runner;
	}
	
	return (sign * result);
}

void PrintLetters(char *arr1, char *arr2, char *arr3, size_t size1, size_t size2, size_t size3)
{
	int i = 0;
	int arr1_lut[ASCII] = {0};
	int arr2_lut[ASCII] = {0};
	int arr3_lut[ASCII] = {0};
	
	assert(NULL != arr1);
	assert(NULL != arr2);
	assert(NULL != arr3);

	InitArr(arr1, arr1_lut, size1);
	InitArr(arr2, arr2_lut, size2);
	InitArr(arr3, arr3_lut, size3);
	
	for (i = 0; i < ASCII; ++i)
	{
		if ((0 != arr1_lut[i]) && (0 != arr2_lut[i]) && 
			(0 == arr3_lut[i]))
		{
			printf("%c\n", (char)i);
		}
	}
}

int IsLittleEndian(void)
{
	unsigned int tmp = 1;
	char *ptr = (char *)&tmp;
	
	if (1 == *ptr)
	{
		return TRUE;
	}

	return FALSE;
}

/*************HelperFunctions**************/
void Reverse(char *str, size_t length)
{
	size_t start = 0;
	size_t end = length -1;
	
	assert(NULL != str);
	
	while (start < end)
	{
		Swap((str+start), (str+end));
		++start;
		--end;
	}
}

void Swap(char *x, char *y)
{
	int tmp = *x;
   *x = *y;
   *y = tmp;
}

void InitArr(char *arr, int *arr_lut, size_t arr_size)
{
	size_t i = 0;
	
	assert(NULL != arr);
	assert(NULL != arr_lut);
	
	for (i = 0; i < arr_size; ++i)
	{
		arr_lut[(int)arr[i]] = 1;
	}
}
