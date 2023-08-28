#include <stdio.h>

static double Power(int n);

static int Flip(int num);

static void Swap(int *a, int *b);

int main()
{
	int a = 1;
	int b = 2;

	/* power test */
	printf("**********power************\n");
	
	printf("%.1f\n", Power(-2));
	printf("%.1f\n", Power(-1));
	printf("%.1f\n", Power(0));
	printf("%.1f\n", Power(1));
	printf("%.1f\n", Power(2));
	printf("%.1f\n", Power(3));
	printf("%.1f\n", Power(4));
	
	/* flip test */
	printf("\n***********flip************\n");
	
	printf("%d\n", Flip(1234));
	printf("%d\n", Flip(5670));
	printf("%d\n", Flip(-5670));
	
	/* swap test */
	printf("\n***********swap************\n");
	
	Swap(&a, &b);
	
	printf("a: %d b: %d\n", a, b);
	
	return 0;
}

static double Power(int n)
{
	int i = 0;
	double base = 10, res = 1;
	
	if (n < 0)
	{
		n = -n;
		base = 1/base;
	}
	
	for (i=1;i<n;i++)
	{
		res *= base;
	}
	
	return res;
}

static int Flip(int num)
{
	int res = 0, remain = 0;

	while (num != 0)
	{
		remain = num % 10;
		res = res * 10 + remain;
		num /= 10;
	}

	return res;
}

static void Swap(int *a, int *b)
{
	int tmp = *a;

	*a = *b;

	*b = tmp;
}

