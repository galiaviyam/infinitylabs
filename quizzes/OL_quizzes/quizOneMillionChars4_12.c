#include <stdio.h>

#define ASCII 256
#define MAX2(a, b) (a > b) ? (a) : (b)

static size_t chars[ASCII] = {0};

void OneMillionChars(char c)
{
	size_t i = 0;
	size_t max = 0;
	
	if (0 != c)
	{
		++chars[(int)c];
	}
	else
	{
		for (i = 0; i < ASCII; ++i)
		{
			max = MAX2(max, chars[i]);
			chars[i] = 0;
		}
		printf("%lu\n", max);
	}
}

size_t CountSetBits(long num)
{
	size_t count = 0;
	
	while (num)
	{
		num = num & (num - 1);
		++count;
	}
	return count;
}

int main(void)
{
	OneMillionChars('a');
	OneMillionChars('b');
	OneMillionChars('a');
	OneMillionChars('c');
	OneMillionChars('a');
	OneMillionChars('b');
	OneMillionChars(0);
	
	OneMillionChars('a');
	OneMillionChars('b');
	OneMillionChars('b');
	OneMillionChars(0);
	
	printf("%lu\n", CountSetBits((long)12));
	
	return 0;
}
