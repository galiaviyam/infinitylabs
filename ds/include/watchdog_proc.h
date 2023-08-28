/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   WatchDog                */
/*   Date:      06/03/23                */
/*   Reviewer:  Noy Elankry             */
/*                                      */
/****************************************/

#ifndef __WATCHDOG_PROC_H__
#define __WATCHDOG_PROC_H__

/*----------------------------------------------------------------------------
A watchdog is an electronic or software timer that is used to detect and 
recover from computer malfunctions. This watchdog acts as a software timer 
that is used for re-running the user's software in case of a crash. 
In the code section protected by the watchdog, if the app collaps,
it will be re-run by the watchdog and vice versa.

The protected code section of the user's code is between the call of WDStart
and the call of WDStop (see below).
----------------------------------------------------------------------------*/

int WDProc(int argc, char **argv);

#endif /* __WATCHDOG_PROC_H__ */


