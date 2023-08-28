/*------------------------------------------------------------------*/
/* DEVELOPER: Gali Aviyam                                           */
/* DATE MODIFIED: 22.11.2022                                        */
/* WORKSHEET NAME: structs                                          */
/* GDB, Valgrind tested                                             */
/* Reviewer: Matan                                                  */
/*------------------------------------------------------------------*/

#include <stdio.h> /*size_t*/

#define MAX2(a, b) (((a) > (b)) ? (a) : (b))
#define MAX3(a, b, c) (((a) > (c)) ? MAX2((a), (b)): MAX2(c, b))

#define SIZEOF_VAR(var) ((size_t)(&(var)+1)-(size_t)(&(var))) 
#define SIZEOF_TYPE(type) ((size_t)(1 + ((type *)0)))

typedef int(*add_func_t)(void **data, int num);

typedef void(*print_func_t)(const void *data);

typedef void(*cleanup_func_t)(void **data);

typedef struct element element_t;
	
int IntInitStruct(element_t *elem, int value);

int AddToInt(void **data, int num);

void PrintInt(const void *data);

void DoNothing(void **data);

int FloatInitStruct(element_t *elem, float value);

int AddToFloat(void **data, int num);

void PrintFloat(const void *data);

int StrInitStruct(element_t *elem, char *str);

int AddToStr(void **data, int num);

size_t IntLen(int num);

void PrintStr(const void *data);

void CleanUpStr(void **data);

void PrintArray(element_t *arr, size_t size);

int AddToArray(element_t *arr, size_t size, int num);

void CleanUpArray(element_t *arr, size_t size);

