/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   WatchDog                */
/*   Date:      06/03/23                */
/*   Reviewer:  Noy Elankry             */
/*                                      */
/****************************************/

#define _POSIX_SOURCE	/* for kill */
#define _GNU_SOURCE		/* for setenv */

#include <assert.h>		/* assert */
#include <sys/types.h>	/* pid_t */ 
#include <signal.h>		/* sigaction */
#include <fcntl.h>		/* For O_* constants */
#include <sys/stat.h>	/* For mode constants */
#include <unistd.h>		/* execvp */
#include <sys/wait.h>	/* waitpid */
#include <semaphore.h>	/* sem_open */
#include <stdio.h>		/* printf */
#include <stdlib.h>		/* setenv */

#include "scheduler.h"	/* scheduler header file */
#include "watchdog.h"	/* watchdog header file */

#define SEC_TILL_RESEND (1)
#define SEC_TILL_RECHECK (5)
#define NUM_OF_RESEND (5)

typedef enum state
{
	READY = 0,
	OK,
	NOT_OK,
	STOP
}state_t;

typedef enum status
{
	ERROR = -1,
	SUCCESS
}status_t;

/*------------Global Variables------------*/
static int g_state = READY;
static scheduler_t *g_sched = NULL;
static pid_t g_app_pid = 0;
static sem_t *g_sem_wd = NULL;

/*------------------------Static Function Declarations-----------------------*/
/*------------Set up Functions------------*/
static int SetUp(char **argv);
static int SetUpSched(char **argv);
static int SetUpSignals(void);
static int SetUpSem(void);

/*--------------Task Functions--------------*/
static int CheckAppTask(void *param);
static int SendSigTask(void *param);

/*---------Signal Handler Functions---------*/
static void Sig1Handler(int signum);
static void Sig2Handler(int signum);

/*-------------Cleanup Function-------------*/
static void DoNothing(void *param);

/*----------------------------------- Main ----------------------------------*/
int WDProc(int argc, char **argv)
{
	status_t status = SUCCESS;
	
	assert(0 < argc);
	
	printf("WD pid: %d\n", getpid());
	
	status = SetUp(argv);
	if (SUCCESS != status)
	{
		return ERROR;
	}
	
	sem_post(g_sem_wd);
	
	if (SUCCESS != SchedRun(g_sched))
	{
		SchedDestroy(g_sched);
		return ERROR;
	}
	SchedDestroy(g_sched);

	sem_wait(g_sem_wd);
	sem_close(g_sem_wd);
	sem_unlink("sem_wd");
	
	return status;
}


/*------------Set up Functions------------*/
static int SetUp(char **argv)
{
	status_t status = SUCCESS;
	char *name = "ENV_PATH";
	
	assert(NULL != argv);
	
	g_app_pid = getppid();

	if (ERROR == setenv(name, "exists", 0))
	{
		return ERROR;
	}
	status += SetUpSignals();
	status += SetUpSem();	
	status += SetUpSched(argv);
	
	if (SUCCESS != status)
	{
		status = ERROR;
	}
	
	return status;
}

static int SetUpSignals(void)
{
	struct sigaction sa1 = {0};
	struct sigaction sa2 = {0};
	
	sa1.sa_handler = &Sig1Handler;
	sa2.sa_handler = &Sig2Handler;
	sa1.sa_flags = 0;
	sa2.sa_flags = 0;

	if (ERROR == sigemptyset(&sa1.sa_mask))
	{
		return ERROR;
	}
	
	if (ERROR == sigemptyset(&sa2.sa_mask))
	{
		return ERROR;
	}
	
	if (SUCCESS != sigaction(SIGUSR1, &sa1, NULL))
	{
		return ERROR;
	}
	if (SUCCESS != sigaction(SIGUSR2, &sa2, NULL))
	{
		return ERROR;
	}
	
	return SUCCESS;
}

static int SetUpSem(void)
{
	g_sem_wd = sem_open("sem_wd", O_CREAT, S_IRWXU, 0);
	if (SEM_FAILED == g_sem_wd)
	{
		return ERROR;
	}
	
	return SUCCESS;
}

static int SetUpSched(char **argv)
{
	ilrd_uid_t uid = {0};
	
	g_sched = SchedCreate();
	if (NULL == g_sched)
	{
		return ERROR;
	}
	
	uid = SchedAddTask(g_sched, &SendSigTask, NULL, &DoNothing, NULL, 
					time(NULL));
	if (UIDIsEqual(bad_uid, uid))
	{
		SchedDestroy(g_sched);
		return ERROR;
	}
	uid = SchedAddTask(g_sched, &CheckAppTask, argv, &DoNothing, NULL, 
					time(NULL));
	if (UIDIsEqual(bad_uid, uid))
	{
		SchedDestroy(g_sched);
		return ERROR;
	}
	
	return SUCCESS;
}

/*--------------Task Functions--------------*/
static int SendSigTask(void *param)
{
	(void)param;
	
	kill(g_app_pid, SIGUSR1);
	return (SEC_TILL_RESEND);
}

static int CheckAppTask(void *param)
{	
	assert(NULL != param);
	printf("check from wd\n");
	switch (g_state)
	{
		case OK:
		{		
			g_state = NOT_OK;
			break;
		}
		case NOT_OK:
		{
			g_app_pid = fork();
			
			if (0 > g_app_pid)
			{
				return ERROR;
			}
			if (0 == g_app_pid)
			{
				printf("App Revived!\n");
				if (SUCCESS != execvp("./a.out", (char **)param))
				{
					exit(1);
				}
			}
			sem_wait(g_sem_wd);
			break;		
		}
		case STOP:
		{
			SchedStop(g_sched);
			break;		
		}
		default:
		{
			break;		
		}
	}

	return (SEC_TILL_RECHECK);
}

/*---------Signal Handler Functions---------*/
static void Sig1Handler(int signum)
{
	if (STOP != g_state)
	{
		g_state = OK;
		printf("app OK\n");
	}
	(void)signum;
}

static void Sig2Handler(int signum)
{
	g_state = STOP;
	printf("app stop\n");
	(void)signum;
}

/*-------------Cleanup Function-------------*/
static void DoNothing(void *param)
{
	(void)param;
}
