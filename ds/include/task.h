/****************************************/
/*										*/   
/*	Developer:	Gali Aviyam				*/
/*	Project:	task					*/
/*	Date:		30/12/22				*/
/*	Reviewer:	Moriah					*/
/*										*/
/****************************************/

#ifndef __TASK_H__
#define __TASK_H__

#include <time.h> /* time_t */

#include "uid.h" /* ilrd_uid_t */

/*------------------------------------------------------------------------------
	A task is a unit of execution or a process.
	Ins this API, the task is a data type to handel task.
	The main functionalities are TaskExecuteFunc, as well as TaskCreate and 
	TaskDestroy.
------------------------------------------------------------------------------*/

typedef struct task task_t;

/*-----------------------------------------------------------------------------
Description:
	The function prototype for the main functionality of the task.
	
Parameters:
	param - A pointer to paramter to do the action with.
	
Return Value:
	The function returns the number of times needed to run TaskExecuteFunc again.
	In case of a failiure, the function returns a negative integer.
-----------------------------------------------------------------------------*/
typedef int(*task_action_func_t)(void *param);

/*-----------------------------------------------------------------------------
Description:
	The function prototype for the cleanup function to run when calling 
	TaskDestroy.
	
Parameters:
	param - Pointer to paramter to cleanup with.
-----------------------------------------------------------------------------*/
typedef void(*task_cleanup_func_t)(void *param);  


/*-----------------------------------------------------------------------------
Description: 
	The TaskCreate function creates a task of type task_t.
	The reasources for the task is dynamically allocated, and can be freed with 
	the TaskDestroy function.
	
Parameters:
	action_func - A pointer to an action function of type task_action_func_t.
	action_param - A pointer to paramter for action_func arguments.
	cleanup_func - A pointer to cleanup function of type task_cleanup_func_t,
					to be run after the task has finished executing.
	cleanup_param - A pointer to cleanup_func arguments.
	run_time - the time in time_t for when the task should be executed.
	
Return Value:
	The function returns a pointer to a task.
	In case of an error,  the function returns NULL.

Complexity:
	time: o(1), space: o(1) 
-----------------------------------------------------------------------------*/
task_t *TaskCreate(task_action_func_t action_func, void *action_param,
                   task_cleanup_func_t cleanup_func, void *cleanup_param,
                   time_t run_time);

/*-----------------------------------------------------------------------------
Description: 
	The TaskDestroy function releases all resources allocated for the task by 
	the TaskCreate function.
	If the function requires special clean up operations - it is needed to 
	include the relevant cleanup_func when calling TaskCreate.
	
Parameters:
	task - a pointer to a task of type task_t.
	
Complexity:
	time: o(1), space: o(1) 
-----------------------------------------------------------------------------*/
void TaskDestroy(task_t *task);

/*-----------------------------------------------------------------------------
Description: 
	The TaskGetRunTime function gets the run time of the given task.
	
Parameters:
	task - a pointer to a task of type task_t.
	
Return Value:
	The function returns the runtime of the task of type time_t.
	
Complexity:
	time: o(1), space: o(1) 
-----------------------------------------------------------------------------*/
time_t TaskGetRunTime(const task_t *task);

/*-----------------------------------------------------------------------------
Description: 
	The TaskSetRunTime function sets the run time of the given task.
	
Parameters:
	task - a pointer to a task of type task_t.
	run_time - the desired runtime of the task of type time_t.
	
Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
void TaskSetRunTime(task_t *task, time_t run_time);

/*-----------------------------------------------------------------------------
Description: 
	The TaskExecuteFunc function executes the given task.
	
Parameters:
	task - a pointer to a task of type task_t.
	
Return Value:
	The function returns a status code:
	0 or positive - success
	negative - failiure.
-----------------------------------------------------------------------------*/
int TaskExecuteFunc(const task_t *task);

/*-----------------------------------------------------------------------------
Description: 
	The TaskGetUID function returns the Unique ID of the task.

Parameters:
	task - a pointer to a task of type task_t.

Return Value:
	The function returns the ilrd_uid_t Unique ID of the task.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
ilrd_uid_t TaskGetUID(const task_t *task);

#endif /* __TASK_H__ */
