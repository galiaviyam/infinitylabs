#include <stdio.h>
#include <assert.h>

#define BYTE_SIZE 8

int FlipDigitsInNum(int num);
char ByteMirror(char num);
void PrintBin(char value);
int FlipBit(int val, unsigned int n);
size_t CountSetBits(char c);
void SwapPointers(int **p1, int **p2);
void TestSwapPointers(void);
void TestStr(void);
size_t StrLen(const char *str);
int StrCmp(const char *str1, const char *str2);
char *StrnCpy(char *dest, const char *src, size_t n);
char *StrCpy(char* dest, const char* src);
char *StrCat(char *dest, const char *src);
unsigned long GetNFibonacciElement(unsigned int n);

int main(void)
{
	char x = 2;
	printf("\n************FlipDigit*************\n");
	printf("before: 58\nafter: %d\n\n", FlipDigitsInNum(58));
	printf("before: -520\nafter: %d\n\n", FlipDigitsInNum(-520));
	
	printf("\n************ByteMirror*************\n");
	printf("before: ");
	PrintBin(x);
	printf("\nafter:  ");
	PrintBin(ByteMirror(x));
	printf("\n");
	
	printf("\n**********CountSetBits**********\n");
	printf("8: %lu\n", CountSetBits(8));
	printf("5: %lu\n", CountSetBits(5));
	printf("85: %lu\n", CountSetBits(85));
	
	printf("\n**********SwapPointers**********\n");
	TestSwapPointers();
	
	TestStr();
	
	
	printf("%dth Fibonacci element is: %ld\n", 4, GetNFibonacciElement(4));
	printf("%dth Fibonacci element is: %ld\n", 5, GetNFibonacciElement(5));
	printf("%dth Fibonacci element is: %ld\n", 6, GetNFibonacciElement(6));
	
	return 0;
}

int FlipDigitsInNum(int num)
{
	int res = 0;
	int remain = 0;

	while (0 != num)
	{
		remain = num % 10;
		res = res * 10 + remain;
		num /= 10;
	}

	return res;
}

char ByteMirror(char num)
{
	char mirror = 0;
	size_t i = 0;
	
	for (i = 0; 8 > i; ++i)
	{
		mirror <<= 1;
		mirror |= (1 & num);
		num >>= 1;
	}
	
	return mirror;
}

void PrintBin(char value)
{
    int i = 0;

    for (i = 7; i >= 0; i--)
    {
        printf("%d", (value & (1 << i)) >> i);
    }
    printf("\n");
}

int FlipBit(int val, unsigned int n)
{
	return (val ^ (1 << n));
}

size_t CountSetBits(char c)
{
	size_t count = 0;
	
	while (0 != c)
	{
		if (1 & c)
		{
			++count;
		}
		c = c >> 1;
	}
	
	return count;
}

char RotateLeft(char byte, unsigned int nbits)
{	
	return ((byte << nbits) | (byte >> (BYTE_SIZE - nbits)));
}

void SwapPointers(int **p1, int **p2)
{
	int *tmp = NULL;
	
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void TestSwapPointers(void)
{
	int a = 5;
	int b = 6;
	int *p1 = &a;
	int *p2 = &b;
	
	SwapPointers(&p1, &p2);
	printf("%d, %d\n", a, b);
	printf("%d, %d\n", *p1, *p2);
}

size_t StrLen(const char *str)
{
	size_t count = 0;
	
	assert(NULL != str);
	
	while ('\0' != *str)
	{
		++count;
		++str;
	}
	
	return count;
}

int StrCmp(const char *str1, const char *str2)
{
	assert(NULL != str1);
	assert(NULL != str2);
	while ('\0' != *str1 && (*str1 == *str2))
	{
		++str1;
		++str2;
	}
    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

char *StrCpy(char* dest, const char* src)
{
	char *ptr = NULL;
	int src_len = 0;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	ptr = dest;
	src_len = StrLen(src) + 1;
	
	ptr = StrnCpy(dest, src, src_len);
 
	return ptr;
}

char *StrnCpy(char *dest, const char *src, size_t n)
{
	char* ptr = NULL;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	ptr = dest;
	
	while ('\0' != *src && 0 !=  n)
	{
		if (NULL == dest)
		{
			return NULL;
		}
		
		*dest = *src;
		++dest;
		++src;
		--n;
	}
	
	while ('\0' != *dest && '\0' == *src)
	{
		*dest = '\0';
		++dest;
	}
	
	return ptr;
}

char *StrCat(char *dest, const char *src)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	StrCpy(dest + StrLen(dest), src);
	
	return dest;
}

void TestStr(void)
{
	int result;

	char str1[20] = "Hello World!";
	char str2[20] = "Hello!";
	char str3[20];
	char str4[20] = "hell";
	
	char src[50];
	char dest[50];

		
	/* StrLen test */
	printf("\n**********StrLen***********\n");
		
	printf("length is %lu \n",StrLen(str1));
	
	/* StrCmp test */
	printf("\n**********StrCmp***********\n");

	result = StrCmp(str1, str2);
	printf("StrCmp(str1, str2) = %d\n", result);
	
	result = StrCmp(str2, str4);
	printf("StrCmp(str2, str4) = %d\n", result);
	
	/* StrCpy test */
	printf("\n**********StrCpy***********\n");
	
	StrCpy(str3, "kuku");
	printf("str3 = %s\n", str3);
	
	/* StrnCpy test */
	printf("\n**********StrnCpy***********\n");
	
	StrnCpy(str3, str1, 4);
	printf("str3 = %s\n", str3);
	
	/* StrCat test */
	printf("\n**********StrCat***********\n");

	StrCpy(dest,  "Happy ");
	StrCpy(src, "Birthday!");
	StrCat(dest, src);
	printf("%s\n", dest);
 
}

unsigned long GetNFibonacciElement(unsigned int n)
{
	unsigned int a = 0;
	unsigned int b = 1;
	unsigned int c = 1;
	
	if (0 == n)
	{
		return 0;
	}
	
	while (--n)
	{
		c = a + b;
		a = b;
		b = c;
	}
	
	return c;
}

char *IntToString(char *str, int num)
{
	assert(NULL != str);
	
	sprintf(str, "%d", num);
	return str;
}


char MultiplyByEight(char num)
{
	return (num << 3);
}
