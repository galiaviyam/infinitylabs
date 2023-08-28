/********************************************************************/
/* DEVELOPER: Gali Aviyam                                           */
/* DATE MODIFIED: 29.11.2022                                        */
/* WORKSHEET NAME: stack                                            */
/* GDB, Valgrind tested                                             */
/* Reviewer: Eitan                                                  */
/********************************************************************/
#include <assert.h> /*assert*/
#include <stdlib.h> /*calloc*/

#include "stack.h"

#define EMPTY 0

struct stack
{
	void **stack_arr;
	size_t size;
	size_t capacity;
};

stack_t *StackCreate(size_t capacity)
{
	stack_t *stack = (stack_t *)malloc(sizeof(stack_t) + capacity);
	if (NULL == stack)
	{
		return NULL;
	}
	stack->stack_arr = (void *)calloc(capacity, sizeof(void *));
	if (NULL == stack->stack_arr)
	{
		free(stack);
		stack = NULL;
		return NULL;
	}
	stack->size = 0;
	stack->capacity = capacity;
	
	return stack;
}
	 
void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
	
	free(stack->stack_arr);
	stack->stack_arr = NULL;
	
	free(stack);	
	stack = NULL;
}

void StackPush(stack_t *stack, void *data)
{
	assert(NULL != stack);

	*(stack->stack_arr + stack->size) = data;
	++(stack->size);
}

void *StackPop(stack_t *stack)
{
	void *ptr = NULL;
	assert(NULL != stack);
	
	ptr = StackPeek(stack);
	
	stack->stack_arr[(stack->size)-1] = NULL;
	
	--(stack->size);
	
	return ptr;
}

void *StackPeek(const stack_t *stack)
{
	void *ptr = NULL;
	assert(NULL != stack);
	
	ptr = *(stack->stack_arr + (stack->size) - 1);
	
	return ptr;
}

size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);
	return stack->size;
}

size_t StackCapacity(const stack_t *stack)
{
	assert(NULL != stack);
	return stack->capacity;	
}

int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);
	return (EMPTY == stack->size);
}
