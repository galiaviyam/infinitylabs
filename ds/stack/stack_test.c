/********************************************************************/
/* DEVELOPER: Gali Aviyam                                           */
/* DATE MODIFIED: 29.11.2022                                        */
/* WORKSHEET NAME: stack                                            */
/* GDB, Valgrind tested                                             */
/* Reviewer: Eitan                                                  */
/********************************************************************/

#include <stdio.h> /*printf*/

#include "stack.h"
v
oid StackTest(void);

int main(void)
{
	StackTest();
	return 0;
}

void StackTest(void)
{
	int data1 = 68;
	float data2 = 55.59;
	char data3 = 'c';
	void *pop = NULL;
	void *peek = NULL;
	
	stack_t *stack = StackCreate(10);
	printf("Is the Stack Empty? %d\n", StackIsEmpty((const stack_t*) stack));	
	printf("\nThe Capacity of the stack is: %lu\n", 
			StackCapacity((const stack_t*) stack));
	
	printf("\n ....PUSH item in to stack....\n ");
	StackPush(stack, &data1);
	peek = StackPeek((const stack_t *)stack);
	printf("\nThe TOP item on the stack is: %d\n", *((int *)peek));
	
	printf("\n ....PUSH item in to stack....\n ");
	StackPush(stack, &data2);

	peek = StackPeek((const stack_t *)stack);
	printf("\nThe TOP item on the stack is: %.2f\n", *((float *)peek));
	
	printf("\nIs the Stack Empty? %d\n", StackIsEmpty((const stack_t*) stack));	
	
	StackPush(stack, &data3);
	printf("\nThe number of elements in the stack currently: %lu\n", 
			StackSize((const stack_t*)stack));
	
	pop = StackPop(stack);
	printf("\nPOP top item off the stack: %c\n ", *((char *)pop));
	StackDestroy(stack);
}
