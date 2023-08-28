#include <stdio.h>

/*struct A*/
/*{*/

/*};*/

struct B
{
	int x;
	int y;
};

int main(void)
{
/*	printf("%lu\n", sizeof(struct A));*/
	printf("%lu\n", sizeof(struct B));
	
	return 0;
}
