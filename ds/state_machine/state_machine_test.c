/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	State machine			*/
/*   Date:		22/01/23				*/
/*	 Reviewer:	Sveta					*/
/*										*/
/****************************************/

#include <stdio.h>			/* printf */

#include "state_machine.h"	/* header file */

enum 
{
	ACCEPTED = 0,
	NOT_ACCEPTED
};

static void PrintAccepted(int state);

int main(void)
{
	char *arr[] = {"00", "01110", "0101010", "0", "01", "10001", "101010"};
	size_t i = 0;
	
	for (i = 0; i < 7; ++i)
	{
		printf("%s: ", arr[i]);
		PrintAccepted(FSMIsValidInput(arr[i]));
	}
	
	return 0;
}

static void PrintAccepted(int state)
{
	if (state == ACCEPTED)
	{
		printf("\tACCEPTED\n");
	}
	else
	{
		printf("\tNOT ACCEPTED\n");
	}
}

