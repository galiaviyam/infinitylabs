#include <stdio.h>
#include <assert.h>




static void PrintPermutations(char *str, size_t l, size_t r);
static void Swap(char *a, char *b);

int main(void)
{
	char str[10] = {'A', 'B', 'C', '\0'};
	
	printf("The permutations of \"%s\" are:\n", str);
	
	PrintPermutations(str, 0 , 3);

	return 0;
}

static void PrintPermutations(char *str, size_t l, size_t r)
{
	size_t i = 0;
	
	assert(NULL != str);
	
	if (l == r)
	{
		printf("%s\n", str);
		return;
	}
	
	for (i = l; i < r; ++i)
	{
		Swap((str + l), (str + i));
		PrintPermutations(str, l + 1, r);
		Swap((str + l), (str + i));
	}
}

static void Swap(char *a, char *b)
{
	char tmp = 0;
	
	assert(NULL != a);
	assert(NULL != b);
	tmp = *a;
	*a = *b;
	*b = tmp;
}
