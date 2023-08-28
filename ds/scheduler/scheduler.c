/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Scheduler				*/
/*   Date:		02/01/23				*/
/*	 Reviewer:	Noy Elankry				*/
/*										*/
/****************************************/

#include <stdlib.h>			/* malloc */
#include <assert.h>			/* assert */
#include <unistd.h>			/* sleep */

#include "task.h"			/* task functions */
#include "Heap_PQ.h"	/* priority queue functions */
#include "scheduler.h"		/* scheduler header file */

#define TIME_ERROR -1

typedef enum
{
	SUCCESS = 0,
	FAIL
}status_t;

typedef enum
{
	TRUE = 1,
	FALSE = 0
}bool_t;

struct scheduler
{
	ilrd_pq_t *pq;
	int is_stop;
};

static ilrd_pq_t *SchedToPQ(const scheduler_t *sched);
static int CmpRunTime(const void *run_time1, const void *run_time2);
static int IsMatchUID(const void *task, void *uid);
static void WaitUntilRunTime(task_t *task);

/*--------------------------------SchedCreate--------------------------------*/
scheduler_t *SchedCreate(void)
{
	scheduler_t *sched = NULL;
	
	sched = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (NULL == sched)
	{
		return NULL;
	}
	
	sched->pq = PQCreate(&CmpRunTime);
	if (NULL == sched->pq)
	{
		free(sched);
		sched = NULL;
		
		return NULL;
	}
	
	sched->is_stop = FALSE;
	
	return sched;
}

/*--------------------------------SchedDestroy-------------------------------*/
void SchedDestroy(scheduler_t *sched)
{
	assert (NULL != sched);
	
	SchedClearTasks(sched);
	
	PQDestroy(SchedToPQ(sched));
	
	free(sched);
	sched = NULL;
}

/*--------------------------------SchedAddTask-------------------------------*/
ilrd_uid_t SchedAddTask(scheduler_t *sched, sched_action_func_t action_func, 
						void *action_param, sched_cleanup_func_t cleanup_func, 
						void *cleanup_param, time_t run_time)
{
	task_t *new_task = NULL;
	int status = SUCCESS;
	
	assert(NULL != sched);
	assert(NULL != action_func);
	assert(NULL != cleanup_func);
	assert(TIME_ERROR != run_time);
	
	new_task = TaskCreate(action_func, action_param, 
						  cleanup_func, cleanup_param, run_time);
	if (NULL == new_task)
	{
		return bad_uid;
	}
	
	status = PQEnqueue(SchedToPQ(sched), (void *)new_task);
	if (FAIL == status)
	{
		TaskDestroy(new_task);
		
		return bad_uid;
	}
	
	return (TaskGetUID(new_task));
}

/*-------------------------------SchedRemoveTask-----------------------------*/
int SchedRemoveTask(scheduler_t *sched, ilrd_uid_t uid)
{
	task_t *task = NULL;
	int is_found = FALSE;
	
	assert(NULL != sched);
	assert(!UIDIsEqual(bad_uid, uid));
	
	task = (task_t *)PQErase(SchedToPQ(sched), &uid, &IsMatchUID);
	if (NULL != task)
	{
		TaskDestroy(task);
		is_found = TRUE;
	}
	
	return is_found;
}

/*----------------------------------SchedRun---------------------------------*/
int SchedRun(scheduler_t *sched)
{
	int run_status = SUCCESS;
	int task_status = SUCCESS;
	task_t *task = NULL;
	ilrd_uid_t last_uid = {0};
	int removed_itself = FALSE;
	
	assert(NULL != sched);

	sched->is_stop = FALSE;
	
	while (FALSE == sched->is_stop && (!SchedIsEmpty(sched)))
	{
		task = (task_t *)PQPeek(SchedToPQ(sched));
		last_uid = TaskGetUID(task);
		
		WaitUntilRunTime(task);
		
		task_status = TaskExecuteFunc(task);
		
		removed_itself = (NULL == (PQErase(SchedToPQ(sched), &last_uid, 
											&IsMatchUID)));
	 	if (0 < task_status)
		{
			TaskSetRunTime(task, (time(NULL) + task_status));
			if (SUCCESS != PQEnqueue(SchedToPQ(sched), task))
			{
				TaskDestroy(task);
				run_status = FAIL;
			}
		}
		else 
		{
			if (0 > task_status)
			{
				run_status = FAIL;
			}
			
			if (!removed_itself)
			{			
				TaskDestroy(task);
			}
		}
	}
	
	return run_status;
}

/*---------------------------------SchedStop---------------------------------*/
void SchedStop(scheduler_t *sched)
{
	assert (NULL != sched);
	
	sched->is_stop = TRUE;
}

/*--------------------------------SchedIsEmpty-------------------------------*/
int SchedIsEmpty(const scheduler_t *sched)
{
	assert (NULL != sched);
	
	return (PQIsEmpty(SchedToPQ(sched)));
}

/*---------------------------------SchedSize---------------------------------*/
size_t SchedSize(const scheduler_t *sched)
{
	assert (NULL != sched);
	
	return (PQSize(SchedToPQ(sched)));
}

/*------------------------------SchedClearTasks------------------------------*/
void SchedClearTasks(scheduler_t *sched)
{
	assert(NULL != sched);
	
	while (!SchedIsEmpty(sched)) 
	{
		TaskDestroy(PQDequeue(SchedToPQ(sched)));
	}
}

/*****************************Helper Functions********************************/
static ilrd_pq_t *SchedToPQ(const scheduler_t *sched)
{
	assert (NULL != sched);
	
	return (sched->pq);
}

static int CmpRunTime(const void *run_time1, const void *run_time2)
{
	time_t time1 = 0;
	time_t time2 = 0;
	
	assert(NULL != run_time1);
	assert(NULL != run_time2);
	
	time1 = TaskGetRunTime((const task_t *)run_time1);
	time2 = TaskGetRunTime((const task_t *)run_time2);

	return (time1 - time2);
}

static int IsMatchUID(const void *task, void *uid)
{
	assert(NULL != task);
	assert(NULL != uid);
	
	return UIDIsEqual(TaskGetUID((const task_t *)task), *(ilrd_uid_t *)uid);
}

static void WaitUntilRunTime(task_t *task)
{
	time_t wait = 0;
		
	wait = TaskGetRunTime(task) - time(NULL);
	while (0 < wait)
	{
		wait = sleep(wait);
	}
}
