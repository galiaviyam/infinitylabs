/*------------------------------------------------------------------*/
/* DEVELOPER: Gali Aviyam                                           */
/* DATE MODIFIED: 22.11.2022                                        */
/* WORKSHEET NAME: structs                                          */
/* GDB, Valgrind tested                                             */
/* Reviewer: Matan                                                  */
/*------------------------------------------------------------------*/

#include "structs.h"
#include <stdio.h>/*printf*/

#define SIZE 3
int ArrayTest(void);
void MacroTest(void);

int main(void)
{
	int status = ArrayTest();
	
	MacroTest();
	
	return status;
}

int ArrayTest(void)
{
	element_t arr[SIZE] = {0};
	
	int num = 3;
	
	IntInitStruct(&arr[0], 5);
	FloatInitStruct(&arr[1], 12.5);
	StrInitStruct(&arr[2], "gali");
	
	PrintArray(arr, SIZE);
	AddToArray(arr, SIZE, num);

	printf("**********after addition**********\n");
	PrintArray(arr, SIZE);
	
	CleanUpArray(arr, SIZE);
	
	return SUCCESS;
}

void MacroTest(void)
{
	int num = 5;
	float f_num = 6.7;
	double d_num = 4.5;
	char ch = 'g';
	
	printf("**********Macro Tests**********\n");
	printf("Max of (%d, %d) = %d\n", 5, 2, MAX2(5, 2));
	printf("Max of (%d, %d, %d) = %d\n\n", 1, 2, 3, MAX3(1, 2, 3));
	printf("Size of char variable: %lu\n", SIZEOF_VAR(ch));
	printf("Size of int variable: %lu\n", SIZEOF_VAR(num));
	printf("Size of float variable: %lu\n", SIZEOF_VAR(f_num));
	printf("Size of double variable: %lu\n\n", SIZEOF_VAR(d_num));	
	
	printf("Size of char: %lu\n", SIZEOF_TYPE(char));
	printf("Size of int: %lu\n", SIZEOF_TYPE(int));
	printf("Size of float: %lu\n", SIZEOF_TYPE(float));
	printf("Size of double: %lu\n", SIZEOF_TYPE(double));
}
