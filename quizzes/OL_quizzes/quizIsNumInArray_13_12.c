#include <stdio.h>

int IsNumInArray(int *arr, size_t size, int num);

int main(void)
{
	int arr[5] = {1, 2, 3, 4, 5};
	printf("%d\n", IsNumInArray(arr, 5, 5));
	printf("%d\n", IsNumInArray(arr, 5, 2));
	printf("%d\n", IsNumInArray(arr, 5, 7));
	printf("%d\n", IsNumInArray(arr, 5, 6));
	return 0;
}


int IsNumInArray(int *arr, size_t size, int num)
{
	int status = 1;
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		status = status * (num ^ arr[i]);
	}
	
	return (!status);
}
