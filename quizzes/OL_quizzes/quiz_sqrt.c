#include <stdio.h>
#include <assert.h>

double Sqrt(double number);

int main(void)
{
	double num1 = 9;
	double num2 = 64;
	double num3 = 100;
	double num4 = 2.5;
	double num5 = 555;
	
	printf("Sqrt of %.2f:\t%.2f\n", num1, Sqrt(num1));
	printf("Sqrt of %.2f:\t%.2f\n", num2, Sqrt(num2));
	printf("Sqrt of %.2f:\t%.2f\n", num3, Sqrt(num3));
	printf("Sqrt of %.2f:\t%.2f\n", num4, Sqrt(num4));
	printf("Sqrt of %.2f:\t%.2f\n", num5, Sqrt(num5));
	
	return 0;
}


double Sqrt(double number)
{
	double result = 0;
	double tmp = 0;
	
	assert(0 <= number);
   	
   	result = number / 2;
   	
	while(result != tmp)
	{
	    tmp = result;
	    result = ( number/tmp + tmp) / 2;
	}
	
	return (result);
}

