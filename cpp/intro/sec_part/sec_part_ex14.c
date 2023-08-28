#include <stdio.h>

int main()
{
	const int i = 3;
    int *ip = (int*)&i;
    i = 4;
    *ip = 5;
/*    int arr[i];*/

    printf("%d %d\n", i, *ip);
    return 0;
}
