/****************************************/
/*   Developer: Gali Aviyam				*/
/*   Project: UID						*/				         
/*   Date: 28/12/22						*/
/*   Reviewer: Ariel Kerner				*/
/*										*/
/****************************************/

#include <stdio.h>		/* printf */
#include <pthread.h>	/* pthread_create */

#include "uid.h"		/* uid header file */

#define SIZE (1000)

static void UIDGenerateTest(void);
static void UIDIsEqualTest(void);
static void ThreadSafeTest(void);
static void *ThreadGenerateTest(void *arg);

int main(void)
{
	UIDGenerateTest();
	UIDIsEqualTest();
	ThreadSafeTest();
	
	return 0;
}

static void UIDGenerateTest(void)
{
	ilrd_uid_t my_uid = UIDGenerate();
	
	printf("************UIDGenerate**************\n");
	if (!UIDIsEqual(my_uid, bad_uid))
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED\n");
	}
	
}

static void UIDIsEqualTest(void)
{
	ilrd_uid_t my_uid = UIDGenerate();
	ilrd_uid_t diff_uid = UIDGenerate();
	ilrd_uid_t equal_uid = my_uid;
	
	printf("************UIDIsEqual**************\n");
	if (!UIDIsEqual(my_uid, diff_uid))
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED\n");
	}
	
	if (UIDIsEqual(my_uid, equal_uid))
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED\n");
	}
}

static void ThreadSafeTest(void)
{
	pthread_t threads[SIZE] = {0};
	
	size_t i = 0;
	
	for (i = 0; i < SIZE; ++i)
	{
		while (0 != pthread_create(&threads[i], NULL, &ThreadGenerateTest, NULL));
	}
	
	for (i = 0; i < SIZE; ++i)
	{		
		pthread_join(threads[i], NULL);
	}
}

static void *ThreadGenerateTest(void *arg)
{
	ilrd_uid_t my_uid = UIDGenerate();
	
	printf("%lu\n", my_uid.counter);	
	
	return arg;
}
