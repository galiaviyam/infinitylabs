/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Scheduler				*/
/*   Date:		02/01/23				*/
/*	 Reviewer:	Noy Elankry				*/
/*										*/
/****************************************/

#include <stdio.h>			/* printf */
#include <stdbool.h>		/* bool */
#include <assert.h>			/* assert */
#include <string.h>			/* strstr */

#include "scheduler.h" /* scheduler header file */

typedef enum
{
	SUCCESS = 0,
	FAIL
}status_t;

typedef struct remove_task
{
	scheduler_t *sched;
	ilrd_uid_t uid;
} remove_task_t;

static void TestNumResultEqual(size_t result, size_t expected_result);
static void TestResultNotNull(void *result);
static void TestBoolResult(int result);
static void TestStatusResult(int result);
static void TestSchedCreate(void);
static void IntegrationTest(void);
static void TestSchedSize(scheduler_t *sched, size_t num_of_tasks);
static void TestSchedClearTasks(scheduler_t *sched);
static void TestSchedRemoveTask(scheduler_t *sched, ilrd_uid_t uid, 
								size_t num_of_tasks);
static void TestSchedRun(void);
static void TestTaskRemoveItself(void);
static void TestDynamicStop(void);
static int DoAction(void *param);
static void DoNothing(void *param);
static int RemoveSelf(void *param);
static int DoActionWriteToFile(void *param);
static int DoActionStopDynamic(void *param);

int main(void)
{
	TestSchedCreate();
	IntegrationTest();
	TestSchedRun();
	TestTaskRemoveItself();
	TestDynamicStop();
	
	return SUCCESS;
}

static void TestSchedCreate(void)
{
	scheduler_t *sched = SchedCreate();
	
	printf("create: ");
	TestResultNotNull(sched);
	
	printf("is empty: ");
	TestBoolResult(SchedIsEmpty(sched));
	printf("\n");
	
	SchedDestroy(sched);	
}

static void IntegrationTest(void)
{
	scheduler_t *sched = SchedCreate();
	size_t i = 0;
	time_t run_time = time(NULL);
	int action_param = 1;
	int clean_up_param = 1;
	ilrd_uid_t uid = {0};
	
	printf("**********Integration Test**********\n");
	printf("-----SchedAddTask-----\n");
	for (i = 0; i < 3; ++i)
	{
		printf("test %lu: ", i + 1);
		uid = SchedAddTask(sched, &DoAction, &action_param, &DoNothing,
									 &clean_up_param, run_time);
		TestBoolResult(!UIDIsEqual(bad_uid, uid));
		run_time += 5;
	}
	
	TestSchedSize(sched, 3);
	TestSchedRemoveTask(sched, uid, 3);
	TestSchedClearTasks(sched);
	printf("\n");
	SchedDestroy(sched);	
}

static void TestSchedSize(scheduler_t *sched, size_t num_of_tasks)
{
	printf("\nSchedSize: ");
	TestNumResultEqual(SchedSize(sched), num_of_tasks);
}

static void TestSchedClearTasks(scheduler_t *sched)
{
	printf("\nSchedClearTasks: ");
	SchedClearTasks(sched);
	TestBoolResult(SchedIsEmpty(sched));
}

static void TestSchedRemoveTask(scheduler_t *sched, ilrd_uid_t uid, 
							size_t num_of_tasks)
{
	printf("\nSchedRemoveTask: ");
	TestBoolResult(SchedRemoveTask(sched, uid));
						
	TestNumResultEqual(SchedSize(sched), num_of_tasks - 1);
}

static void TestSchedRun(void)
{
	scheduler_t *sched = SchedCreate();
	int param1 = 1;
	int param2 = 4;

	SchedAddTask(sched, &DoAction, &param1, &DoNothing, &param1, time(NULL) + 1);

	SchedAddTask(sched, &DoAction, &param2, &DoNothing, &param2, time(NULL) + 2);
													
	SchedAddTask(sched, &DoAction, &param1, &DoNothing, &param1, time(NULL) + 3);

	printf("\n-------SchedRun-------\n");
	TestStatusResult(SchedRun(sched));


	TestBoolResult(SchedIsEmpty(sched));
	printf("\n");
	
	SchedDestroy(sched);
}

static void TestTaskRemoveItself(void)
{
	remove_task_t remove_struct = {0};
	int status = FAIL;
	time_t run_time = time(NULL);
	scheduler_t *sched = NULL;
	
	sched = SchedCreate();
	remove_struct.sched = sched;
	remove_struct.uid = SchedAddTask(sched, &RemoveSelf, &remove_struct, 
							&DoNothing, &remove_struct, run_time);
	
	if (SUCCESS == SchedRun(remove_struct.sched) && SchedIsEmpty(remove_struct.sched))
	{
		status = SUCCESS;
	}
	printf("\nself remove: ");
	TestStatusResult(status);
	SchedDestroy(remove_struct.sched);
}

static void TestDynamicStop(void)
{
	scheduler_t *sched = NULL;
	int param = 2;
	time_t run1 = time(NULL);
	time_t run2 = time(NULL) + 2;
	time_t run3 = time(NULL) + 30;

	sched = SchedCreate();
	
	SchedAddTask(sched, &DoActionStopDynamic, (void *)sched, &DoNothing, 
    			&param, run1);
	
	SchedAddTask(sched, &DoAction, &param, &DoNothing, 
				&param, run3);
	
	SchedAddTask(sched, &DoActionWriteToFile, (void *)sched, &DoNothing, 
				&param, run2);			
	
	printf("\n-------Dynamic Stop-------\n");
	TestStatusResult(SchedRun(sched));

	TestBoolResult(!SchedIsEmpty(sched));
	SchedDestroy(sched);

	remove("stop.txt");
}

/**************************test helper functions*************************/
static int DoAction(void *param)
{
	if((*(int *)param) > 0)
	{
		--*(int *)param;
	}
	printf("run again in %d seconds\n", *(int *)param);
	
	return (*(int *)param);
}

static void DoNothing(void *param)
{
	(void)param;
}

static int RemoveSelf(void *param)
{	
	remove_task_t *remove_struct = NULL;
	
	assert(param);
	
	remove_struct = (remove_task_t *)param;
	SchedRemoveTask(remove_struct->sched, remove_struct->uid);
	
	return 0;
}

static int DoActionStopDynamic(void *param)
{
	FILE *fp = NULL;
	char line[80];
	
	assert(NULL != param);

	fp = fopen("stop.txt", "a+");
	if (NULL == fp)
	{
		printf("ERROR!\n");
		return -1;
	}

	while (fgets(line, 80, fp))
	{
		if (strstr(line, "stop"))
		{
			SchedStop((scheduler_t *)param);
			printf("Stopped\n");
		}
		else
		{		
			printf("did not stop yet\n");
		}
	}
	
	fclose(fp);
	fp = NULL;
    
    return 1;
}

static int DoActionWriteToFile(void *param)
{
	FILE *fp = NULL;
	
	assert(NULL != param);
	
	fp = fopen("stop.txt", "a");
	if (NULL == fp)
	{
		return FAIL;
	}
	
	fputs("stop\n", fp);
	printf("written stop to file\n");
	
	if(0 != fclose(fp))
	{
		return FAIL;
	}
	fp = NULL;
    
    return 5;
}

/**************************test utility functions************************/
static void TestStatusResult(int result)
{
	if (result == SUCCESS)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}

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
