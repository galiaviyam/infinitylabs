/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Signals Ping Pong       */
/*   Date:      21/02/23                */
/*   Reviewer:  Moriah                  */
/*                                      */
/****************************************/

#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE	/* for kill	*/
#endif /* _POSIX_SOURCE */

#include <stdlib.h>		/*sysytem*/
#include <signal.h>		/*sigaction*/
#include <stdio.h>		/*printf*/
#include <sys/types.h>	/*pid_t*/ 
#include <unistd.h>		/*execvp*/
#include <sys/wait.h>	/*wait, waitpid*/

typedef enum status
{
	SYS_FAULT = -1,
	SUCCESS
}status_t;

static void PingPong1(void);
static void PingPong2(void);
static void SignalHandler(int signum);
/*----------------------------------------------------------------------------*/

int main(void)
{
	PingPong1();
	PingPong2();
	
	return 0;
}
/*----------------------------------------------------------------------------*/

static void PingPong1(void)
{
	pid_t pid = 0;
	status_t status = 0;
	struct sigaction sa = {0};
	
	sa.sa_flags = 0;
	sa.sa_handler = &SignalHandler;
	
	if (SYS_FAULT == sigemptyset(&sa.sa_mask))
	{
		return;
	}

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	
	pid = fork();
	if (0 > pid)
	{
		printf("fork fail");
		return;
	}
	
	if (0 < pid)
	{
		kill(pid, SIGUSR1);
		waitpid(pid, (int *)status, 0);
	}
	
}

static void PingPong2(void)
{
	pid_t pid = 0;
	status_t status = 0;
	struct sigaction child = {0};
	struct sigaction parent = {0};
	
	child.sa_flags = 0;
	child.sa_handler = &SignalHandler;
	
	if (SYS_FAULT == sigemptyset(&child.sa_mask))
	{
		return;
	}

	parent.sa_flags = 0;
	parent.sa_handler = &SignalHandler;
	
	if (SYS_FAULT == sigemptyset(&parent.sa_mask))
	{
		return;
	}
	
	sigaction(SIGUSR1, &child, NULL);
	sigaction(SIGUSR2, &parent, NULL);
	
	pid = fork();
	printf("pid: %d\n", pid);
	sleep(10);
	
	if (0 > pid)
	{
		printf("fork fail");
		return;
	}
	
	if (0 == pid)
	{
		sleep(20);
		
		if ((SYS_FAULT == execlp("pwd", "pwd", NULL)))
		{
			exit(SYS_FAULT);
		}
	}
	
	if (0 < pid)
	{
		kill(pid, SIGUSR1);
		pause();
		waitpid(pid, (int *)status, 0);
	}
	
}

/*--------------------------  Utility Functions  ----------------------------*/
static void SignalHandler(int signum)
{
	if (SIGUSR1 == signum)
	{
		printf("PARENT: Ping\n");	
		kill(getppid(), SIGUSR2);	
	}
	else if (SIGUSR2 == signum)
	{
		printf("CHILD: Pong\n");
	}
}

