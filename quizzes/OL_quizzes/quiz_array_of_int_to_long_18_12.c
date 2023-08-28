#include <stddef.h>
#include <stdio.h>

long *SumIntPairsToLong(int ints[], size_t numOfElemnts)
{
	size_t i = 0;
	long *runner = NULL;
	
	runner = (long *)ints;
	
	for (i = 0; i < numOfElemnts; ++runner, i += 2)
	{
		*runner = (long)ints[i] + (long)ints[i + 1];
	}
	
	return ((long *)ints);
}

int main()
{
	int ints[] = {1, 6 ,456, -3, 8, 12};
	long *result = SumIntPairsToLong(ints, 6);
	size_t i = 0;
	
	for (i = 0; i < 3; ++i)
	{
		printf("%ld, ", result[i]);
	}
	
	printf("\n");
	
	return 0;
}
