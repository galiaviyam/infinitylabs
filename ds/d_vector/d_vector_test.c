/*****************************************/
/*   Developer: Gali Aviyam	           	 */
/*   Project: Vector		 	         */				         
/*   Date: 04/12/22		            	 */
/*					                     */
/*****************************************/
#include <stdio.h>	/*printf*/
#include <string.h>	/*memcmp*/
#include <assert.h>	/*assert*/

#include "d_vector.h" /*header file*/

typedef enum
{
	SUCCESS = 0,
	FAIL

} status_t;

static void VectorTests(void);
static int TestGetAccess(const vector_t *vector, size_t index, void *element, 
size_t element_size);
static int TestResize(const vector_t *vector, size_t size, size_t 
*prev_capasity);

int main()
{
	VectorTests();
	return 0;
}

static void VectorTests(void)
{
	size_t size = 9;
	int element[] = {0, 1, 2, 3, 4, 63, 64, -45, 987};
	size_t capacity = 1;
	size_t element_size = sizeof(int);
	size_t i = 0;
	size_t j = 0;
	status_t status = SUCCESS;
	vector_t *my_vector = VectorCreate(capacity, element_size);
	
	status += TestResize(my_vector, i, &capacity);

	for (i = 1; i <= size; ++i)
	{
		printf("test %lu:", i);

		my_vector = VectorPushBack(my_vector, (void *)&element[i - 1]);
		status += TestResize(my_vector, i, &capacity);
		
		for (j = 0; j < i; ++j)
		{
			status += TestGetAccess(my_vector, j, (void *)&element[j], 
											element_size);
		}
		
		if (!status)
		{
			printf("\t\033[0;32mPassed\033[0m\n");
		}
		else
		{
			status = FAIL;
			printf("\t\033[0;31mFailed\033[0m\n");
		}
	}

	for (i = size; i > 0; --i)
	{
		my_vector = VectorPopBack(my_vector);
		
		for (j = 0; j < (i - 1); ++j)
		{
			status += TestGetAccess(my_vector, j, (void *)&element[j], 
											element_size);
		}
	}
	
	VectorDestroy(my_vector);

	if (status)
	{
		printf("\033[0;31m");
		printf("Failed in %d tests\n", status);
	}
	else
	{
		printf("\033[0;32m");
		printf("Passed all tests!\n\n");
	}	
	printf("\033[0m");
}

static int TestResize(const vector_t *vector, size_t size, size_t 
*prev_capasity) 
{
	return ((VectorCapacity(vector) == size) && size != *prev_capasity);
}

static int TestGetAccess(const vector_t *vector, size_t index, void 
*element, size_t element_size) 
{
	status_t status = SUCCESS;
	
	assert(vector);
	assert(element);
	
	status += memcmp(VectorGetAccessElement(vector, index), element, 
					element_size) != 0;
	
	return status;
}
