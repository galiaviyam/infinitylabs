/*------------------------------------------------------------------*/
/* DEVELOPER: Gali Aviyam                                           */
/* DATE MODIFIED: 17.11.2022                                        */
/* WORKSHEET NAME: files                                            */
/* GDB, Valgrind tested                                                  */
/* Reviewer: Vladimir                                               */
/*------------------------------------------------------------------*/
   
#include <stdio.h> /*printf*/
typedef void (*function)(int);

typedef struct print_me
{
	int num;
	function Print;
}print_me;

void InitArray(print_me *arr, size_t size);
void PrintArray(print_me *arr, size_t size);

void Print(int num);

int main()
{

	print_me arr[10];
	
	InitArray(arr, 10);
	PrintArray(arr, 10);
	
	return 0;
}

void InitArray(print_me *arr, size_t size)
{
	size_t i = 0;

	for (i = 0; i < size; ++i)
	{
		(arr + i)->num = 5 * i;
		(arr + i)->Print = Print;

	}
}

void PrintArray(print_me *arr, size_t size)
{
	size_t i = 0;

	for (i = 0; i < size; ++i)
	{
		(arr + i)->Print((arr + i)->num);
	}
}

void Print(int num)
{
	printf("%d\n", num);
}
