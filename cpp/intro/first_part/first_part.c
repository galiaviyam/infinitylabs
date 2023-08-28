#include <stdio.h> //printf

static void Ex2(void);
static void Ex3(void);

int main(void)
{
	Ex2();

	
	return 0;
}

void Ex2(void)
{
	enum E {AA, BB, CC, DD};
	enum E2 {TT, KK};
	enum E e = (enum E)2;
	enum E2 e2 = (enum E2)AA;
	// E2 e22 = KK;
	//++e;
	int i = e;
}


