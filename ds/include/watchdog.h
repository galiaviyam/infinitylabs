/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   WatchDog                */
/*   Date:      06/03/23                */
/*   Reviewer:  Noy Elankry             */
/*                                      */
/****************************************/

#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

/*----------------------------------------------------------------------------
A watchdog is an electronic or software timer that is used to detect and 
recover from computer malfunctions. This watchdog acts as a software timer 
that is used for re-running the user's software in case of a crash. 
In the code section protected by the watchdog, if the app collaps,
it will be re-run by the watchdog and vice versa.

The protected code section of the user's code is between the call of WDStart
and the call of WDStop (see below).
----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Description
	The WDStart function starts the mutual protection of the watchdog.
Parameters
	'argc' - The argc argument of the user's app.
	'argv' - The argv argument of the user's app.
Return Value
	0 - SUCCESS
	Non-zero value - Failure
------------------------------------------------------------------------------*/
int WDStart(int argc, char **argv);

/*------------------------------------------------------------------------------
Description
	The WDStop function stops the mutual protection of the watchdog.
------------------------------------------------------------------------------*/
void WDStop(void);

#endif /* __WATCHDOG_H__ */


