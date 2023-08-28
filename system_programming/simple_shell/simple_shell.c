/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Simple Shell            */
/*   Date:      19/02/23                */
/*   Reviewer:  Ariel Biton             */
/*                                      */
/****************************************/

#include <stdio.h>			/* printf */
#include <stdlib.h>			/* exit */
#include <string.h>			/* strcmp */
#include <unistd.h>			/* fork, execvp*/
#include <sys/wait.h>		/* waitpid */
#include <assert.h>			/* assert */

#include "simple_shell.h"	/* simple shell header */

#define MAX_COMMAND_LEN 1024
#define MAX_ARGS 64
#define MAX_ARG_LEN 256

typedef enum status
{
	ERROR = -1,
	SUCCESS,
	EXIT
} status_t;

typedef enum bool
{
	FALSE = 0,
	TRUE
} bool_t;

typedef enum sys_or_fork
{
	SYSTEM = 0,
	FORK
} sys_or_fork_t;

static int GetRunTypeChoice();
static int IsExit(const char *cmd);
static int ParseCommand(char *command, char **args, int max_args);
static int RunCommand(char *command, int is_fork);
static int HandleFork(char **args);
static int HandleSystem(char *command);

int SimpleShell(void)
{
	int status = SUCCESS;
	int choice = 0;
	char command[MAX_COMMAND_LEN] = {0};
	
	choice = GetRunTypeChoice();
	if (FORK != choice && SYSTEM != choice)
	{
		perror("Invalid option\n");
		return ERROR;
	}
	
	while (EXIT != status && ERROR != status)
	{
		printf("Enter command (exit to quit): ");
		
		if(!fgets(command, MAX_COMMAND_LEN, stdin))
		{
			return ERROR;
		}
		
		command[strcspn(command, "\n")] = '\0';
		
		status = RunCommand(command, choice);		
	}

	return status;
}

static int GetRunTypeChoice()
{
	int choice = ERROR;
	
	do
	{
		printf("Please choose 1 for fork() or 0 for system(): ");
		scanf("%d", &choice);
	
		getchar();
	} while (FORK != choice && SYSTEM != choice);
	
	return choice;
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

static int RunCommand(char *command, int is_fork)
{
	int status = SUCCESS;
	char* args[MAX_ARGS];
	int num_of_args = 0;
	
	if (is_fork)
	{
		num_of_args = ParseCommand(command, args, MAX_ARGS);
		
		if (0 < num_of_args)
		{
			status = HandleFork(args);
		}
	}
	else
	{
		status = HandleSystem(command);
	}
	
	return status;
}

static int HandleFork(char **args)
{
	int status = 0;
	int pid = 0;
	
	if (IsExit(args[0]))
	{
		return EXIT;
	}
	
	pid = fork();

	if (0 == pid)
	{
		status = execvp(args[0], args);
		if (ERROR == status)
		{
			perror("Failed to execute command.\n");
			exit(status);
		}
	}
	else if (0 < pid)
	{
		do
		{
			if (ERROR == waitpid(pid, &status, 0))
			{
				perror("Failed to wait.\n");
			}
			
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	else
	{
		perror("Fork() failed.\n");
		
		return ERROR;
	}

	return WEXITSTATUS(status);
}

static int HandleSystem(char *command)
{
	int status = SUCCESS;
	
	assert(NULL != command);

	if (IsExit(command))
	{
		return EXIT;
	}
	
	status = system(command);

	if (ERROR == status)
	{
		perror("Failed to create child process.\n");
	}
	
	if (!WIFEXITED(status))
	{
		return ERROR;
	}
	
	return WEXITSTATUS(status);
}

static int IsExit(const char *cmd)
{
	assert(NULL != cmd);
	
	return (0 == strcmp(cmd, "exit"));
}
