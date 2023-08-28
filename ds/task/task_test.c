/****************************************/
/*										*/   
/*	Developer:	Gali Aviyam				*/
/*	Project:	task					*/
/*	Date:		30/12/22				*/
/*	Reviewer:	Moriah					*/
/*										*/
/****************************************/

#include <stdio.h>			/* printf */
#include <stdbool.h>		/* bool */
#include <assert.h>			/* assert */

#include "task.h" /* task header file */


static void TestNumResultEqual(size_t result, size_t expected_result);
static void TestResultNotNull(void *result);
static void TestBoolResult(int result);
int DoAction(void *param);
void CleanUp(void *param);
static void TestTaskCreate(void);
static void TestTaskGetRunTime(void);
static void TestTaskSetRunTime(void);
static void TestTaskGetUID(void);
static void TestTaskExecuteFunc(void);

enum status
{
	SUCCESS = 0,
	FAIL = 1
};

int main(void)
{
	TestTaskCreate();
	TestTaskGetRunTime();
	TestTaskSetRunTime();
	TestTaskGetUID();
	TestTaskExecuteFunc();
	return SUCCESS;
}

static void TestTaskCreate(void)
{
	task_t *task = NULL;
	time_t run_time = 555;
	int action_param = 10;
	int clean_up_param = 10;
	
	task = TaskCreate(&DoAction, &action_param, &CleanUp, &clean_up_param, 
	run_time);
	
	printf("TaskCreate: ");
	TestResultNotNull(task);

	TaskDestroy(task);
	printf("\n");	
}

static void TestTaskGetRunTime(void)
{
	task_t *task = NULL;
	time_t run_time = 555;
	int action_param = 10;
	int clean_up_param = 10;
	
	task = TaskCreate(&DoAction, &action_param, &CleanUp, &clean_up_param, 
	run_time);

	printf("TaskGetRunTime: ");
	TestNumResultEqual(TaskGetRunTime(task), 555);
	
	TaskDestroy(task);
	printf("\n");
}

static void TestTaskSetRunTime(void)
{
	task_t *task = NULL;
	time_t run_time = 555;
	int action_param = 10;
	int clean_up_param = 10;
	
	task = TaskCreate(&DoAction, &action_param, &CleanUp, &clean_up_param, 
	run_time);

	printf("TaskSetRunTime: ");
	TaskSetRunTime(task, 666);
	TestNumResultEqual(TaskGetRunTime(task), 666);
	
	TaskDestroy(task);
	printf("\n");
}

static void TestTaskGetUID(void)
{
	task_t *task = NULL;
	time_t run_time = 555;
	int action_param = 10;
	int clean_up_param = 10;
	
	task = TaskCreate(&DoAction, &action_param, &CleanUp, &clean_up_param, 
	run_time);

	printf("TaskGetUID: ");
	TestBoolResult(!UIDIsEqual(bad_uid, TaskGetUID(task)));
	
	TaskDestroy(task);
	printf("\n");
}

static void TestTaskExecuteFunc(void)
{
	task_t *task = NULL;
	time_t run_time = 555;
	int action_param = 10;
	int clean_up_param = 10;
	
	task = TaskCreate(&DoAction, &action_param, &CleanUp, &clean_up_param, 
	run_time);

	printf("TaskExecuteFunc: ");
	TestNumResultEqual(TaskExecuteFunc(task), 11);
	
	TaskDestroy(task);
	printf("\n");
}

/**************************test helper functions*************************/
int DoAction(void *param)
{
	return ++(*(int *)param);
}

void CleanUp(void *param)
{
	*(int *)param = 0;
}

/**************************test utility functions************************/
static void TestBoolResult(int result)
{
	if (result)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}

static void TestNumResultEqual(size_t result, size_t expected_result)
{
	if (result == expected_result)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}

static void TestResultNotNull(void *result)
{
	if (NULL != result)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}
