/*********************************************/
/*                                           */   
/*   Developer: Gali Aviyam                  */
/*   Project:   Multithreaded memory mapping */
/*   Date:      02/03/23                     */
/*   Reviewer:  Shauli                       */
/*                                           */
/*********************************************/

#include <pthread.h>	/* pthread_create */
#include <stdio.h>		/* printf */
#include <stdlib.h>		/* malloc */
#include <assert.h>		/* assert */
#include <string.h>		/* memcpy */

#define MAX_THREADS (300)
#define ARR_SIZE (300)
int g_num = 0;
pthread_key_t g_key = {0};

static void Exe1(void);
static void *WriteToGlobal(void *arg);
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(void)
{
	Exe1();
	
	return 0;
}

static void Exe1(void)
{
	size_t i = 0;
	pthread_t threads[MAX_THREADS] = {0};
	int var = 3;
	
	for (i = 0; i < MAX_THREADS; ++i)
	{
		while (0 != pthread_create(&threads[i], NULL, &WriteToGlobal, &var));
	}
	
	for (i = 0; i < MAX_THREADS; ++i)
	{
		pthread_join(threads[i], NULL);
	}
}

static void *WriteToGlobal(void *arg)
{
	void *specific_data = (int *)malloc(sizeof(pthread_t));
	pthread_t self = pthread_self();
	
	memcpy(specific_data, &self, sizeof(pthread_t));
	pthread_setspecific(g_key, specific_data);
	
	pthread_mutex_lock(&mutex);
	printf("thread %d, main_local_var:\t%p\n", g_num, (void *)arg);
	printf("thread %d, pthread_self():\t%p\n", g_num, (void *)self);
	printf("thread %d, local variable:\t%p\n", g_num, (void *)&specific_data);
	printf("thread %d, arg address:\t%p\n", g_num, (void *)&arg);
	printf("thread %d, heap variable:\t%p\n", g_num, (void *)specific_data);
	printf("thread %d, g_key address:\t%p\n", g_num, (void *)&g_key);
	printf("thread %d, routine address:\t%p\n", g_num, &WriteToGlobal);
	printf("thread %d, main address:\t%p\n", g_num, &main);
	printf("\n");
	++g_num;
	
	pthread_mutex_unlock(&mutex);
	
	free(specific_data);
	specific_data = NULL;
	
	return arg;
}
