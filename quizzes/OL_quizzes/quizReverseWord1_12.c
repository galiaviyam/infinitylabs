#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void ReverseWord(char* begin, char* end);
void ReverseWordsInSentence(char* s);

int main(void)
{
	char s[] = "I like chocolate and cookies";
	
	ReverseWordsInSentence(s);
	printf("%s\n", s);
	
	return 0;
}

void ReverseWord(char* begin, char* end)
{	
	char tmp = '\0';
	
	while (begin < end)
	{
		tmp = *begin;
		*begin = *end;
		*end = tmp;
		++begin;
		--end;
	}
}
 
void ReverseWordsInSentence(char *str)
{
	char *start = NULL;
	char *tmp = NULL;
	
	assert(NULL != str);
	
	start = str;
	tmp = str;
	
	while (*tmp) 
	{
		++tmp;
		if ('\0' == *tmp)
		{
			ReverseWord(start, tmp - 1);
		}
		else if (' ' == *tmp)
		{
			ReverseWord(start, tmp - 1);
			start = tmp + 1;
		}
	}
 
	ReverseWord(str, tmp - 1);
}
