/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Producer-Consumer       */
/*   Date:      27/02/23                */
/*   Reviewer:  Shauli                  */
/*                                      */
/****************************************/

#include <pthread.h>	/* pthread_create */
#include <stdio.h>		/* printf */
#include <stdlib.h>		/* malloc */
#include <assert.h>		/* assert */
#include <semaphore.h>	/* sem_open */
#include <fcntl.h>		/* For O_* constants */
#include <sys/stat.h>	/* For mode constants */
#include <string.h>		/* strncpy */

#include "dlist.h"		/* dlist header file */
#include "c_buff.h"		/* c_buff header file */

#define SIZE (10)
#define MAX_LOOP (1000)

typedef enum lock
{
	UNLOCKED = 0,
	LOCKED
} lock_t;

typedef enum bool
{
	FALSE = 0,
	TRUE
} bool_t;

typedef enum status
{
	ERROR = -1,
	SUCCESS
} status_t;

typedef struct insert
{
	dlist_t *list;
	size_t produce[SIZE];
	size_t consume[SIZE];
} insert_t;

typedef struct cbuff_struct
{
	c_buff_t *c_buff;
	size_t produce[SIZE];
	size_t consume[SIZE];
} cbuff_struct_t;

typedef struct thread_safe_fsq
{
	int q[SIZE];
	pthread_mutex_t read_mutex;
	pthread_mutex_t write_mutex;
	sem_t empty_cells;
	sem_t full_cells;
	size_t read_idx;
	size_t write_idx;
} thread_safe_fsq_t;


static int g_lock = 0;
static int g_num = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = {0};
sem_t *sem = NULL;
sem_t ex4_sem1 = {0};
sem_t ex4_sem2 = {0};
sem_t sem6 = {0};

static void Exe1(void);
static void *ReadFromGlobal(void *num);
static void *WriteToGlobal(void *num);

static void Exe2(void);
static void *RemoveFromList(void *insert_struct);
static void *InsertToList(void *insert_struct);
static void InitStructList(insert_t *insert_struct);
static void PrintArr(size_t *arr, size_t size);

static void Exe3(void);
static void *InsertToListEx3(void *insert_struct);
static void *RemoveFromListEx3(void *insert_struct);

static void Exe4(void);
static void *InsertToQueueEx4(void *cbuff_struct);
static void *RemoveFromQueueEx4(void *cbuff_struct);
static void InitStructCbuff(cbuff_struct_t *insert_struct);

static void Exe5(void);
static void *InsertToQueueEx5(void *queue_struct);
static void *RemoveFromQueueEx5(void *queue_struct);
static void FSQInit(thread_safe_fsq_t *fsq);
static void FSQEnqueue(thread_safe_fsq_t *fsq, int value);
static size_t FSQDequeue(thread_safe_fsq_t *fsq);

static void Exe6(void);
static void *ProduceEx6(void *arg);
static void *ConsumeEx6(void *arg);

int main(void)
{
/*	Exe1();*/
/*	Exe2();*/
/*	Exe3();*/
/*	Exe4();*/
/*	Exe5();*/
	Exe6();
	
	return 0;
}

/*---------------------------------------------------------------------------*/
/*------------------------------    Exe1    ---------------------------------*/
/*---------------------------------------------------------------------------*/
static void Exe1(void)
{
	pthread_t producer_thread = {0};
	pthread_t consumer_thread = {0};
	int num = 3;
	int arr[SIZE] = {0};
	size_t i = 0;
	
	while (0 != pthread_create(&producer_thread, NULL, &WriteToGlobal, &num));
	while (0 != pthread_create(&consumer_thread, NULL, &ReadFromGlobal, arr));
	
	pthread_join(producer_thread, NULL);
	pthread_join(consumer_thread, NULL);
	
	for (i = 0; i < SIZE; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

static void *WriteToGlobal(void *num)
{
	size_t i = 0;
	
	for (i = 0; i < SIZE; ++i)
	{
		while (LOCKED == g_lock);
		
		g_num += *(int *)num;
		g_lock = LOCKED;
	}
	pthread_exit(NULL);
}

static void *ReadFromGlobal(void *num)
{
	size_t i = 0;
	
	for (i = 0; i < SIZE; ++i)
	{
		while (UNLOCKED == g_lock);
		
		*((int *)num + i) = g_num;
		g_lock = UNLOCKED;
	}
	pthread_exit(NULL);
	
	return NULL;
}

/*---------------------------------------------------------------------------*/
/*------------------------------    Exe2    ---------------------------------*/
/*---------------------------------------------------------------------------*/
static void Exe2(void)
{
	pthread_t producer_threads[SIZE] = {0};
	pthread_t consumer_threads[SIZE] = {0};
	
	size_t i = 0;
	insert_t *insert = (insert_t *)malloc(sizeof(insert_t));
	if (NULL == insert)
	{
		printf("malloc error\n");
		return;
	}
	
	pthread_mutex_init(&mutex, NULL);
	InitStructList(insert);
	
	for (i = 0; i < SIZE; ++i)
	{
		while (0 != pthread_create(&producer_threads[i], NULL, &InsertToList, insert));
		while (0 != pthread_create(&consumer_threads[i], NULL, &RemoveFromList, insert));
	}
	
	for (i = 0; i < SIZE; ++i)
	{		
		pthread_join(producer_threads[i], NULL);
		pthread_join(consumer_threads[i], NULL);
	}
	
	PrintArr(insert->consume, SIZE);
	
	DlistDestroy(insert->list);
	insert->list = NULL;
	
	free(insert);
	insert = NULL;
	
	pthread_mutex_destroy(&mutex);
}

static void InitStructList(insert_t *insert_struct)
{
	size_t i = 0;
	
	assert(NULL != insert_struct);
	
	insert_struct->list = DlistCreate();
	
	for (i = 0; i < SIZE; ++i)
	{
		insert_struct->produce[i] = i;
	}
}

static void *InsertToList(void *insert_struct)
{
	insert_t *in_struct = NULL;
	static size_t i = 0;
	size_t num_running = MAX_LOOP;
		
	assert(NULL != insert_struct);
	
	in_struct = (insert_t *)insert_struct;
	
	
	while (--num_running)
	{
		pthread_mutex_lock(&mutex);
		
		DlistPushBack(in_struct->list, &in_struct->produce[i]);

		pthread_mutex_unlock(&mutex);
	}
	
	++i;
	pthread_exit(NULL);
	return NULL;
}


static void *RemoveFromList(void *insert_struct)
{
	insert_t *in_struct = NULL;
	static size_t i = 0;
	size_t data = 0;
	int has_new_data = FALSE;
	size_t num_running = MAX_LOOP;
		
	assert(NULL != insert_struct);
	
	in_struct = (insert_t *)insert_struct;
	
	while (--num_running)
	{
		pthread_mutex_lock(&mutex);
		
		if (!DlistIsEmpty(in_struct->list))
		{
			data = *(size_t *)DlistPopBack(in_struct->list);
			has_new_data = TRUE;
		}
		pthread_mutex_unlock(&mutex);
		
		if (has_new_data)
		{
			in_struct->consume[i] = data;
			has_new_data = FALSE;
		}
	}
	++i;			
	
	pthread_exit(NULL);
	return NULL;
}

static void PrintArr(size_t *arr, size_t size)
{
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		printf("%lu\n", arr[i]);
	}
	
	printf("\n");
}

/*---------------------------------------------------------------------------*/
/*------------------------------    Exe3    ---------------------------------*/
/*---------------------------------------------------------------------------*/
static void Exe3(void)
{
	pthread_t producer_threads[SIZE] = {0};
	pthread_t consumer_threads[SIZE] = {0};

	size_t i = 0;
	insert_t *insert = (insert_t *)malloc(sizeof(insert_t));
	if (NULL == insert)
	{
		printf("malloc error\n");
		return;
	}
	pthread_mutex_init(&mutex, NULL);
	sem = sem_open("ex3_sem", O_CREAT, S_IRWXU, 0);
	if (SEM_FAILED == sem)
	{
		printf("sem_open failed\n");
		return;
	}
	
	InitStructList(insert);
	
	for (i = 0; i < SIZE; ++i)
	{
		while (0 != pthread_create(&producer_threads[i], NULL, &InsertToListEx3, insert));
		while (0 != pthread_create(&consumer_threads[i], NULL, &RemoveFromListEx3, insert));
	}
	
	for (i = 0; i < SIZE; ++i)
	{		
		pthread_detach(producer_threads[i]);
		pthread_join(consumer_threads[i], NULL);
	}
	
	PrintArr(insert->consume, SIZE);
	
	DlistDestroy(insert->list);
	insert->list = NULL;
	
	free(insert);
	insert = NULL;
	
	pthread_mutex_destroy(&mutex);
	sem_close(sem);
}

static void *InsertToListEx3(void *insert_struct)
{
	insert_t *in_struct = NULL;
	static size_t i = 0;
	size_t num_running = MAX_LOOP;
	
	assert(NULL != insert_struct);
	
	in_struct = (insert_t *)insert_struct;
	
	
	while (--num_running)
	{
		pthread_mutex_lock(&mutex);
		
		if (SUCCESS != sem_post(sem))
		{
			return NULL;
		}
		DlistPushBack(in_struct->list, &in_struct->produce[i]);

		pthread_mutex_unlock(&mutex);
	}
	
	++i;
	pthread_exit(NULL);
}

static void *RemoveFromListEx3(void *insert_struct)
{
	insert_t *in_struct = NULL;
	static size_t i = 0;
	size_t data = 0;
	size_t num_running = MAX_LOOP;
	
	assert(NULL != insert_struct);
	
	in_struct = (insert_t *)insert_struct;
	
	while (--num_running)
	{
		if (SUCCESS != sem_wait(sem))
		{
			return NULL;
		}
		pthread_mutex_lock(&mutex);
		
		data = *(size_t *)DlistPopBack(in_struct->list);
		pthread_mutex_unlock(&mutex);
		
		in_struct->consume[i] = data;
	}

	++i;			
	pthread_exit(NULL);
}


/*---------------------------------------------------------------------------*/
/*------------------------------    Exe4    ---------------------------------*/
/*---------------------------------------------------------------------------*/

static void Exe4(void)
{
	pthread_t producer_threads[SIZE] = {0};
	pthread_t consumer_threads[SIZE] = {0};

	size_t i = 0;
	cbuff_struct_t *insert = (cbuff_struct_t *)malloc(sizeof(cbuff_struct_t));
	if (NULL == insert)
	{
		printf("malloc error\n");
		return;
	}

	pthread_mutex_init(&mutex, NULL);
	
	sem_init(&ex4_sem1, 0, 0);
	
	sem_init(&ex4_sem2, 0, 1);
	
	InitStructCbuff(insert);
	
	for (i = 0; i < SIZE; ++i)
	{
		while (0 != pthread_create(&producer_threads[i], NULL, &InsertToQueueEx4, insert));
		while (0 != pthread_create(&consumer_threads[i], NULL, &RemoveFromQueueEx4, insert));
	}
	
	for (i = 0; i < SIZE; ++i)
	{		
		pthread_join(producer_threads[i], NULL);
		pthread_join(consumer_threads[i], NULL);
	}
	
	PrintArr(insert->consume, SIZE);
	
	pthread_mutex_destroy(&mutex);
	sem_destroy(&ex4_sem1);
	sem_destroy(&ex4_sem2);
	
	CbuffDestroy(insert->c_buff);
	insert->c_buff = NULL;
	
	free(insert);
	insert = NULL;
}

static void *InsertToQueueEx4(void *cbuff_struct)
{
	cbuff_struct_t *in_struct = NULL;
	static size_t i = 0;
	size_t num_running = MAX_LOOP;
	void *data = NULL;
	
	assert(NULL != cbuff_struct);
	
	in_struct = (cbuff_struct_t *)cbuff_struct;
	
	while (--num_running)
	{
		data = &in_struct->produce[i];
		
		if (SUCCESS != sem_wait(&ex4_sem2))
		{
			return NULL;
		}
		
		pthread_mutex_lock(&mutex);
		
		CbuffWrite(in_struct->c_buff, data, 1);

		pthread_mutex_unlock(&mutex);

		if (SUCCESS != sem_post(&ex4_sem1))
		{
			return NULL;
		}
	}
	
	++i;
	pthread_exit(NULL);
}

static void *RemoveFromQueueEx4(void *cbuff_struct)
{
	cbuff_struct_t *in_struct = NULL;
	static size_t i = 0;
	size_t data = 0;
	size_t num_running = MAX_LOOP;
	
	assert(NULL != cbuff_struct);
	
	in_struct = (cbuff_struct_t *)cbuff_struct;
	
	while (--num_running)
	{
		if (SUCCESS != sem_wait(&ex4_sem1))
		{
			return NULL;
		}
		pthread_mutex_lock(&mutex);
		
		CbuffRead(in_struct->c_buff, &data, 1);
		
		pthread_mutex_unlock(&mutex);
		
		if (SUCCESS != sem_post(&ex4_sem2))
		{
			return NULL;
		}
		
		in_struct->consume[i] = data;
	}

	++i;			
	pthread_exit(NULL);
}

static void InitStructCbuff(cbuff_struct_t *insert_struct)
{
	size_t i = 0;
	
	assert(NULL != insert_struct);
	
	insert_struct->c_buff = CbuffCreate(15);
	
	for (i = 0; i < SIZE; ++i)
	{
		insert_struct->produce[i] = i;
	}
}

/*---------------------------------------------------------------------------*/
/*------------------------------    Exe5    ---------------------------------*/
/*---------------------------------------------------------------------------*/

int produce[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

static void Exe5(void)
{
	pthread_t producer_threads[SIZE] = {0};
	pthread_t consumer_threads[SIZE] = {0};

	size_t i = 0;
	thread_safe_fsq_t *insert = (thread_safe_fsq_t *)malloc(sizeof(thread_safe_fsq_t));
	if (NULL == insert)
	{
		printf("malloc error\n");
		return;
	}
	
	FSQInit(insert);
	
	for (i = 0; i < SIZE; ++i)
	{
		while (0 != pthread_create(&producer_threads[i], NULL, &InsertToQueueEx5, insert));
		while (0 != pthread_create(&consumer_threads[i], NULL, &RemoveFromQueueEx5, insert));
	}
	
	for (i = 0; i < SIZE; ++i)
	{		
		pthread_join(producer_threads[i], NULL);
		pthread_join(consumer_threads[i], NULL);
	}
	pthread_mutex_destroy(&insert->read_mutex);
	pthread_mutex_destroy(&insert->write_mutex);
	sem_close(&insert->empty_cells);
	sem_close(&insert->full_cells);
	
	free(insert);
	insert = NULL;
}

static void *InsertToQueueEx5(void *arg)
{
	thread_safe_fsq_t *fsq = NULL;
	size_t num_running = MAX_LOOP;
	static size_t i = 0;
	
	assert(NULL != arg);
	
	fsq = (thread_safe_fsq_t *)arg;
	
	while (--num_running)
	{
		if (SUCCESS != sem_wait(&fsq->empty_cells))
		{
			return NULL;
		}
		
		pthread_mutex_lock(&fsq->write_mutex);
		
		FSQEnqueue(fsq, produce[i]);
	
		pthread_mutex_unlock(&fsq->write_mutex);

		if (SUCCESS != sem_post(&fsq->full_cells))
		{
			return NULL;
		}

	}
	
	++i;
	pthread_exit(NULL);
}

static void *RemoveFromQueueEx5(void *arg)
{
	thread_safe_fsq_t *fsq = NULL;
	int data = 0;
	size_t num_running = MAX_LOOP;
	
	assert(NULL != arg);
	
	fsq = (thread_safe_fsq_t *)arg;
	
	while (--num_running)
	{
		if (SUCCESS != sem_wait(&fsq->full_cells))
		{
			return NULL;
		}
		pthread_mutex_lock(&fsq->read_mutex);
		
		data = FSQDequeue(fsq);
	
		pthread_mutex_unlock(&fsq->read_mutex);

		if (SUCCESS != sem_post(&fsq->empty_cells))
		{
			return NULL;
		}
		
		printf("%d\n", data);
	}

	pthread_exit(NULL);
}

static void FSQInit(thread_safe_fsq_t *fsq)
{
	pthread_mutex_init(&fsq->read_mutex, NULL);
	pthread_mutex_init(&fsq->write_mutex, NULL);

	fsq->read_idx = 0;
	fsq->write_idx = 0;
	
	sem_init(&fsq->empty_cells, 0, SIZE);
	sem_init(&fsq->full_cells, 0, 0);
}

static void FSQEnqueue(thread_safe_fsq_t *fsq, int value)
{
	fsq->q[fsq->write_idx] = value;
	fsq->write_idx = (fsq->write_idx + 1) % SIZE;
}

static size_t FSQDequeue(thread_safe_fsq_t *fsq)
{
	int value = 0;
	
	value = fsq->q[fsq->read_idx];
	fsq->read_idx = (fsq->read_idx + 1) % SIZE;
	
	return value;
}



/*---------------------------------------------------------------------------*/
/*------------------------------    Exe6    ---------------------------------*/
/*---------------------------------------------------------------------------*/
#define MAX_CONSUMERS (10)
#define MAX_MESSAGES (10)
#define MAX_LEN (10)

char g_message_buffer[MAX_LEN] = {0};
int g_curr_ver = 0;

static void Exe6(void)
{
	pthread_t producer_thread = {0};
	pthread_t consumer_threads[MAX_CONSUMERS] = {0};
	size_t cons_num[MAX_CONSUMERS] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	char message[] = "Hello :)";
	size_t i = 0;
	
	sem_init(&sem6, 0, 0);
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);
    
	while (0 != pthread_create(&producer_thread, NULL, &ProduceEx6, &message));

	for (i = 0; i < MAX_CONSUMERS; ++i)
	{
		while (0 != pthread_create(&consumer_threads[i], NULL, &ConsumeEx6, &cons_num[i]));
	}
	
	for (i = 0; i < MAX_CONSUMERS; ++i)
	{		
		pthread_join(consumer_threads[i], NULL);
/*		sem_post(&sem6);*/
	}
	pthread_join(producer_thread, NULL);
	
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	sem_destroy(&sem6);
}

static void *ProduceEx6(void *arg)
{
	size_t j = 0;
	size_t len = 0;
	size_t i = 0;
	char *message = (char *)arg;
	
	while (i < MAX_LOOP)
	{	
		len = strlen(message);
		
		pthread_mutex_lock(&mutex);
		
		strncpy(g_message_buffer, message, len);
		++g_curr_ver;
		
		pthread_mutex_unlock(&mutex);

		pthread_cond_broadcast(&cond);

		for (j = 0; j < MAX_CONSUMERS; ++j)
		{
			sem_wait(&sem6);
		}
		
		++i;
	}
	
	return NULL;
}

static void *ConsumeEx6(void *arg)
{
	char message[MAX_LEN] = {0};
	size_t i = 0;
	int last_version = 0;
	
	while (i < MAX_LOOP)
	{
		pthread_mutex_lock(&mutex);
		
		while(last_version == g_curr_ver)
		{
			pthread_cond_wait(&cond, &mutex);
		}
		strcpy(message, g_message_buffer);

		pthread_mutex_unlock(&mutex);
		
		++last_version;
		
		if (SUCCESS != sem_post(&sem6))
		{
			return NULL;
		}
		++i;
		printf("message thread num %d: %s\n", *(int *)arg, message);
	}

	(void)arg;
	return (NULL);
}
