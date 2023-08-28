#include <stdio.h>		/* printf */
#include <semaphore.h>	/* semaphore		*/
#include <pthread.h>	/* pthread_create	*/
#include <unistd.h>		/* sleep			*/

static sem_t g_sem1;
static sem_t g_sem2;

/*----------------------------Function Declarations---------------------------*/

static void *DoPing(void *data);
static void *DoPong(void *data);

/*----------------------------Function Definitions----------------------------*/

int main(void)
{
	pthread_t ping_thread;
	pthread_t pong_thread;
	
	if (0 != sem_init(&g_sem1, 0, 0))
	{
		return -1;
	}

	if (0 != sem_init(&g_sem2, 0, 1))
	{
		return -1;
	}

	pthread_create(&ping_thread, NULL, &DoPing, NULL);
	pthread_create(&pong_thread, NULL, &DoPong, NULL);
	
	pthread_join(ping_thread, NULL);
	pthread_join(pong_thread, NULL);

	sem_destroy(&g_sem1);
	sem_destroy(&g_sem2);

	return 0;
}

static void *DoPing(void *data)
{
	(void)data;
	
	while (1)
	{
		sem_wait(&g_sem2);
		printf("PING\n");
		sem_post(&g_sem1);
	}
	
	pthread_exit(NULL);
}

static void *DoPong(void *data)
{
	(void)data;
	
	while (1)
	{
		sem_wait(&g_sem1);
		printf("PONG\n");
		sem_post(&g_sem2);
	}
	
	pthread_exit(NULL);
}

