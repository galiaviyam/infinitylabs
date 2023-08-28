/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Semaphore               */
/*   Date:      27/02/23                */
/*   Reviewer:  Noy                     */
/*                                      */
/****************************************/

#include <stdio.h>		/* printf */
#include <stdlib.h>		/* atoi */
#include <string.h>		/* strcspn */
#include <assert.h>		/* assert */
#include <fcntl.h>		/* For O_* constants */
#include <sys/stat.h>	/* For mode constants */
#include <semaphore.h>	/* sem_open */
#include <ctype.h>		/* toupper */


#define MAX_COMMAND_LEN 1024
#define MAX_ARGS 4

typedef enum status
{
	ERROR = -1,
	SUCCESS
} status_t;

static int RunCommand(char *command, sem_t *sem);
static int SemGetValue(sem_t *sem);
static int ParseCommand(char *command, char **args, int max_args);
static int SemIncrement(sem_t *sem, const int num);
static int SemDecrement(sem_t *sem, const int num);


int main(const int argc, const char **argv)
{
	sem_t *sem = NULL;
	char command[MAX_COMMAND_LEN] = {0};
	int status = SUCCESS;
	
	assert(NULL != argv);
	assert(1 < argc);
	
	sem = sem_open(argv[1], O_CREAT, S_IRWXU, 5);
	if (SEM_FAILED == sem)
	{
		printf("sem_open failed\n");
		return ERROR;
	}
	
	while ('X' != *command)
	{
		printf("Choose an option:\n\
		D <number> (Decrement)\n\
		I <number> (Increment)\n\
		V (view the value)\n\
		X (exit):\n");
		
		if(!fgets(command, MAX_COMMAND_LEN, stdin))
		{
			printf("fgets failed\n");
			return ERROR;
		}
		
		command[strcspn(command, "\n")] = '\0';
		
		status = RunCommand(command, sem);		
	}
	
	return status;
}

static int RunCommand(char *command, sem_t *sem)
{
	int status = SUCCESS;
	char* args[MAX_ARGS];
	int num_of_args = 0;
	
	num_of_args = ParseCommand(command, args, MAX_ARGS);
	*command = toupper(*command);
	
	if ('V' == *command)
	{
		status = SemGetValue(sem);
	}
	else if ('I' == *command && 1 < num_of_args)
	{
		status = SemIncrement(sem, atoi(args[1]));
	}
	else if ('D' == *command && 1 < num_of_args)
	{
		status = SemDecrement(sem, atoi(args[1]));
	}
	
	return status;
}

static int ParseCommand(char *command, char **args, int max_args)
{
	char* arg = NULL;
	int num_of_args = 0;
	
	assert(NULL != command);
	assert(NULL != args);
	
	arg = strtok(command, " ");
	
	while (arg != NULL && num_of_args < max_args)
	{
		args[num_of_args] = arg;
		arg = strtok(NULL, " ");
		++num_of_args;
	}
	
	args[num_of_args] = NULL;
	
	return num_of_args;
}

static int SemIncrement(sem_t *sem, int num)
{
	int status = SUCCESS;
	int i = 0;
	
	for (i = 0; i < num && SUCCESS == status; ++i)
	{
		status = sem_post(sem);
	}
		
	return status;
}

static int SemDecrement(sem_t *sem, int num)
{
	int status = SUCCESS;
	int i = 0;
	
	for (i = 0; i < num && SUCCESS == status; ++i)
	{
		status = sem_wait(sem);
	}
		
	return status;
}

static int SemGetValue(sem_t *sem)
{
	int status = SUCCESS;
	int sval = 0;
	
	status = sem_getvalue(sem, &sval);
	
	printf("The Value Is: %d\n", sval);
	
	return status;
}
