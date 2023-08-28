/*------------------------------------------------------------------*/
/* DEVELOPER: Gali Aviyam                                           */
/* DATE MODIFIED: 22.11.2022                                        */
/* WORKSHEET NAME: structs                                          */
/* GDB, Valgrind tested                                             */
/* Reviewer: Matan                                                  */
/*------------------------------------------------------------------*/

#include <stdio.h>/*printf, size_t*/
#include <string.h> /*strlen*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc, free*/

#include "structs.h" /*header file*/

#define SIZE 3
#define ERROR -1
#define NULL_TERM_LEN 1

typedef struct element
{
	void *data;
	add_func_t add_f_p;		
	print_func_t print_f_p;
	cleanup_func_t cleanup_f_p;
};

enum EXIT_STATUS
{
	ERROR = -1,
	SUCCESS,
	FAIL
};

int IntInitStruct(element_t *elem, int value)
{
	assert(NULL != elem);
	*((int *)(&(elem->data))) = value;
	elem->add_f_p = &AddToInt;
	elem->print_f_p = &PrintInt;
	elem->cleanup_f_p = &DoNothing;

	return 0;
}

int FloatInitStruct(element_t *elem, float value)
{
	assert(NULL != elem);
	*((float *)(&(elem->data))) = value;
	elem->add_f_p = &AddToFloat;
	elem->print_f_p = &PrintFloat;
	elem->cleanup_f_p = &DoNothing;
	
	return 0;
}

int StrInitStruct(element_t *elem, char *str)
{
	assert(NULL != elem);
	assert(NULL != str);

	*((char **)(&(elem->data))) = malloc((strlen(str)+1) * sizeof(char));;
	if (NULL == str)
	{
		return ERROR;
	}
	strcpy(*((char **)(&(elem->data))), str);
	elem->add_f_p = &AddToStr;
	elem->print_f_p = &PrintStr;
	elem->cleanup_f_p = &CleanUpStr;
	
	return 0;
}

void PrintArray(element_t *arr, size_t size)
{
	size_t i = 0;
	element_t *copy = NULL;
	assert(NULL != arr);
	
	copy = arr;
	for (i = 0; i < size; ++i)
	{
		copy->print_f_p((const void*)copy->data);
		++copy;
	}
}

int AddToArray(element_t *arr, size_t size, int num)
{
	int exit_status = 0;
	size_t i = 0;
	element_t *copy = NULL;
	assert(NULL != arr);
	
	copy = arr;
	for (i = 0; i < size; ++i)
	{
		exit_status = copy->add_f_p(&(copy->data), num);
		++copy;
	}
	return exit_status;
}

void CleanUpArray(element_t *arr, size_t size)
{
	size_t i = 0;
	element_t *copy = NULL;
	assert(NULL != arr);
	
	copy = arr;
	for (i = 0; i < size; ++i)
	{
		copy->cleanup_f_p((void**)copy->data);
		++copy;
	}
}

int AddToInt(void **data, int num)
{	
	assert(NULL != data);
	**((int **)&data) += num;
		
	return SUCCESS;
}

int AddToFloat(void **data, int num)
{
	assert(NULL != data);
	**((float **)&data) += num;
		
	return SUCCESS;
}

int AddToStr(void **data, int num)
{
	size_t data_len = 0;
	size_t int_len = 0;
	size_t new_len = 0;
	char *tmp = NULL;
	
	assert(NULL != data);

	data_len = strlen(*(char **)data) + NULL_TERM_LEN;
	int_len = IntLen(num) + NULL_TERM_LEN;
	new_len = data_len + int_len;
	
	tmp = (char*)malloc(new_len * sizeof(char));
	if (NULL == tmp)
	{
		return ERROR;
	}
	
	strcpy(tmp, *((char **)data));

	*(char **)data = realloc(*(char **)data, new_len * sizeof(char));
	if (NULL == (char **)data)
	{
		return ERROR;
	}
	
	sprintf(*((char **)data), "%s%d", tmp, num);
	
	free(tmp);
	tmp = NULL;
	
	return SUCCESS;
}

size_t IntLen(int num)
{
	size_t count = 0;
	
	while (num != 0)
	{
		num /= 10;
		++count;
	}
	return count;
}

void PrintInt(const void *data)
{
	printf("element is %d\n", *((int *)(&data)));
}

void PrintFloat(const void *data)
{
	printf("element is %.2f\n", *((float *)(&data)));
}

void PrintStr(const void *data)
{
	printf("element is %s\n", (char *)(data));
}

void DoNothing(void **data)
{
	(void)data;
}

void CleanUpStr(void **data)
{
	free(*((char **)&data));
	*((char **)&data) = NULL;
}
