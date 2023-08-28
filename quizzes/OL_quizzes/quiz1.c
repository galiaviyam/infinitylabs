#include <stdio.h>

void main(int argc, char *argv[])
{
	int num;
	const int num2 = 6;
	int num3;
	
	printf("%d", num);
	scanf("%d", &num);
	
	printf("100 divided by %d is %d", num, 100/num);
	
	char ch = 97;
	
	num3 = num2 - 5;
	printf("%d", num3);
	
	num = 4.7;

	
	num = 2 * num++;
}
