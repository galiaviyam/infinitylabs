/****************************************/
/*   Developer: Gali Aviyam				*/
/*   Project: UID						*/				         
/*   Date: 28/12/22						*/
/*   Reviewer: Ariel Kerner				*/
/*										*/
/****************************************/

#include <unistd.h>		/* getpid */
#include <stdatomic.h>	/* atomic_fetch_add */

#include "uid.h"		/* uid header file */

#define ERROR -1

const ilrd_uid_t bad_uid = {0, ERROR, 0};

static size_t GetCount(void);

ilrd_uid_t UIDGenerate(void)
{
	ilrd_uid_t uid = {0};
	
	uid.time = time(NULL);
	if ((time_t)ERROR == uid.time)
	{
		return bad_uid;
	}

	uid.pid = getpid();
	uid.counter = GetCount();
	
	return uid;
}

int UIDIsEqual(ilrd_uid_t handle1, ilrd_uid_t handle2)
{
	return ((handle1.pid == handle2.pid) && 
			(handle1.time == handle2.time) && 
			(handle1.counter == handle2.counter));
}

static size_t GetCount(void)
{
	static atomic_size_t counter = 0;
	
	return (atomic_fetch_add(&counter, 1));
}

