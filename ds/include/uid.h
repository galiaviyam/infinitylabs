/****************************************/
/*   Developer: Gali Aviyam				*/
/*   Project: UID						*/				         
/*   Date: 28/12/22						*/
/*   Reviewer: Ariel Kerner				*/
/*										*/
/****************************************/

#ifndef __UID_H__
#define __UID_H__

#include <sys/types.h>	/*pid_t*/
#include <time.h> /*time_t*/

/****************************************************************************/
/* A unique identifier (UID) is an identifier that is guaranteed to be 		*/
/* unique among all identifiers used for those objects and for a specific	*/
/* purpose. The concept was formalized early in the development of computer	*/
/* science and information systems.											*/
/****************************************************************************/

/*-----------------------------------------------------------------------------
Description: 
	ilrd_uid_t is a handel to a UID. 
-----------------------------------------------------------------------------*/
typedef struct ilrd_uid ilrd_uid_t;

/*-----------------------------------------------------------------------------
Description: 
	bad_uid is a handel to the bad UID. 
-----------------------------------------------------------------------------*/
extern const ilrd_uid_t bad_uid;

struct ilrd_uid
{
   pid_t pid;
   time_t time;
   size_t counter;
};

/*-----------------------------------------------------------------------------
Description:
	The UIDGenerate function generates a new UID.
	
Return Value:
	The function returns the new UID.
	In case of faliure, the function returns bad_uid.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
ilrd_uid_t UIDGenerate(void);

/*-----------------------------------------------------------------------------
Description:
	The UIDIsEqual function compares between two UIDs.
	
Parameters:
	handle1 - a UID to compare.
	handle2 - a UID to compare with handle1.
	
Return Value:
	The function returns 1 if the UIDs are the same. Otherwise it returns 0.

Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
int UIDIsEqual(ilrd_uid_t handle1, ilrd_uid_t handle2);

#endif /* __UID_H__ */
