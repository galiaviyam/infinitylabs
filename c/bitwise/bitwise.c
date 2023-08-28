/*------------------------------------------------------------------*/
/* DEVELOPER: Gali Aviyam                                           */
/* DATE MODIFIED: 17.11.2022                                        */
/* WORKSHEET NAME: Bitwise                                          */
/* GDB, Valgrind tested                                             */
/* Reviewer: Vladimir                                               */
/*------------------------------------------------------------------*/

#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/

#define BYTE_SIZE 8

long Pow2(unsigned int x, unsigned int y);
int IsPowerOf2(unsigned int n);
int IsPowerOf2Loop(unsigned int n);
int AddOne(int n);
void Print3BitsOn(int *arr, size_t size);
unsigned char ByteMirror(unsigned char num);
void PrintBin(char value);
int Check2And6(unsigned char c);
int Check2Or6(unsigned char c);
int Swap3And5(unsigned char c);
unsigned int ClosestDivBy16(unsigned int x);
void Swap(int *x, int *y);
size_t CountSetBits(int n);
void PrintFloatBits(float *num);

int main()
{
	int arr[7] = {1, 7, 8, 11, 88, 100, 101};
	unsigned int x = 2;
	int a = 8;
	int b = 5;
	
	float num1 = 12;
	float num2 = 11.99;
	float num3 = 1;
	float num4 = 1.1;
	float num5 = 99.99;
	
	printf("\n1 ***************Pow2****************\n");
	printf("7*(2^3) = %ld\n", Pow2(7, 3));
	
	printf("\n2 ************IsPowerOf2*************\n");
	printf("8: %d\n", IsPowerOf2(8));
	printf("5: %d\n", IsPowerOf2(5));

	printf("\n2 **********IsPowerOf2Loop***********\n");
	printf("8: %d\n", IsPowerOf2Loop(8));
	printf("5: %d\n", IsPowerOf2Loop(5));
	
	printf("\n3 **************AddOne***************\n");
	printf("8 + 1 = %d\n", AddOne(8));
	printf("5 + 1 = %d\n", AddOne(5));

	printf("\n4 ***********Print3BitsOn************\n");
	printf("numbers in array which have exactly 3 bits on:\n");
	Print3BitsOn(arr, 7);
	
	printf("\n5 ************ByteMirror*************\n");
	printf("before: ");
	PrintBin(x);
	printf("\nafter:  ");
	PrintBin(ByteMirror(x));
	printf("\n");
	
	printf("\n6 ************Check2And6************\n");
	printf("%d: %d\n", 34, Check2And6(34));
	printf("%d: %d\n", 20, Check2And6(20));
	
	printf("\n6 ************Check2Or6*************\n");
	printf("%d: %d\n", 34, Check2Or6(34));
	printf("%d: %d\n", 20, Check2Or6(20));
	printf("%d: %d\n", 50, Check2Or6(50));
		
	printf("\n6 ************Swap3And5*************\n");
	printf("before: ");
	PrintBin((char)164);
	printf("\nafter:  ");
	PrintBin(Swap3And5(164));
	printf("\n");
	
	printf("\n7 **********ClosestDivBy16***********\n");
	printf("number is: %d\nclosest number divisable by 16 is: %d\n\n", 33,
	ClosestDivBy16(33));
	printf("number is: %d\nclosest number divisable by 16 is: %d\n\n", 17,
	ClosestDivBy16(17));
	printf("number is: %d\nclosest number divisable by 16 is: %d\n\n", 22,
	ClosestDivBy16(22));
	
	printf("\n8 ***************Swap****************\n");
	printf("before: a = %d, b = %d\n", a, b);
	Swap(&a, &b);
	printf("\nafter: a = %d, b = %d\n", a, b);
	
	printf("\n9 **********CountSetBits**********\n");
	printf("8: %lu\n", CountSetBits(8));
	printf("5: %lu\n", CountSetBits(5));
	printf("85: %lu\n", CountSetBits(85));
	
	printf("\n10 **********PrintFloatBits**********\n");
	PrintFloatBits(&num1);
	PrintFloatBits(&num2);
	PrintFloatBits(&num3);
	PrintFloatBits(&num4);
	PrintFloatBits(&num5);
	
	return 0;
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

long Pow2(unsigned int x, unsigned int y)
{
	return x << y;
}

int IsPowerOf2(unsigned int n)
{
	if (0 != (n & (n - 1)))
	{
		return 0;
	}
	return 1;
}

int IsPowerOf2Loop(unsigned int n)
{
	int n_copy = n;
	int count = 0;
	
	while (0 != n_copy)
	{
		if (1 & n_copy)
		{
			++count;
		}
		n_copy = n_copy >> 1;
	}
	
	if (1 == count)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int AddOne(int n)
{
	int m = 1;

	while(n & m)
    {
		n = n ^ m;
		m = m << 1;
	}
	
	n = n ^ m;

	return n;
}

void Print3BitsOn(int *arr, size_t size)
{
	size_t i = 0;
	int copy = 0;
	int count = 0;
	
	assert(NULL != arr);
	
	for (i = 0; i < size; ++i)
	{
		count = 0;
		copy = *(arr + i);
	
		while (0 != copy)
		{
			if (1 & copy)
			{
				++count;
			}
			copy = copy >> 1;
		}
		
		if (3 == count)
		{
			printf("%d\n", *(arr + i));
		}
	}
}

unsigned char ByteMirror(unsigned char num)
{
	char result = 0;
	
	while (num > 0)
	{
		result = result << 1;
		result = result | (num & 1);
		num = num >> 1;
	}

	return result;
}

int Check2And6(unsigned char c)
{
	return ((c >> 1) & 1 && (c >> 5) & 1);
}

int Check2Or6(unsigned char c)
{
	return ((c >> 1) & 1 || (c >> 5) & 1);
}

int Swap3And5(unsigned char c)
{
	unsigned char bit_three = 0;
	unsigned char bit_five = 0;
	unsigned char swap_bits = 0;
	
	bit_three = (c >> 2) & 1;
	bit_five = (c >> 4) & 1;	
	swap_bits = bit_three ^ bit_five;
	swap_bits = (swap_bits << 2) | (swap_bits << 4);
	
	return (c ^ swap_bits);
}

unsigned int ClosestDivBy16(unsigned int x)
{
	while (x != (x >> 4) << 4)
	{
		--x;
	}
	return x;
}

void Swap(int *x, int *y)
{
	*x = *x ^ *y ;
	*y = *x ^ *y ;
	*x = *x ^ *y ;
}

size_t CountSetBits(int n)
{
	int n_copy = n;
	size_t count = 0;
	
	while (0 != n_copy)
	{
		if (1 & n_copy)
		{
			++count;
		}
		n_copy = n_copy >> 1;
	}
	
	return count;
}

void PrintFloatBits(float *num)
{
	int *num_p = NULL;
	
	num_p = (int*) &num;

	PrintBin(*num_p);
}
