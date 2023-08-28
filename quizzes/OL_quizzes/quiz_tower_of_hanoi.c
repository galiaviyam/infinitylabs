#include <stdio.h>	/* printf */

static void TowerOfHanoi(int n, char from_rod, char to_rod, char aux_rod);

int main(void)
{
	TowerOfHanoi(3, 'A', 'C', 'B');
	
	return 0;
}

static void TowerOfHanoi(int n, char from_rod, char to_rod, char aux_rod)
{
	if (1 == n)
	{
		printf("Disk %d moved from %c to %c\n", n, from_rod, to_rod);
	}
	else
	{
		TowerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
		printf("Disk %d moved from %c to %c\n", n, from_rod, to_rod);
		TowerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
	}
}
