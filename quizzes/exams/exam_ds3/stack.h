/********************************************************************/
/* DEVELOPER: Gali Aviyam                                           */
/* DATE MODIFIED: 29.11.2022                                        */
/* WORKSHEET NAME: stack                                            */
/* GDB, Valgrind tested                                             */
/* Reviewer: Eitan                                                  */
/********************************************************************/


#ifndef STACK_H_
#define STACK_H_

#include <stddef.h>	/*size_t*/

/************************struct*****************************/
typedef struct stack stack_t;


/******************Function Declarations********************/

/*-----------------------------------------------------------------------------
   Description 
   The StackCreate() function receives the capacity of the stack to be allocated,
   and creates a stack type with it.
   Note! The capacity size that is sent to the function,
   has to be bigger than zero for a defined behavior of the function!
   Note! when using StackCreate() it is mandatory to be using StackDestroy() to
   free the memory.
   
   Return Value
   The function returns a pointer to  the allocated initialized stack with the
   size of the capacity. If the allocation fails, the return value is NULL.
   time: o(1) / space: o(n)
-----------------------------------------------------------------------------*/
stack_t *StackCreate(size_t capacity);
	 
/*-----------------------------------------------------------------------------
   Description 
   The StackDestroy() function recieves a stack to be free, and frees all
   allocated memory in stack.
	
   Return Value
   The function returns nothing, it cant fail.
   time: o(1) / space: o(1)
-----------------------------------------------------------------------------*/
void StackDestroy(stack_t *stack);

/*-----------------------------------------------------------------------------
   Description 
   The StackPush() function inserts the argument data into the received stack
   argument.
	
   Return Value
   The function returns nothing.
   If the passed arguments are NULL- This will cause the program an undefined
   behavior.
   time: o(1) / space: o(1)
-----------------------------------------------------------------------------*/	 
void StackPush(stack_t *stack, void *data);

/*-----------------------------------------------------------------------------
   Description 
   The StackPop() function removes the top element of the received stack argument.
	
   Return Value
   The function returns nothing.
   If the passed argument is NULL- This will cause the program an undefined
   behavior.
   time: o(1) / space: o(1)
-----------------------------------------------------------------------------*/	 
void *StackPop(stack_t *stack);	

/*-----------------------------------------------------------------------------
   Description 
   The StackPeek() function shows the top element of the received stack argument.
   If the passed argument is NULL- This will cause the program an undefined
   behavior.
   
   Return Value
   The function returns the value of the top element of the received argument 
   stack.
   time: o(1) / space: o(1)
-----------------------------------------------------------------------------*/
void *StackPeek(const stack_t *stack);	

/*-----------------------------------------------------------------------------
   Description 
   The StackSize() function shows the amount of occupied elements in the stack.
   If the passed argument is NULL- This will cause the program an undefined
   behavior.
	
   Return Value
   The function returns the amount of occupied elements in the stack.
   time: o(1) / space: o(1)
-----------------------------------------------------------------------------*/
size_t StackSize(const stack_t *stack);	

/*-----------------------------------------------------------------------------
   Description 
   The StackCapacity() function shows the max capacity of the received stack
   argument.
   If the passed argument is NULL- This will cause the program an undefined
   behavior.
	
   Return Value
   The function returns the max capacity of the stack.
   time: o(1) / space: o(1)
-----------------------------------------------------------------------------*/	 	
size_t StackCapacity(const stack_t *stack);

/*-----------------------------------------------------------------------------
   Description 
   The StackIsEmpty() function checks whether the received stack argument is
   empty- with not even one element inside. 
   If the passed argument is NULL- This will cause the program an undefined
   behavior.
	
   Return Value
   The function returns TRUE(=1) if the received stack argument is empty,
   and FALSE(=0) if not.
   time: o(1) / space: o(1)
-----------------------------------------------------------------------------*/
int StackIsEmpty(const stack_t *stack);		

#endif
