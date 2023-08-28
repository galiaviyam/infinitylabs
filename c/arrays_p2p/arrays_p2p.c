#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#define ALIVE 1
#define DEAD 0
#define SIZE 100
#define COLS 4
#define ERROR -1

static int *Sum2DArr(int arr[][COLS], int *sum_arr, size_t rows);
static void TestSum2DArr();
static int JosephusProblem(int group[], int size);
static void TestJosephus();
static void PrintDataTypesSizes();
static char **EnvpLowCopy(char **envp);
static void SizeOfMatrix(char **matrix, size_t *row_len);
static int AllocateMatrix(char **source_matrix, char **dest_matrix);
static void CopyMatrix(char **src, char **dest);
static void ToLowerAndPrint(char **matrix);
static void DestroyMatrix(char **matrix);

int main(int argc, char *argv[], char *envp[])
{	
	printf("\n***********sum 2D array**********\n");
	TestSum2DArr();
	
	printf("\n************josephus*************\n");
	TestJosephus();
	
	printf("\n***********data Types***********\n");
	PrintDataTypesSizes();
	
	printf("\n******environment variables******\n");
	EnvpLowCopy(envp);
	
	return 0;
}

static int *Sum2DArr(int arr[][COLS], int *sum_arr, size_t rows)
{
	size_t i = 0;
	size_t j = 0;
	
	
	for (i = 0; i < rows; ++i)
	{
		sum_arr[i] = 0;
		
		for (j = 0; j < COLS; j++)
		{
			sum_arr[i] += arr[i][j]; 
		}
	}
	
	return (sum_arr);
}

static void TestSum2DArr()
{
	size_t rows = 3;
	size_t i = 0;
	
	 int arr[3][4] = {{2, 4, 6, 5}, {1, 3, 5, 6}, {7, 8, 9, 0}};
	 		   
	 int arr_sum[2] = {0, 0};
	 int *new_arr = Sum2DArr(arr, arr_sum, rows);
	 
	 for (i = 0; i < rows; ++i)
	 {
	 	printf("%d\n", new_arr[i]);
	 }
	
}

static int JosephusProblem(int group[], int size)
{
	int i = 0;
	int last_alive = 0;
	int num_of_alive = size;
	size_t interval = 2;
	
	for (i = 0; i < size; ++i) /* initializing everyone to alive */
	{
		group[i] = ALIVE;
	}
	
	i = 1;
	
	while (num_of_alive > 1)
	{
		if (2 == interval)
		{
			group[i] = DEAD;
			--num_of_alive;
			interval = 0;
		}
		
		if ((i + 1) > (size -1))
		{
			i = -1;
		}
		++i;
		
		if (group[i] == ALIVE)
		{
			++interval;
			if (2 != interval)
			{
				last_alive = i;
			}
		}
	}
	
	return last_alive;
}

static void TestJosephus()
{
	int group[100];
	int five[5];
	int three[3];

	printf("size is 100, index is: %d\n", JosephusProblem(group, 100));
	printf("size is 5, index is: %d\n", JosephusProblem(five, 5));
	printf("size is 3, index is: %d\n", JosephusProblem(three, 3));
}

static void PrintDataTypesSizes()
{
	fprintf(stdout, "char: %ld\n", sizeof(char));
	fprintf(stdout, "unsigned char: %ld\n", sizeof(unsigned char));
	fprintf(stdout, "signed char: %ld\n", sizeof(signed char));
	fprintf(stdout, "int: %ld\n", sizeof(int));
	fprintf(stdout, "unsigned int: %ld\n", sizeof(unsigned int));
	fprintf(stdout, "unsigned short: %ld\n", sizeof(unsigned short int));
	fprintf(stdout, "long int: %ld\n", sizeof(long int));
	fprintf(stdout, "short int: %ld\n", sizeof(short int));
	fprintf(stdout, "unsigned long int: %ld\n", sizeof(unsigned long int));
	fprintf(stdout, "float: %ld\n", sizeof(float));
	fprintf(stdout, "double: %ld\n", sizeof(double));
	fprintf(stdout, "long double: %ld\n", sizeof(long double));
}

static char **EnvpLowCopy(char **envp)
{
	size_t row_len = 0;
	char **envp_copy = NULL;

	assert(NULL != envp);
	SizeOfMatrix(envp, &row_len);
	
	envp_copy = malloc(sizeof(char *) * row_len);
	
	if (NULL == envp_copy)
	{
		return NULL;
	}

	if (ERROR == AllocateMatrix(envp, envp_copy))
	{
		return NULL;
	}
	
	CopyMatrix(envp, envp_copy);
	ToLowerAndPrint(envp_copy);
	DestroyMatrix(envp_copy);
	
	return envp_copy;

	
}

static void SizeOfMatrix(char **matrix, size_t *row_len)
{
	char **row_iterator = matrix;
	
	while (NULL != *row_iterator)
	{
		*row_len += 1;
		++row_iterator;
	}
	
	*row_len += 1;
}	

static int AllocateMatrix(char **source_matrix, char **dest_matrix)
{
	char **src_iterator = source_matrix;
	char **dest_iterator = dest_matrix;
	size_t string_length = 0;

	while (NULL != *src_iterator)
	{
		string_length = strlen((char *)*src_iterator);
		*dest_iterator = (char *)malloc(sizeof(char *) * string_length);
		
		if (NULL == *dest_iterator)
		{
			return ERROR;
		}

		++src_iterator;
		++dest_iterator;
	}
	
	return 0;
}

static void CopyMatrix(char **src, char **dest)
{
	char **src_iterator = src;
	char **dest_iterator = dest;

	while (NULL != *src_iterator)
	{
		strcpy(*dest_iterator, (const char *)*src_iterator);

		++src_iterator;
		++dest_iterator;
	}
}

static void ToLowerAndPrint(char **matrix)
{
	char **row_iterator = matrix;
	char *col_iterator = *matrix;
	size_t ch = 0;
	size_t string_len = 0;
	
	while (NULL != *row_iterator)
	{
		col_iterator = *row_iterator;
		string_len = strlen(col_iterator);
		
		for (ch = 0; ch < string_len; ++ch)
		{
			*(col_iterator + ch) = (char)tolower((int)*(col_iterator + ch));
		}
		
		printf("%s\n", *row_iterator);
		++row_iterator;
	}
}

static void DestroyMatrix(char **matrix)
{
	char **row_iterator = matrix;

	while (NULL != *row_iterator)
	{
		free(*row_iterator);
		*row_iterator = NULL;
		
		++row_iterator;
	}
	
	free(matrix);
	matrix = NULL;
}

