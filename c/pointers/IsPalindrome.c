#include "string.h"


int main()
{
	printf("\n********IsPalindrome*********\n");
	
	printf("12321: %d\n", IsPalindrome("12321"));
	printf("1: %d\n", IsPalindrome("1"));
	printf("papa: %d\n", IsPalindrome("papa"));
	printf("papap: %d\n", IsPalindrome("papap"));
	printf("123: %d\n", IsPalindrome("123"));
}

int IsPalindrome(char *str)
{
	char *start = NULL;
	char *end = NULL;
	assert(NULL != str);
	
	start = (char*)str;
	end = (char*)str + StrLen(str) -1;
		
	while (start < end)
	{
		if (*start != *end)
		{
			return 0;
		}
		
		++start;
		--end;
	}
	
	return 1;
}
