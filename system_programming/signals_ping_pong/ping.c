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


static void Ping(void);
static void SigHandler(int sig_num, siginfo_t *info, void *context);

int main(void)
{
	Ping();
	
	return 0;
}

static void Ping(void)
{
	struct sigaction sa = {0};
	int i = 0;
	
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &SigHandler;
	
	sigaction(SIGUSR1, &sa, NULL);

	printf("PING PID: %d\n", getpid());
	
	for (i = 0; i < 3; ++i)
	{
		pause();
	}
		
	
}

static void SigHandler(int sig_num, siginfo_t *info, void *context)
{
	if (SIGUSR1 == sig_num)
	{
		printf("PING\n");
		kill(info->si_pid, SIGUSR2);
	}
	
	(void)context;
}

