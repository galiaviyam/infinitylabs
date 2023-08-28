#include <stdio.h>	/* printf */
#include <stdlib.h>	/* rand */

static size_t lut[100] = {0};
static size_t num_of_calls = 0;

static size_t GetNonReapitingRandom(void);

int main(void)
{
	size_t i = 0;
	
	for (i = 0; i < 150; ++i)
	{	
		printf("%lu\n", GetNonReapitingRandom());
	}
	
	return 0;
}


static size_t GetNonReapitingRandom(void)
{
	size_t num = 0;
	size_t i = 0;
	
	++num_of_calls;
	
	while (num_of_calls < 100)
	{
		num = rand() % 100;
		
		if (0 == lut[num])
		{
			lut[num] = 1;
			
			return num;
		}
	}
	
	num_of_calls = 0;
	
	for (i = 0; i < 100; ++i)
	{
		lut[i] = 0;
	}
	
	num = rand() % 100;
	lut[num] = 1;
			
	return num;
}
