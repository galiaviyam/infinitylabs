/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Recursion				*/
/*   Date:		26/01/23				*/
/*	 Reviewer:	Noy Cohen				*/
/*										*/
/****************************************/

#include <stdio.h>		/* printf */
#include <string.h>		/* strcmp */
#include "recursion.h"	/* recursion API */

static void TestStatusResult(int result);
static void TestNumResultEqual(size_t result, size_t expected_result);
static void TestNumGreaterThan(size_t result, size_t small_value);

void TestIterFibonacci(void);
void TestRecFibonacci(void);
void TestRecFlipList(void);
void TestRecStackSort(void);
void TestRecStrLen(void);
void TestRecStrCmp(void);
void TestRecStrCpy(void);
void TestRecStrCat(void);
void TestRecStrStr(void);

typedef enum status
{
	SUCCESS = 0,
	FAIL
} status_t;

int main(void)
{
	TestIterFibonacci();
	TestRecFibonacci();
	TestRecFlipList();
	TestRecStackSort();
	TestRecStrLen();
	TestRecStrCmp();
	TestRecStrCpy();
	TestRecStrCat();
	TestRecStrStr();
	
	return 0;
}


void TestIterFibonacci(void)
{
	printf("------IterFibonacci------\n");

	TestNumResultEqual(0, IterFibonacci(0));	
	TestNumResultEqual(3, IterFibonacci(4));
	TestNumResultEqual(5, IterFibonacci(5));
	TestNumResultEqual(8, IterFibonacci(6));
}

void TestRecFibonacci(void)
{
	printf("-------RecFibonacci-------\n");
	
	TestNumResultEqual(0, RecFibonacci(0));
	TestNumResultEqual(3, RecFibonacci(4));
	TestNumResultEqual(5, RecFibonacci(5));
	TestNumResultEqual(8, RecFibonacci(6));
}

void TestRecFlipList(void)
{
	int status = FAIL;	
	
	node_t node1 = {(void *)1, NULL};
    node_t node2 = {(void *)2, NULL};
    node_t node3 = {(void *)3, NULL};
    node_t node4 = {(void *)4, NULL};

	
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = NULL;
	
	if (&node4 == RecFlipList(&node1))
	{
		status = SUCCESS;
	}
	
	printf("--------RecFlipList--------\n");	
	TestStatusResult(status);
}

void TestRecStackSort(void)
{
	status_t status = SUCCESS;
	size_t i = 0;
	
	int data1 = 68;
	int data2 = 55;
	int data3 = 30;
	int data4 = 21;
	int data5 = 15;
	
	void *top = NULL;
	
	stack_t *stack = StackCreate(5);
	
	StackPush(stack, &data3);
	StackPush(stack, &data2);
	StackPush(stack, &data5);
	StackPush(stack, &data1);
	StackPush(stack, &data4);

	printf("--------RecStackSort--------\n");	

	RecStackSort(stack);
	
	for (i = 0; i < 5; ++i)
	{
		top = StackPeek(stack);
		if (*(int *)top > *(int *)StackPop(stack))
		{
			status = FAIL;
		}
	}
	
	TestStatusResult(status);
	
	StackDestroy(stack);
}

void TestRecStrLen(void)
{
	const char str1[20] = "Hello World!";
	const char str2[20] = "Hello";
	
	printf("--------RecStrLen--------\n");	
	
	TestNumResultEqual(RecStrLen(str1), strlen(str1));

	TestNumResultEqual(RecStrLen(str2), strlen(str2));
}

void TestRecStrCmp(void)
{
	const char str1[15] = "Hello World!";
	const char str2[15] = "Hello";
	const char str3[15] = "hell";

	printf("--------RecStrCmp--------\n");	
	
	TestNumGreaterThan(RecStrCmp(str1, str2), 0);

	TestNumGreaterThan(RecStrCmp(str2, str3), 0);

	TestNumResultEqual(RecStrCmp(str2, str2), 0);
}

void TestRecStrCpy(void)
{
	char str1[20] = "recursion is cool";
	char str2[20] = {0};

	printf("--------RecStrCpy--------\n");	
	
	RecStrCpy(str2, str1);
	TestStatusResult(strcmp(str2, str1));	
}

void TestRecStrCat(void)
{
	char dest[20] = "Happy ";
	char src[10] = "Birthday!";
	
	printf("--------RecStrCat--------\n");	

	RecStrCat(dest, src);
	
	TestStatusResult(strcmp(dest, "Happy Birthday!"));
}

void TestRecStrStr(void)
{
	const char haystack[20] = "supernova123";
	const char needle[10] = "nova";
	const char str1[20] = "blabla dancey";
	const char str2[10] = "dance";

	printf("--------RecStrStr--------\n");	
	
	TestStatusResult(strcmp(RecStrStr(haystack, needle), strstr(haystack, needle)));

	TestStatusResult(strcmp(RecStrStr(str1, str2), strstr(str1, str2)));
}




static void TestNumResultEqual(size_t result, size_t expected_result)
{
	if (result == expected_result)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}

static void TestStatusResult(int result)
{
	if (result == SUCCESS)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}

static void TestNumGreaterThan(size_t result, size_t small_value)
{
	if (result > small_value)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}
