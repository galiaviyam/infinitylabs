/*------------------------------------------------------------------*/
/* DEVELOPER: Gali Aviyam                                           */
/* DATE MODIFIED: 13.11.2022                                        */
/* WORKSHEET NAME: Functions                                        */
/* GDB, Valgrind tested                                             */
/* Reviewer: Eitan                                                  */
/*------------------------------------------------------------------*/

#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/

#define ESC 27
#define SIZE 256

int InputCheckIfElse();
int InputCheckSwitchCase();
int InputCheckLUT();
void APrint(void);
void TPrint(void);
void ESCProgram(void);
void DoNothing(void);

typedef void (*functions)();

int main()
{
	char choice = '\0';
	printf("Hello! please select an option:\n1. if/else\n2. switch case\n3. LUT\n4. quit\n");
	
	choice = getchar();
	
	switch (choice)
	{
		case '1':
			InputCheckIfElse();
			break;
		case '2':
			InputCheckSwitchCase();
			break;
		case '3':
			InputCheckLUT();
			break;
		default:
			break;
	}
	
	return 0;
}

int InputCheckIfElse()
{
	char key ='\0';
	
	printf("Welcome to If/Else! please press any key.\npress esc to quit.\n");
	system("stty -icanon -echo");
		
	while (ESC != key)
	{
		key = getchar();
		
		if ('a' == key)
		{
			APrint();
		}
		if ('t' == key)
		{
			TPrint();
		}
	}
	
	system("stty icanon echo");
	return 0;
}

int InputCheckSwitchCase()
{
	char key ='\0';
		
	printf("Welcome to Switch Case! please press any key.\npress esc to quit.\n");
	system("stty -icanon -echo");
	
	while (ESC != key)
	{
		key = getchar();
		
		switch (key)
		{
			case 'a':
				APrint();
				break;
			case 't':
				TPrint();
				break;
			default:
				break;
		}
	}
	
	system("stty icanon echo");
	return 0;
}

int InputCheckLUT()
{
	int c = '\0';
	size_t i = 0;
	
	functions lut[SIZE] = {NULL};
	
	printf("Welcome to LUT! please press any key.\npress esc to quit.\n");
	system("stty -icanon -echo");
	
	for (i = 0; i < SIZE; ++i)
	{
		lut[i] = &DoNothing;
	}
	
	lut['a'] = &APrint;
	lut['t'] = &TPrint;
	lut[ESC] = &ESCProgram;
	
	while (ESC != (c = getchar()))
	{
		lut[getchar()]();
	}
	
	return 0;
}

void APrint(void)
{
	printf("A-pressed\n");
}

void TPrint(void)
{
	printf("T-pressed\n");
}
void ESCProgram(void)
{
	system("stty icanon echo");
	exit(0);
}

void DoNothing(void)
{
}
