/****************************************/
/*										*/   
/*	Developer:	Gali Aviyam				*/
/*	Project:	task					*/
/*	Date:		30/12/22				*/
/*	Reviewer:	Moriah					*/
/*										*/
/****************************************/

#include <assert.h>	/* assert */
#include <stdlib.h> /* malloc */

#include "task.h" /* task header file */

struct task 
{
	task_action_func_t action_func;
	void *action_param;
	task_cleanup_func_t cleanup_func;
	void *cleanup_param;
	time_t run_time;
	ilrd_uid_t uid;
};

static int IsBadUID(ilrd_uid_t uid);
static void TaskInit(task_action_func_t action_func, void *action_param,
                     task_cleanup_func_t cleanup_func, void *cleanup_param,
                     time_t run_time, task_t *task);

/*--------------------------------TaskCreate---------------------------------*/
task_t *TaskCreate(task_action_func_t action_func, void *action_param,
                   task_cleanup_func_t cleanup_func, void *cleanup_param,
                   time_t run_time)
{
	task_t *task = NULL;
	
	assert(NULL != action_func);
	assert(NULL != cleanup_func);
	assert(-1 != run_time);
	
	task = (task_t *)malloc(sizeof(task_t));
	if (NULL == task)
	{
		return NULL; 
	}
	
	task->uid = UIDGenerate();
	if (IsBadUID(task->uid))
	{
		free(task);
		task = NULL;
		
		return NULL;
	}
	
	TaskInit(action_func, action_param, cleanup_func, cleanup_param, run_time, 
			task);

	return task;
}

/*--------------------------------TaskDestroy--------------------------------*/
void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	task->cleanup_func(task->cleanup_param);
	
	free(task);
	task = NULL;
}

/*------------------------------TaskGetRunTime-------------------------------*/
time_t TaskGetRunTime(const task_t *task)
{
	assert(NULL != task);

	return (task->run_time);
}

/*------------------------------TaskSetRunTime-------------------------------*/
void TaskSetRunTime(task_t *task, time_t run_time)
{
	assert(NULL != task);
	
	task->run_time = run_time;
}

/*------------------------------TaskExecuteFunc------------------------------*/
int TaskExecuteFunc(const task_t *task)
{
	assert(NULL != task);
	
	return (task->action_func(task->action_param));
}

/*--------------------------------TaskGetUID---------------------------------*/
ilrd_uid_t TaskGetUID(const task_t *task)
{
	assert(NULL != task);
	
	return (task->uid);
}

/*****************************Helper Functions********************************/

static int IsBadUID(ilrd_uid_t uid)
{
	return (UIDIsEqual(bad_uid, uid));
}

static void TaskInit(task_action_func_t action_func, void *action_param,
                     task_cleanup_func_t cleanup_func, void *cleanup_param,
                     time_t run_time, task_t *task)
{
	assert(NULL != action_func);
	assert(NULL != cleanup_func);
	assert(NULL != task);
	
	task->action_func = action_func;
	task->action_param = action_param;
	task->cleanup_func = cleanup_func;
	task->cleanup_param = cleanup_param;
	task->run_time = run_time;
}

