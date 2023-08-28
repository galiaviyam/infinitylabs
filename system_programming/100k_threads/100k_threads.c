/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   100K Threads            */
/*   Date:      25/02/23                */
/*   Reviewer:  Noy                     */
/*                                      */
/****************************************/

#include <pthread.h>	/* pthread_create */
#include <assert.h>		/* assert */
#include <unistd.h>		/* sleep */
#include <stdio.h>		/* printf */
#include <stdlib.h>		/* calloc */

#define SIZE (100000)
#define MAX_THREADS (32753)
#define RANGE (100000)

size_t g_array[SIZE];

const unsigned int test_num = 1234567890;
unsigned int g_range = test_num / 3;

static void Exe1(void);
static void Exe2(void);
static void Exe3(void);
static void Exe4(void);

static void *WriteToGlobalArr(void *arg);
static void *SumOfDivisors(void *num);
static unsigned int SimpleSumOfDivisors(size_t num);
static void SimpleSumOfDivisorsEx6(size_t num);

int main(void)
{
/*	Exe1();*/
/*	Exe2();*/
/*	Exe3();*/
	Exe4();
	
	printf("Sum of divisors is %u\n", SimpleSumOfDivisors(test_num));
	SimpleSumOfDivisorsEx6(test_num);
	
	return 0;
}

static void Exe1(void)
{
	size_t i = 0;
	pthread_t threads[SIZE] = {0};
	int arr[SIZE] = {0};
	time_t start = 0;
	time_t end = 0;
	size_t count = 0;
	
	start = time(&start);
	
	for (i = 0; i < SIZE; ++i)
	{
		arr[i] = i;
		pthread_create(&threads[i], NULL, &WriteToGlobalArr, &arr[i]);
	}
	
	end = time(&end);

	sleep(10);

	for (i = 0; i < SIZE; ++i)
	{
		if (i == g_array[i])
		{
			++count;
		}
	}
	
	printf("%lu correct values\n", count);
	
	printf("Time (before 10 sec sleep): %ld seconds\n", end - start);
}

static void Exe2(void)
{
	size_t i = 0;
	pthread_t threads[MAX_THREADS] = {0};
	int arr[MAX_THREADS] = {0};
	time_t start = 0;
	time_t end = 0;
	size_t count = 0;
	
	start = time(&start);
	
	for (i = 0; i < MAX_THREADS; ++i)
	{
		arr[i] = i;
		while (0 != pthread_create(&threads[i], NULL, &WriteToGlobalArr, &arr[i]));
	}
	
	end = time(&end);

	sleep(10);

	for (i = 0; i < MAX_THREADS; ++i)
	{
		if (i == g_array[i])
		{
			++count;
		}
	}
	
	printf("%lu correct values\n", count);
	
	printf("Time (before 10 sec sleep): %ld seconds\n", end - start);
}

static void Exe3(void)
{
	size_t i = 0;
	pthread_t threads[SIZE] = {0};
	int arr[SIZE] = {0};
	time_t start = 0;
	time_t end = 0;
	size_t count = 0;
	
	start = time(&start);
	
	for (i = 0; i < SIZE; ++i)
	{
		arr[i] = i;
		while (0 != pthread_create(&threads[i], NULL, &WriteToGlobalArr, &arr[i]));
		
		pthread_detach(threads[i]);
	}
	
	end = time(&end);

	sleep(10);

	for (i = 0; i < SIZE; ++i)
	{
		if (i == g_array[i])
		{
			++count;
		}
	}
	
	printf("%lu correct values\n", count);
	
	printf("Time (before 10 sec sleep): %ld seconds\n", end - start);
}

static void Exe4(void)
{
	size_t i = 0;
	pthread_t threads[MAX_THREADS] = {0};
	unsigned int upper_limit[MAX_THREADS] = {0};
	time_t start = 0;
	time_t end = 0;
	unsigned int sum = 0;
	unsigned int lim = (test_num / g_range) + 1;
	unsigned int *retval = NULL;

	start = time(&start);
	
	for (i = 0; i < lim; ++i)
	{
		upper_limit[i] = (g_range * (i + 1));
		while (0 != pthread_create(&threads[i], NULL, &SumOfDivisors, &upper_limit[i]));
	}
	
	end = time(&end);

	for (i = 0; i < lim; ++i)
	{
		pthread_join(threads[i], (void **)&retval);
		sum += *retval;
		
		free(retval);
		retval = NULL;
	}
	
	printf("sum of divisors: %u\n", sum);
	
	printf("Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

static void *SumOfDivisors(void *arg)
{
	unsigned int sum_of_divisors = 0;
	unsigned int *retval = NULL;
	unsigned int upper_limit = 0;
	unsigned int i = 0;
	
	assert(NULL != arg);
	
	upper_limit = *(unsigned int *)arg;
	
	for (i = upper_limit - (g_range - 1); i <= test_num && i <= upper_limit; ++i)
	{
		if (0 == test_num % i)
		{
			sum_of_divisors += i;
		}
	}
	
	retval = (unsigned int *)calloc(1, sizeof(unsigned int));
	if (NULL == retval)
	{
		return NULL;
	}
	
	*retval = sum_of_divisors;
	
	return retval;
}

static unsigned int SimpleSumOfDivisors(size_t num)
{
	unsigned int sum_of_divisors = 0;
	unsigned int i = 0;
	time_t start = 0;
	time_t end = 0;
	
	start = time(NULL);
	for (i = 1; i <= num ; ++i)
	{
		if (0 == num % i)
		{
			sum_of_divisors += i;
		}
	}
	end = time(NULL);
	
	printf("Time: %ld seconds\n", end - start);
	
	return sum_of_divisors;
}


static void SimpleSumOfDivisorsEx6(size_t num)
{
	unsigned int partial_sum = 0;
	unsigned int total_sum = 0;
	time_t start = 0;
	time_t end = 0;
	
	start = time(NULL);
	#pragma omp parallel private(partial_sum) shared(total_sum)
	{
		size_t i = 1;
		partial_sum = 0;
		total_sum = 0;
		
		#pragma omp for 
		for (i = 1; i <= num; ++i)
		{
			if (0 == (num % i))
			{
				partial_sum += i;
			}
		}
		
		#pragma omp critical
		{
			total_sum += partial_sum;
		}
	}
	end = time(NULL);
	
	printf("openMP sum: %u \n", total_sum);
	printf("time: %ld\n", end - start);
}

static void *WriteToGlobalArr(void *arg)
{
	int i = *(int *)arg;
	g_array[i] = i;

	return NULL;
}
