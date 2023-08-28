#include <stdio.h>
#include <string.h>
#include <ctype.h>

static void TF(int num);
static char *StrRev(char *str);
static void Swap(int *a, int *b);


int main()
{
	char *str = "HeLlo";	
	
	TF();
	
	printf("%s", StrRev(str));
	
	return 0;
}



/*function 1*/

static void TF(int num)
{
	size_t i = 0;
	
	for (i = 1; i <= num; ++i)
	{
		if (0 == i % 3)
		{
			printf("T");
		}
		if (0 == i % 5)
		{
			printf("F");
		}
		else if (0 != i % 3)
		{
			printf("%lu", i);
		}
		printf("\n");
	}
}


static char *StrRev(char *str)
{
	char *start = NULL;
	char *end = NULL;
	char tmp = '\0';
	
	assert(NULL != str);
	
	start = str;
	end = strlen(str) -1;
	
	while (end >= start)
	{
		tolower(*end);
		tolower(*start);
		Swap(*end, *start);
		
		++start;
		--end;
	}
	start = tmp;
	
	return str;
}

static void Swap(int *a, int *b)
{
	int tmp = *a;

	*a = *b;

	*b = tmp;
}
