/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Signals Ping Pong       */
/*   Date:      21/02/23                */
/*   Reviewer:  Moriah                  */
/*                                      */
/****************************************/

#define _GNU_SOURCE

#include <stdio.h>		/* printf() */
#include <unistd.h>		/* fork() */
#include <signal.h>		/* kill() */
#include <sys/wait.h>	/* wait() */
#include <assert.h>		/* assert() */
#include <stdlib.h>		/* atoi */


static void Pong(int pid_ping);
static void SigHandler(int sig_num, siginfo_t *info, void *context);

int main(int argc, char *argv[])
{
	assert(argv[0]);
	assert(argv[1]);
	
	Pong(atoi(argv[1]));
	(void)argc;
	
	return 0;
}

static void Pong(int pid_ping)
{
	struct sigaction sa = {0};
/*	siginfo_t info = {0};*/
	int i = 0;
/*	int pid = getpid();*/
	
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &SigHandler;
	
/*	info.si_pid = pid;*/
	
	sigaction(SIGUSR2, &sa, NULL);
	
	for (i = 0; i < 3; ++i)
	{
		kill(pid_ping, SIGUSR1);
		sleep(1);
	}
}

static void SigHandler(int sig_num, siginfo_t *info, void *context)
{
	if (SIGUSR2 == sig_num)
	{
		printf("PONG\n");
	}
	
	(void)context;
	(void)info;
}

