/*****************************************/
/*   Developer: Gali Aviyam              */
/*   Project: Circular Buffer 		     */				         
/*   Date: 13/12/22		            	 */
/*   Reviewer: Moriah	     			 */
/*****************************************/

#include <stdio.h> /*printf*/
#include <string.h> /*strncmp*/

#include "c_buff.h"/*header file*/

static void TestCreate(void);
static void TestCapacity(c_buff_t *buffer, size_t res);
static void TestFreeSpace(c_buff_t *buffer, size_t res);
static void TestIsEmpty(c_buff_t *buffer);
static void TestWrite(void);
static void TestRead(void);
static void IntegrationTest(void);
static void TestNumResultEqual(size_t result, size_t expected_result);
static void TestResultNotNull(void *result);
static void TestBoolResult(int result);

enum status
{
	SUCCESS = 0,
	FAIL
};

int main(void)
{
	TestCreate();
	printf("\n");
	TestWrite();
	TestRead();
	IntegrationTest();
	return 0;
}

static void TestCreate(void)
{
	c_buff_t *buffer = CbuffCreate(9);
	printf("create:\t\t");
	TestResultNotNull(buffer);
	TestIsEmpty(buffer);
	TestCapacity(buffer, 9);
	TestFreeSpace(buffer, 9);
	
	CbuffDestroy(buffer);
}


static void TestCapacity(c_buff_t *buffer, size_t res)
{
	size_t cap = CbuffCapacity(buffer);
	printf("capacity:\t");
	TestNumResultEqual(cap, res);
}

static void TestFreeSpace(c_buff_t *buffer, size_t res)
{
	size_t space = CbuffGetFreeSpace(buffer);
	printf("free space:\t");
	TestNumResultEqual(space, res);
}

static void TestIsEmpty(c_buff_t *buffer)
{
	size_t is_empty = CbuffIsEmpty(buffer);
	printf("IsEmpty:\t");
	TestBoolResult(is_empty);
}

static void TestWrite(void)
{
	c_buff_t *buffer = CbuffCreate(5);
	const char src[] ="Circular Buffer";
	
	printf("Test write to empty buffer:\t\t");
	TestNumResultEqual(CbuffWrite(buffer, src, 3), 3);
	
	printf("Test write to part-full buffer:\t\t");
	TestNumResultEqual(CbuffWrite(buffer, src, 2), 2);

	printf("Test fail to write to full buffer:\t");	
	TestNumResultEqual(CbuffWrite(buffer, src, 3), 0);

	
	CbuffDestroy(buffer);
}

static void TestRead(void)
{
	size_t cap = 10;
	ssize_t ret_val = 0;
	const char src[] = "Circular Buffer";
	char dest[50] = {0};
	c_buff_t *buffer = CbuffCreate(cap);
	
	
	printf("\n*****Test Read start without splitting*****\n");
	CbuffWrite(buffer, src, 3);
	ret_val = CbuffRead(buffer, dest, 3);
	TestNumResultEqual(ret_val, 3);
	TestNumResultEqual(strncmp(dest, src, 3), 0);
	
	printf("\n*****Test Read middle without splitting*****\n");
	CbuffWrite(buffer, src, 3);
	ret_val = CbuffRead(buffer, dest, 2);
	TestNumResultEqual(ret_val, 2);
	TestNumResultEqual(strncmp(dest, src, 2), 0);
	
	printf("\n*******Test Read split end and start*******\n");
	CbuffWrite(buffer, src, 6);
	ret_val = CbuffRead(buffer, dest, 7);
	TestNumResultEqual(ret_val, 7);
	TestNumResultEqual(strncmp(dest+1, src, 3), 0);
	TestNumResultEqual(strncmp(dest+4, src+3, 3), 0);
	
	CbuffDestroy(buffer);
}

static void IntegrationTest(void)
{
	c_buff_t *cbuffer = NULL;
	int test[64] = {0};
	int test_buffer[64] = {0};
	size_t i = 0;
	ssize_t written_bytes = 0;
	ssize_t read_bytes = 0;
	int status = SUCCESS;
	
	for (i = 0; i < 64; ++i)
	{
		*(test + i) = i * i;
	}
	
	cbuffer = CbuffCreate(256);

	written_bytes = CbuffWrite(cbuffer, test, 128);
	
	status += !(128 == (size_t)written_bytes);
	
	status += !(128 == CbuffGetFreeSpace(cbuffer));
	
	read_bytes = CbuffRead(cbuffer, test_buffer, 64);
	
	status += !(64 == (size_t)read_bytes);
								 
	status += !(192 == CbuffGetFreeSpace(cbuffer));
									   	 
	for (i = 0; i < 16; ++i)
	{
		status += !(*(test + i) == *(test_buffer + i));
	}
	
	read_bytes = CbuffRead(cbuffer, test_buffer, 80);
	
	status += !(64 == (size_t)read_bytes);
								 
	status += !(256 == CbuffGetFreeSpace(cbuffer));
									   	 
	written_bytes = CbuffWrite(cbuffer, test, 192);
	
	status += !(192 == (size_t)written_bytes);
	
	status += !(64 == CbuffGetFreeSpace(cbuffer));
	
	read_bytes = CbuffRead(cbuffer, test_buffer, 64);
	
	for (i = 0; i < 16; ++i)
	{
		status += !(*(test + i) == *(test_buffer + i));
	}
	
	read_bytes = CbuffRead(cbuffer, test_buffer + 16, 128);
	
	status += !(128 == (size_t)read_bytes);
								 
	for (i = 0; i < 48; ++i)
	{
		status += !(*(test + i) == *(test_buffer + i));
	}
	
	if (0 != status)
	{
		printf("Fail in %d tests\n", status);
	}
	else
	{
		printf("Pass all tests!\n");
	}
	
	CbuffDestroy(cbuffer);		
}

/*****************Test helper functions*******************/

static void TestBoolResult(int result)
{
	if (result)
	{
		printf("\033[0;32mPASSED\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAILED\033[0m\n");
	}
}

static void TestNumResultEqual(size_t result, size_t expected_result)
{
	if (result == expected_result)
	{
		printf("\033[0;32mPASSED\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAILED\033[0m\n");
	}
}

static void TestResultNotNull(void *result)
{
	if (NULL != result)
	{
		printf("\033[0;32mPASSED\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAILED\033[0m\n");
	}
}
