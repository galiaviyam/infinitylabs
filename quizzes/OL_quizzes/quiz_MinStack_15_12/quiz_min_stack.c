#include <stdio.h>	/* printf */
#include <assert.h> /* assert */

#include "stack.h" /* header file */

typedef struct mstack
{
	stack_t *stack;
	stack_t *min_stack;
} mstack_t;

static void MinStackPush(mstack_t *mstack, int *data)
{
	assert(NULL != mstack);
	assert(NULL != data);
	
	StackPush(mstack->stack, data);
	
	if (StackIsEmpty(mstack->min_stack) || *data < *(int *)StackPeek(mstack->min_stack))
	{
		StackPush(mstack->min_stack, data);
	}
}

static void *MinStackPop(mstack_t *mstack)
{
	assert(NULL != mstack);
	
	if (StackPeek(mstack->stack) == StackPeek(mstack->min_stack)) 
	{
		StackPop(mstack->min_stack);
	}
	
	return (StackPop(mstack->stack));
}


int main (void)
{
	mstack_t test_stack = {0};
	size_t capacity = 10;
	int test_buffer[10] = {1, 6, -4, 4, 6 -8, 9, 4, 3, 0};
	size_t i = 0;
	
	test_stack.stack = StackCreate(capacity);
	test_stack.min_stack = StackCreate(capacity);
	
	for (i = 0; i < capacity; ++i)
	{
		MinStackPush(&test_stack, &test_buffer[i]);
	}
	
	for (i = 0; i < capacity/2; ++i)
	{
		MinStackPop(&test_stack);
	}
	
	(*(int *)StackPeek(test_stack.min_stack) == -4) ? printf("SUCCESS\n"): 
													  printf("FAIL\n");
	
	StackDestroy(test_stack.stack); 
	StackDestroy(test_stack.min_stack);
	
	return 0;
}
