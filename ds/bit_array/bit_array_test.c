#include <stdio.h>

#include "bit_array.h"

#define STR_LEN 65

typedef enum
{
	SUCCESS = 0,
	FAIL

} status_t;

static status_t BitArrSetOnTest(void);
static status_t BitArrSetOffTest(void);
static status_t BitArrFlipBitTest(void);
static status_t BitArrGetValTest(void);
static status_t BitArrSetValTest(void);
static status_t BitArrFlipAllTest(void);
static status_t BitArrSetAllTest(void);
static status_t BitArrUnsetAllTest(void);
static status_t BitArrRotateLeftTest(void);
static status_t BitArrRotateRightTest(void);
static status_t BitArrCountSetBitsTest(void);
static status_t BitArrCountSetBitsLutTest(void);
static status_t BitArrCountOffBitsTest(void);
static status_t BitArrMirrorTest(void);
static status_t BitArrMirrorLutTest(void);
static status_t BitArrMirrorO1Test(void);
static void BitArrToStringTest(void);
static void BitArrayTests(void);

int main()
{
	BitArrayTests();
	
	return 0;
}

static void BitArrayTests(void)
{
	status_t stat = SUCCESS;
	
	stat += BitArrSetOnTest();
	stat += BitArrSetOffTest();
	stat += BitArrFlipBitTest();
	stat += BitArrGetValTest();
	stat += BitArrSetValTest();
	stat += BitArrFlipAllTest();
	stat += BitArrSetAllTest();
	stat += BitArrUnsetAllTest();
	stat += BitArrRotateLeftTest();
	stat += BitArrRotateRightTest();
	stat += BitArrCountSetBitsTest();
	stat += BitArrCountSetBitsLutTest();
	stat += BitArrCountOffBitsTest();
	stat += BitArrMirrorTest();
	stat += BitArrMirrorLutTest();
	stat += BitArrMirrorO1Test();

	BitArrToStringTest();
	
		
	if (0 == stat)
	{
		printf("Passed all tests!\n\n");
	}
	else
	{
		printf("Failed\n\n");
	}
}


static status_t BitArrSetOnTest(void)
{
 	const int tests = 3;
 	status_t stat = SUCCESS;
 	int i = 0;
 	size_t bitarr = 0;
	size_t index[] = {0, 1, 32};
	size_t res[] = {1, 3, 4294967299};
	
	printf("BitArrSetOn:\n\n");
	
	for (i = 0; i < tests; ++i)
	{
		printf("test %d:", i + 1);
		
		bitarr = BitArrSetOn(bitarr, index[i]);
		
		if (bitarr == res[i])
		{
			printf("\tPassed\n");
		}
		else
		{
			stat = FAIL;
			printf("\tFailed\n");
		}
	}
	
	printf("\n\n");
	
	return stat;
}
 
static status_t BitArrSetOffTest(void)
{
	const int tests = 3;
	status_t stat = SUCCESS;
	int i = 0;
	size_t bitarr[] = {4294967299, 3, 1};
	size_t index[] = {32, 1, 0};
	size_t res[] = {3, 1, 0};
	
	printf("BitArrSetOff:\n\n");
	
	for (i = 0; i < tests; ++i)
	{
		printf("test %d:", i + 1);
		
		if (BitArrSetOff(bitarr[i], index[i]) == res[i])
		{
			printf("\tPassed\n");
		}
		else
		{
			stat = FAIL;
			printf("\tFailed\n");
		}
	}
	
	printf("\n\n");
	
	return stat;
}

static status_t BitArrFlipBitTest(void)
{
	const int tests = 3;
	status_t stat = SUCCESS;
	int i = 0;
	size_t bitarr[] = {0, 1, 4294967299};
	size_t index[] = {0, 0, 32};
	size_t res[] = {1, 0, 3};
	
	printf("BitArrFlipBit:\n\n");
	
	for (i = 0; i < tests; ++i)
	{
		printf("test %d:", i + 1);
		
		if (BitArrFlipBit(bitarr[i], index[i]) == res[i])
		{
			printf("\tPassed\n");
		}
		else
		{
			stat = FAIL;
			printf("\tFailed\n");
		}
	}
	
	printf("\n\n");
	
	return stat;
}

static status_t BitArrGetValTest(void)
{
	const int tests = 4;
	status_t stat = SUCCESS;
	int i = 0;
	size_t bitarr[] = {0, 1, 4294967299, 4294967299};
	size_t index[] = {0, 0, 32, 30};
	int res[] = {0, 1, 1, 0};
	
	printf("BitArrGetVal:\n\n");
	
	for (i = 0; i < tests; ++i)
	{
		printf("test %d:", i + 1);
		
		if (BitArrGetVal(bitarr[i], index[i]) == res[i])
		{
			printf("\tPassed\n");
		}
		else
		{
			stat = FAIL;
			printf("\tFailed\n");
		}
	}
	
	printf("\n\n");
	
	return stat;
}

static status_t BitArrSetValTest(void)
{
	const int tests = 4;
	status_t stat = SUCCESS;
	int i = 0;
	size_t bitarr[] = {0, 4294967299, 1, 4294967299};
	size_t index[] = {0, 32, 0, 30};
	bit_val_t value[] = {bit_on, bit_on, bit_off, bit_off};
	size_t res[] = {1, 4294967299, 0, 4294967299};
	
	printf("BitArrSetVal:\n\n");
	
	for (i = 0; i < tests; ++i)
	{
		printf("test %d:", i + 1);
		
		if (BitArrSetVal(bitarr[i], index[i], value[i]) == res[i])
		{
			printf("\tPassed\n");
		}
		else
		{
			stat = FAIL;
			printf("\tFailed\n");
		}
	}
	
	printf("\n\n");
	
	return stat;
}

static status_t BitArrFlipAllTest(void)
{
	const int tests = 2;
	status_t stat = SUCCESS;
	int i = 0;
	size_t bitarr[] = {0, -1};
	size_t res[] = {-1, 0};
	
	printf("BitArrFlipAll:\n\n");
	
	for (i = 0; i < tests; ++i)
	{
		printf("test %d:", i + 1);
		
		if (BitArrFlipAll(bitarr[i]) == res[i])
		{
			printf("\tPassed\n");
		}
		else
		{
			stat = FAIL;
			printf("\tFailed\n");
		}
	}
	
	printf("\n\n");
	
	return stat;
}

static status_t BitArrSetAllTest(void)
{
	const int tests = 5;
	status_t stat = SUCCESS;
	int i = 0;
	size_t bitarr[] = {0, -1, 324, 9075896, 24398};
	size_t res = -1;
	
	printf("BitArrSetAll:\n\n");
	
	for (i = 0; i < tests; ++i)
	{
		printf("test %d:", i + 1);
		
		if (BitArrSetAll(bitarr[i]) == res)
		{
			printf("\tPassed\n");
		}
		else
		{
			stat = FAIL;
			printf("\tFailed\n");
		}
	}
	
	printf("\n\n");
	
	return stat;
}

static status_t BitArrUnsetAllTest(void)
{
	const int tests = 5;
	status_t stat = SUCCESS;
	int i = 0;
	size_t bitarr[] = {0, -1, 324, 9075896, 24398};
	size_t res = 0;
	
	printf("BitArrUnsetAll:\n\n");
	
	for (i = 0; i < tests; ++i)
	{
		printf("test %d:", i + 1);
		
		if (BitArrUnsetAll(bitarr[i]) == res)
		{
			printf("\tPassed\n");
		}
		else
		{
			stat = FAIL;
			printf("\tFailed\n");
		}
	}
	
	printf("\n\n");
	
	return stat;
}

static status_t BitArrRotateLeftTest(void)
{
	const int tests = 4;
	status_t stat = SUCCESS;
	int i = 0;
	size_t bitarr[] = {0, -1, 5, 5};
	size_t n[] = {0, 34, 1, 3};
	size_t res[] = {0, -1, 10, 40};
	
	printf("BitArrRotateLeft:\n\n");
	
	for (i = 0; i < tests; ++i)
	{
		printf("test %d:", i + 1);
		
		if (BitArrRotateLeft(bitarr[i], n[i]) == res[i])
		{
			printf("\tPassed\n");
		}
		else
		{
			stat = FAIL;
			printf("\tFailed\n");
		}
	}
	
	printf("\n\n");
	
	return stat;
}

static status_t BitArrRotateRightTest(void)
{
	const int tests = 4;
	status_t stat = SUCCESS;
	int i = 0;
	size_t bitarr[] = {0, -1, 10, 40};
	size_t n[] = {0, 34, 1, 3};
	size_t res[] = {0, -1, 5, 5};
	
	printf("BitArrRotateRight:\n\n");
	
	for (i = 0; i < tests; ++i)
	{
		printf("test %d:", i + 1);
		
		if (BitArrRotateRight(bitarr[i], n[i]) == res[i])
		{
			printf("\tPassed\n");
		}
		else
		{
			stat = FAIL;
			printf("\tFailed\n");
		}
	}
	
	printf("\n\n");
	
	return stat;
}

static status_t BitArrCountSetBitsTest(void)
{
	const int tests = 4;
	status_t stat = SUCCESS;
	int i = 0;
	size_t bitarr[] = {0, -1, 10, 40};
	size_t res[] = {0, 64, 2, 2};
	
	printf("BitArrCountSetBits:\n\n");
	
	for (i = 0; i < tests; ++i)
	{
		printf("test %d:", i + 1);
		
		if (BitArrCountSetBits(bitarr[i]) == res[i])
		{
			printf("\tPassed\n");
		}
		else
		{
			stat = FAIL;
			printf("\tFailed\n");
		}
	}
	
	printf("\n\n");
	
	return stat;
}

static status_t BitArrCountSetBitsLutTest(void)
{
	const int tests = 4;
	status_t stat = SUCCESS;
	int i = 0;
	size_t bitarr[] = {0, -1, 10, 40};
	size_t res[] = {0, 64, 2, 2};
	
	printf("BitArrCountSetBitsLut:\n\n");
	
	for (i = 0; i < tests; ++i)
	{
		printf("test %d:", i + 1);
		
		if (BitArrCountSetBitsLut(bitarr[i]) == res[i])
		{
			printf("\tPassed\n");
		}
		else
		{
			stat = FAIL;
			printf("\tFailed\n");
		}
	}
	
	printf("\n\n");
	
	return stat;
}

static status_t BitArrCountOffBitsTest(void)
{
	const int tests = 4;
	status_t stat = SUCCESS;
	int i = 0;
	size_t bitarr[] = {0, -1, 10, 40};
	size_t res[] = {64, 0, 62, 62};
	
	printf("BitArrCountOffBits:\n\n");
	
	for (i = 0; i < tests; ++i)
	{
		printf("test %d:", i + 1);
		
		if (BitArrCountOffBits(bitarr[i]) == res[i])
		{
			printf("\tPassed\n");
		}
		else
		{
			stat = FAIL;
			printf("\tFailed\n");
		}
	}
	
	printf("\n\n");
	
	return stat;
}



static void BitArrToStringTest(void)
{	
	const int tests = 3;
	int i = 0;
	char buffer[STR_LEN] = {0};
	size_t bitarr[] = {0, 1, 4};
	
	printf("BitArrToString:\n\n");
	for (i = 0; i < tests; ++i)
	{
		printf("number:\t%lu \n", bitarr[i]);
		printf("Function print:\t%s\n\n", BitArrToString(bitarr[i], buffer));
	}
	
	printf("\n\n");
}

static status_t BitArrMirrorTest(void)
{	
	const int tests = 4;
	status_t stat = SUCCESS;
	int i;
	size_t num[] = {0, 0xFFFFFFFF00000000, 0xFF00FF00FF00FF00,
					0xAAAAAAAAAAAAAAAA};
	size_t res[] = {0, 0x00000000FFFFFFFF, 0x00FF00FF00FF00FF,
					0x5555555555555555};
	
	printf("BitArrMirror:\n\n");
	for (i = 0; i < tests; ++i)
	{
		printf("test %d:", i + 1);
		if (BitArrMirror(num[i]) == res[i])
		{
			printf("\tPassed\n");
		}
		else
		{
			stat = FAIL;
			printf("\tFailed\n");
		}
	}
	
	printf("\n\n");
	
	return stat;
}

static status_t BitArrMirrorLutTest(void)
{	
	const int tests = 4;
	status_t stat = SUCCESS;
	int i;
	size_t num[] = {0, 0xFFFFFFFF00000000, 0xFF00FF00FF00FF00,
					0xAAAAAAAAAAAAAAAA};
	size_t res[] = {0, 0x00000000FFFFFFFF, 0x00FF00FF00FF00FF,
					0x5555555555555555};
	
	printf("BitArrMirrorLut:\n\n");
	for (i = 0; i < tests; ++i)
	{
		printf("test %d:", i + 1);
		if (BitArrMirrorLut(num[i]) == res[i])
		{
			printf("\tPassed\n");
		}
		else
		{
			stat = FAIL;
			printf("\tFailed\n");
		}
	}
	
	printf("\n\n");
	
	return stat;
}

static status_t BitArrMirrorO1Test(void)
{	
	const int tests = 4;
	status_t stat = SUCCESS;
	int i;
	size_t num[] = {0, 0xFFFFFFFF00000000, 0xFF00FF00FF00FF00,
					0xAAAAAAAAAAAAAAAA};
	size_t res[] = {0, 0x00000000FFFFFFFF, 0x00FF00FF00FF00FF,
					0x5555555555555555};
	
	printf("BitArrMirrorO1:\n\n");
	for (i = 0; i < tests; ++i)
	{
		printf("test %d:", i + 1);
		if (BitArrMirrorO1(num[i]) == res[i])
		{
			printf("\tPassed\n");
		}
		else
		{
			stat = FAIL;
			printf("\tFailed\n");
		}
	}
	
	printf("\n\n");
	
	return stat;
}
