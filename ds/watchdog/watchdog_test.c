/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   WatchDog                */
/*   Date:      06/03/23                */
/*   Reviewer:  Noy Elankry             */
/*                                      */
/****************************************/

#include <stdio.h>
#include <time.h>		/* time */

#include "watchdog.h"	/* watchdog header file */


typedef enum status
{
	ERROR = -1,
	SUCCESS,
	FAIL
}status_t;


int main(void)
{
	time_t begin = {0};
	printf("start\n");
	
	WDStart(1, NULL);
	
	begin = time(NULL);
	while (time(NULL) < begin + 20);
	
	WDStop();
	
	printf("ended\n");
	return 0;
}

