#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/
#include <ctype.h> /*tolower*/
#include <stdlib.h> /*malloc*/
#include "string.h"

#define ERROR -1
#define SIZE 20

int main()
{
	int result;
	int chr1 = 'l';

	char str1[SIZE] = "Hello World!";
	char str2[SIZE] = "Hello!";
	char str3[SIZE];
	char str4[SIZE] = "HELLO!";
	char *str5;
	char *str6;
	
	const char haystack[20] = "supernova";
	const char needle[10] = "nova";
	const char str8[20] = "blabla dancey";
	const char str9[10] = "dance";
	
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
	
	/* StrnCmp test */
	printf("\n**********StrnCmp***********\n");
	
	result = StrnCmp(str1, str2, 0);
	printf("StrnCmp(str1, str2) = %d\n", result);
	
	result = StrnCmp(str1, str2, 4);
	printf("StrnCmp(str1, str2) = %d\n", result);
	
	result = StrnCmp(str1, str2, 7);
	printf("StrnCmp(str1, str2) = %d\n", result);
	
	/* StrcaseCmp test */
	printf("\n*********StrcaseCmp**********\n");

	result = StrcaseCmp(str2, str4);
	printf("StrcaseCmp(str2, str4) = %d\n", result);
	
	/* StrChr test */
	printf("\n**********StrChr***********\n");
	
	str5 = StrChr(str2, chr1);
	printf("char: %c\npointer: %p\n", *str5, str5);
	
	/* StrDup test */
	printf("\n**********StrDup***********\n");
	
	str6 = StrDup(str3);
	printf("str3 = %s\n", str3);
	free(str6);
	
	/* StrCat test */
	printf("\n**********StrCat***********\n");

	StrCpy(dest,  "Happy ");
	StrCpy(src, "Birthday!");
	StrCat(dest, src);
	printf("%s", dest);
 
	/* StrnCat test */
	printf("\n**********StrnCat***********\n");
	
	StrCpy(dest,  "Happy ");
	StrnCat(dest, src, 3);
	printf("%s\n", dest);
	
	/* Strstr test */
	printf("\n**********StrStr***********\n");
	
	printf("The substring is: %s\n", StrStr(haystack, needle));
	printf("The substring is: %s\n", StrStr(str8, str9));	
	printf("The substring is: %s\n", StrStr("aaaaaaaaabcdzzzzzzzzzzzzzzzz", "abcd"));
	printf("The substring is: %s\n", StrStr("everibody dance now", "dance"));
	
	/* StrSpn test */
	printf("\n**********StrSpn***********\n");
	
	printf("Length of initial segment matching: %ld\n", StrSpn("cabbage", "abc"));
	
	return 0;
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
		str1++;
		str2++;
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

int StrnCmp(const char *str1, const char *str2, size_t n)
{
	assert(NULL != str1);
	assert(NULL != str2);
	
	while ('\0' != *str1 && (*str1 == *str2) && 0 != n)
	{
		++str1;
		++str2;
		--n;
	}
	if (0 == n)
	{
		return 0;
	}
	
	return (*(unsigned char*)str1 - *(unsigned char*)str2);
}

int StrcaseCmp(const char *str1, const char *str2)
{
	assert(NULL != str1);
	assert(NULL != str2);
	
	while ('\0' != *str1 && (tolower(*str1) == tolower(*str2)))
	{
		++str1;
		++str2;
	}
	
	return *(const char*)str1 - *(const char*)str2;
}

char *StrChr(const char *str, int c)
{
	assert(NULL != str);
	
	while ('\0' != *str)
	{
		if ((char)c == *str)
		{
			return (char*)str;
		}
		++str;
	}
	
	return NULL;
}

char *StrDup(char *src)
{
	char *str = NULL;
	int len = 0;
	
	assert(NULL != src);
	
	len = StrLen(src);
	
	str = malloc(len + 1);
	if (NULL == str)
	{
		return NULL;
	}
	
	StrCpy(str, src);
	
	return str;
}

char *StrCat(char *dest, const char *src)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	StrCpy(dest + StrLen(dest), src);
	
	return dest;
}

char *StrnCat(char *dest, const char *src, size_t num)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	StrnCpy(dest + StrLen(dest), src, num);
		
	return dest;
}

char *StrStr(const char *haystack, const char *needle)
{
	size_t needle_len = 0;

	assert(NULL != haystack);
	assert(NULL != needle);
	
	needle_len = StrLen(needle);
	
	if ('\0' == (*needle))
	{
		return (char*)haystack;
	}
	
	while ('\0' != (*haystack))
	{
		
		if (StrnCmp(haystack, needle, needle_len) == 0)
		{
			return (char*)haystack;
		}
		haystack++;
	}
	return NULL;
}

size_t StrSpn(const char *str, const char *chars)
{
	size_t counter = 0;
	
	assert(NULL != str);
	assert(NULL != chars);
	
	while ('\0' != *str && NULL == StrChr(str, *chars))
	{
		++counter;
		++str;
	}

	return counter;
}
