/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   WatchDog                */
/*   Date:      06/03/23                */
/*   Reviewer:  Noy Elankry             */
/*                                      */
/****************************************/

#define _GNU_SOURCE		/* getenv */

#include <pthread.h>	/* pthread_create */
#include <assert.h>		/* assert */
#include <sys/types.h>	/* pid_t */ 
#include <signal.h>		/* sigaction */
#include <fcntl.h>		/* For O_* constants */
#include <sys/stat.h>	/* For mode constants */
#include <unistd.h>		/* execvp */
#include <sys/wait.h>	/* waitpid */
#include <semaphore.h>	/* sem_open */
#include <stdlib.h>		/* getenv */
#include <stdio.h>		/* printf */

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

typedef struct args
{
	scheduler_t *sched;
	char **argv;
}args_t;

/*------------Global Variables------------*/
static args_t g_args = {0};
static pid_t g_proc_pid = 0;
static int g_state = READY;
static pthread_t g_thread = {0};
static sem_t *g_sem_wd = NULL;

/*------------------------Static Function Declarations-----------------------*/
/*------------Set up Functions------------*/
static int SetUp(char **argv);
static int SetUpSched(char **argv);
static int SetUpSignals(void);
static int SetUpSem(void);

/*--------------Task Functions--------------*/
static int SendSigTask(void *param);
static int CheckAppTask(void *param);

/*---------Signal Handler Functions---------*/
static void Sig1Handler(int signum);
static void Sig2Handler(int signum);

/*--------Process and Thread Functions------*/
static int ProcCreate(void);
static void *ThreadFunction(void *arg);

/*-------------Cleanup Function-------------*/
static void DoNothing(void *param);

/*----------------------------Function Definitions---------------------------*/
int WDStart(int argc, char **argv)
{	
	status_t status = SUCCESS;
	
	assert(0 < argc);
	
	status = SetUp(argv);
	if (SUCCESS != status)
	{
		return ERROR;
	}
	
	printf("app pid: %d\n", getpid());
	if (NULL == getenv("ENV_PATH"))
	{
		status = ProcCreate();
		if (ERROR == status)
		{
			return ERROR;
		}
		sem_wait(g_sem_wd);
	}
	else
	{
		g_proc_pid = getppid();
		sem_post(g_sem_wd);
	}	
	
	while (0 != pthread_create(&g_thread, NULL, &ThreadFunction, NULL));
		
	return status;
}


void WDStop(void)
{
	size_t i = 0;
	
	printf("STOP SENT!!!\n");
	
	for (i = 0; i < NUM_OF_RESEND; ++i)
	{
		sleep(1);
		kill(g_proc_pid, SIGUSR2);
		kill(getpid(), SIGUSR2);
	}
	
	unsetenv("ENV_PATH");
	pthread_join(g_thread, NULL);
	sem_close(g_sem_wd);
	sem_unlink("sem_wd");
}

/*------------Set up Functions------------*/
static int SetUp(char **argv)
{
	status_t status = SUCCESS;
	
	g_state = READY;

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
	
	g_args.argv = argv;
	g_args.sched = SchedCreate();
	if (NULL == g_args.sched)
	{
		return ERROR;
	}
	
	uid = SchedAddTask(g_args.sched, &SendSigTask, NULL, &DoNothing, NULL, 
						time(NULL));
	if (UIDIsEqual(bad_uid, uid))
	{
		SchedDestroy(g_args.sched);
		return ERROR;
	}
	
	uid = SchedAddTask(g_args.sched, &CheckAppTask, g_args.sched, &DoNothing, 
						NULL, time(NULL));
	if (UIDIsEqual(bad_uid, uid))
	{
		SchedDestroy(g_args.sched);
		return ERROR;
	}
	
	return SUCCESS;
}

/*--------------Task Functions--------------*/
static int SendSigTask(void *param)
{
	(void)param;
	kill(g_proc_pid, SIGUSR1);
	
	return (SEC_TILL_RESEND);
}

static int CheckAppTask(void *param)
{
	printf("check from app\n");
	switch (g_state)
	{
		case OK:
		{
			g_state = NOT_OK;
			break;		
		}
		case NOT_OK:
		{
			if (ERROR == ProcCreate())
			{
				return ERROR;
			}
			sem_wait(g_sem_wd);
			break;		
		}
		case STOP:
		{
			SchedStop(g_args.sched);
			break;		
		}
		default:
		{
			break;
		}
	}

	(void)param;
	
	return (SEC_TILL_RECHECK);
}

/*---------Signal Handler Functions---------*/
static void Sig1Handler(int signum)
{
	if (STOP != g_state)
	{
		g_state = OK;	
		printf("proc OK\n");
	}
	
	(void)signum;
}

static void Sig2Handler(int signum)
{
	g_state = STOP;
	printf("proc stop\n");
	(void)signum;
}

/*--------Process and Thread Functions------*/
static int ProcCreate(void)
{
	status_t status = SUCCESS;

	g_proc_pid = fork();
	
	if (0 > g_proc_pid)
	{
		status = ERROR;
	}
	else if (0 == g_proc_pid)
	{
		printf("WatchDog Started!\n");
		status = execvp("../watchdog_proc/watchdog_proc.out", g_args.argv);
		if (SUCCESS != status)
		{
			exit(1);
		}
	}
	
	return status;
}

static void *ThreadFunction(void *arg)
{
	SchedRun(g_args.sched);
	
	SchedDestroy(g_args.sched);

	(void)arg;
	
	pthread_exit(NULL);
}

/*-------------Cleanup Function-------------*/
static void DoNothing(void *param)
{
	(void)param;
}

