#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main()
{
	char *str1 = "hello";
	const int len = strlen(str1);

	char str2[6];

	char *str3 = (char *)malloc(len + 1);
	
	if (NULL == str3)
	{
		return -1;
	}
	
	while (*str1)
	{
		*str3 = *str1;
		++str3;
		++str1;
	}
	
	strcpy(str2, str1);
	
	if (islower(*str1))
	{
		*str1 = toupper(*str1);
	}
	
	free(str3);
	str3 = NULL;
	
	return 0;
}
