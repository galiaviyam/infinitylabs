/*****************************************/
/*   Developer: Gali Aviyam	           	 */
/*   Project: Vector		 	         */				         
/*   Date: 04/12/22		            	 */
/*					                     */
/*****************************************/
#include <stdlib.h> /*malloc*/
#include <string.h> /*memcpy*/
#include <assert.h> /*assert*/

#include "d_vector.h" /*h file*/

#define GROWTH_FACTOR 2
#define SHRINK_THRESHOLD 0.25

struct vector
{
	size_t capacity;
	size_t size;
	size_t element_size;
	char *vector_arr;
};

vector_t *VectorCreate(size_t capacity, size_t element_size)
{
	vector_t *vector = (vector_t*)malloc(sizeof(vector_t) + element_size * capacity);
	if (NULL == vector)
	{
		return NULL;
	}
	vector->capacity = capacity;
	vector->size = 0;
	vector->element_size = element_size;
	vector->vector_arr = (char *)vector + sizeof(vector_t);
	
	return vector;
}

void VectorDestroy(vector_t *vector)
{
	assert(NULL != vector);
	free(vector);
	vector = NULL;
}

vector_t *VectorPushBack(vector_t *vector, const void *element)
{
	char *last_elem = NULL;
	assert(NULL != vector);
	assert(NULL != element);
	
	last_elem = vector->vector_arr + 
				sizeof(char) * vector->element_size * vector->size;
	
	memcpy((void *)last_elem, element, vector->element_size);
	++(vector->size);

	if (vector->size == vector->capacity)
	{
		vector = VectorResize(vector, (GROWTH_FACTOR * vector->capacity));
	}
	
	return vector;
}

vector_t *VectorPopBack(vector_t *vector)
{
	assert(NULL != vector);
	
	--(vector->size);
	
	if ((0 != vector->size) && 
			(vector->size <= (SHRINK_THRESHOLD * vector->capacity)))
	{
		vector = VectorResize(vector, vector->capacity / GROWTH_FACTOR);
	}
	
	return vector;
}

void *VectorGetAccessElement(const vector_t *vector, size_t index)
{
	return ((vector->vector_arr) + 
			(sizeof(char) * vector->element_size * index));
}

size_t VectorSize(const vector_t *vector)
{
	assert(NULL != vector);
	return vector->size;
}

size_t VectorCapacity(const vector_t *vector)
{
	assert(NULL != vector);
	return vector->capacity;
}

vector_t *VectorResize(vector_t *vector, size_t new_capacity)
{
	vector_t *tmp = NULL;
	size_t new_size = 0;
	
	assert(NULL != vector);
	
	new_size = sizeof(vector_t) + (new_capacity * vector->element_size);
	tmp = vector;
	
	tmp = (vector_t*)realloc(tmp, new_size);
	if (NULL == tmp)
	{
		return NULL;
	}
	
	vector = tmp;
	vector->capacity = new_capacity;
	vector->vector_arr = (char *)(vector) + sizeof(vector_t);
	return vector;
}
