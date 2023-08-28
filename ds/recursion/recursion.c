/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Recursion				*/
/*   Date:		26/01/23				*/
/*	 Reviewer:	Noy Cohen				*/
/*										*/
/****************************************/

#include <string.h>		/* strncmp */
#include <assert.h>		/* assert */

#include "recursion.h"	/* recursion API */

int IterFibonacci(int element_index)
{
	int first = 0;
	int second = 1;
	int res = 1;

	assert(0 <= element_index);
	
	if (0 == element_index)
	{
		return 0;
	}
	
	while (--element_index)
	{
		res = first + second;
		first = second;
		second = res;
	}
	
	return res;
}

int RecFibonacci(int element_index)
{
	static int result_arr[200] = {0};
	
	assert(0 <= element_index);
	
	if (1 >= element_index)
	{
		return element_index;
	}
	
	if (0 != result_arr[element_index])
	{
		return result_arr[element_index];
	}

	result_arr[element_index] = RecFibonacci(element_index - 1) +
								 RecFibonacci(element_index - 2);
	return (result_arr[element_index]);
}

node_t *RecFlipList(node_t *node)
{
	node_t *new_head = NULL;
	
	assert(NULL != node);
	
	if (NULL == node->next)
	{
		return node;
	}
	
	new_head = RecFlipList(node->next);
	node->next->next = node;
	node->next = NULL;
	
	return new_head;
}

void RecStackSort(stack_t *stack)
{
	void *top = NULL;

	assert(NULL != stack);
	
	if (!StackIsEmpty(stack))
	{
		top = StackPop(stack);
		
		RecStackSort(stack);
		
		RecStackSortInsert(stack, top);
	}
}

void RecStackSortInsert(stack_t *stack, int *data)
{
	void *top = NULL;
	
	assert(NULL != stack);
	assert(NULL != data);

	if (StackIsEmpty(stack) || *data > *(int *)StackPeek(stack))
	{
		StackPush(stack, data);
		return;
	}
	
	top = StackPop(stack);
	RecStackSortInsert(stack, data);
	
	StackPush(stack, top);
}
 
size_t RecStrLen(const char *str)
{
	assert(NULL != str);
	
	if ('\0' == *str)
	{
		return 0;
	}
	
	return (1 + RecStrLen(str + 1));
}

int RecStrCmp(const char *str1, const char *str2)
{
	assert(NULL != str1);
	assert(NULL != str2);
	
/*	if (*str1 < *str2)*/
/*	{*/
/*		return -1;*/
/*	}*/
/*	if (*str1 > *str2)*/
/*	{*/
/*		return 1;*/
/*	}*/
	if ('\0' == *str1 || *str1 != *str2)
	{
		return (*str1 - *str2);
	}
	
	return (RecStrCmp((str1 + 1), (str2 + 1)));
}

char *RecStrCpy(char *dst, const char *src)
{
	assert(NULL != dst);
	assert(NULL != src);
	
	*dst = *src;
	
	if ('\0' == *src)
	{
		return dst;
	}
	
	return (RecStrCpy((dst + 1), (src + 1)) - 1);
}

char *RecStrCat(char *dst, const char *src)
{
	assert(NULL != dst);
	assert(NULL != src);
	
	if ('\0' == *dst)
	{
		return RecStrCpy(dst, src);
	}
	
	return (RecStrCat(dst + 1, src) - 1);
}

char *RecStrStr(const char *haystack, const char *needle)
{
	assert(NULL != haystack);
	assert(NULL != needle);
	
	if ('\0' == *haystack)
	{
		return NULL;
	}
	
	if (0 == strncmp(haystack, needle, RecStrLen(needle)))
	{
		return (char *)haystack;
	}
	
	return (RecStrStr((haystack + 1), needle));
}
