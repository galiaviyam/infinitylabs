#include <stdio.h>

#include "header.h"

int x = 99;

void PrintGlobalVariableAddress(void)
{
	printf("address of x: %p\n", &x);
}
