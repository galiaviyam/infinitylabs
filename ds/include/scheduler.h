/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Scheduler				*/
/*   Date:		02/01/23				*/
/*	 Reviewer:	Noy Elankry				*/
/*										*/
/****************************************/

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <stddef.h>		/*size_t*/

#include "uid.h"        /* ilrd_uid_t */

/*----------------------------------------------------------------------------
	scheduling is the action of assigning resources to perform tasks.
	The tasks arr added to the schedule according to priority order 
	determined by to the execution time of each task.

MAIN FUNCTIONS:
	* SchedAddTask.
	* SchedRemoveTask.
	* SchedStop. 
	* SchedRun.

ADDITIONAL FUNCTIONS:
	* SchedIsEmpty.
	* SchedSize.
	* SchedClearTasks.
	
NOTE: bad_uid means invalid UID. read more in the UID documentation.
----------------------------------------------------------------------------*/

typedef struct scheduler scheduler_t;

/*-----------------------------------------------------------------------------
Description:
	The function prototype for the main functionality of a task.
	
Parameters:
	param - A pointer to paramter to do the action with.
	
Return Value:
	The function returns zero when success with no need to rerun,
	the number of seconds needed to rerun the task, or in case of a failiure, 
	the function returns a negative integer.
-----------------------------------------------------------------------------*/
typedef int(*sched_action_func_t)(void *param);

/*-----------------------------------------------------------------------------
Description:
	The function prototype for the cleanup function to run on a task when 
	calling SchedRemoveTask.
	
Parameters:
	param - Pointer to paramter to cleanup with.
-----------------------------------------------------------------------------*/
typedef void(*sched_cleanup_func_t)(void *param);  

/*-----------------------------------------------------------------------------
Description:
	The SchedCreate function allocates a new schedule.  
	resources for the schedule are dynamically allocated, and must be destroyed 
	with SchedDestroy.
	
Return Value:
	The function returns a handle to the new schedule.
	In case of a faliure, the function returns NULL.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
scheduler_t *SchedCreate(void);

/*-----------------------------------------------------------------------------
Description:
	The SchedDestroy function destroys all schedule's allocated resources. 
	Note! Passing a NULL as the passed argument sched will cause an undefined 
	behavior.

Parameters:
	sched - A pointer to the schedule to be destroyed.

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
void SchedDestroy(scheduler_t *sched);

/*-----------------------------------------------------------------------------
Description: 
	The SchedAddTask function creates a task and inserts it to the schedule.
	
Parameters:
	sched - A pointer to the schedule to add the task to.
	action_func - A pointer to an action function of type task_action_func_t.
	action_param - A pointer to paramter for action_func arguments.
	cleanup_func - A pointer to cleanup function of type task_cleanup_func_t,
					to be run after the task has finished executing.
	cleanup_param - A pointer to cleanup_func arguments.
	run_time - the time in time_t for when the task should be executed.
	
Return Value:
	The function returns the uid of the task.
	In case of an error,  the function returns a bad_uid.

Complexity:
	time: o(n), space: o(1) 
-----------------------------------------------------------------------------*/
ilrd_uid_t SchedAddTask(scheduler_t *sched, sched_action_func_t action_func, 
						void *action_param, sched_cleanup_func_t cleanup_func, 
						void *cleanup_param, time_t run_time);

/*-----------------------------------------------------------------------------
Description: 
	The SchedRemoveTask function removes the task from the schedule and releases 
	all resources allocated by the SchedAddTask function.
	If the function requires special clean up operations - it is needed to 
	include the relevant cleanup_func when calling SchedAddTask.
	
Parameters:
	sched - A pointer to the schedule to remove the task from.
	
Return Value:
	The function returns a boolean integer:
	1 - if the task is found and removed,
	0 - if the task is not found.
	
Complexity:
	time: o(n), space: o(1) 
-----------------------------------------------------------------------------*/
int SchedRemoveTask(scheduler_t *sched, ilrd_uid_t uid);

/*-----------------------------------------------------------------------------
Description: 
	The SchedRun function runs all the tasks in the schedule.
	For each task, the sched_action_func_t function is executed, and inserted
	back to the schedule with the new run_time.
	After it finished running, the task is removed from the schedule.
	
Parameters:
	sched - A pointer to the schedule to remove the task from.
	
Return Value:
	The function returns a status code:
	0 - if all tasks succeded,
	otherwise - at least one task failed
	
Complexity:
	time: o(n), space: o(1) 
-----------------------------------------------------------------------------*/
int SchedRun(scheduler_t *sched);

/*---------------------------------------------------------------------------
Description:
	The SchedStop function notifies the schedule to stop running.
	Note! Passing a NULL as the passed argument sched will cause an undefined 
	behavior.

Parameters:
	sched - A pointer to the schedule to be cleared.
	
Complexity: 
	time: O(1)  / space: O(1) 
---------------------------------------------------------------------------*/ 
void SchedStop(scheduler_t *sched); 

/*-----------------------------------------------------------------------------
Description:
	The SchedIsEmpty function checks whether the schedule is empty.
	Note! Passing a NULL as the passed argument sched will cause an undefined 
	behavior.
	
Parameters:
	sched - A pointer to the schedule.
	
Return Value:
	The function returns 1 if the schedule is empty. 
	Otherwise it returns 0.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
int SchedIsEmpty(const scheduler_t *sched);

/*-----------------------------------------------------------------------------
Description: 
	The SchedSize function counts the tasks in the schedule. 
	Note! Passing a NULL as the passed argument sched will cause an undefined 
	behavior.

Parameters:
	sched - A pointer to the schedule.
	
Return Value:
	The function returns the number of tasks in the schedule. 

Complexity: 
	time: O(n)  / space: O(1) 
-----------------------------------------------------------------------------*/
size_t SchedSize(const scheduler_t *sched);

/*---------------------------------------------------------------------------
Description:
	The SchedClearTasks function empties the schedule of tasks.
	Note! Passing a NULL as the passed argument sched will cause an undefined 
	behavior.

Parameters:
	sched - A pointer to the schedule to be cleared.
	
Complexity: 
	time: O(n)  / space: O(1) 
---------------------------------------------------------------------------*/ 
void SchedClearTasks(scheduler_t *sched);


#endif 	/* __SCHEDULER_H__ */
