/*****************************************/
/*   Developer: Gali Aviyam              */
/*   Project: Circular Buffer 		     */				         
/*   Date: 13/12/22		            	 */
/*   Reviewer: Moriah	     			 */
/*****************************************/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <sys/types.h> /*ssize_t*/
#include <string.h> /*memcpy*/

#include "c_buff.h"/*header file*/


#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))

struct c_buff
{
	size_t capacity;
	size_t size;
	char *loc;
	char data[1];
};

/********************************Create**********************************/
c_buff_t *CbuffCreate(size_t capacity)
{
	c_buff_t *buffer = NULL;

    assert(0 < capacity);
    
    buffer = (c_buff_t *)malloc(sizeof(c_buff_t) + (sizeof(char) * capacity));
    if (NULL ==  buffer)
    {
          return NULL;
    }
    
    buffer->capacity = capacity;
    buffer->size = 0;
    buffer->loc = (char *)(buffer) + OFFSETOF(c_buff_t, data);
    
    return buffer;
}

/********************************Destroy**********************************/
void CbuffDestroy(c_buff_t *cbuff)
{
	free(cbuff);
	cbuff = NULL;
}

/********************************Write***********************************/
static void WriteHelper(c_buff_t *cbuff, const void *src, size_t count)
{
	assert(NULL != cbuff);
	assert(NULL != src);

	memcpy(cbuff->loc, src, count);
	cbuff->size += count;
	cbuff->loc += count;
	cbuff->loc = cbuff->data + ((cbuff->loc - cbuff->data) % cbuff->capacity);
}

ssize_t CbuffWrite(c_buff_t *cbuff, const void *src, size_t count)
{
	size_t free_space = 0;
	size_t bytes_to_write = 0;
	size_t bytes_to_end = 0;
	size_t ret_value = 0;
	
	assert(NULL != cbuff);
	assert(NULL != src);
	
	free_space = CbuffGetFreeSpace(cbuff);
	bytes_to_write = (count <= free_space) ? count : free_space;
	bytes_to_end = (cbuff->data + cbuff->capacity) - cbuff->loc;
	ret_value = bytes_to_write;
	
	if (bytes_to_end < bytes_to_write)
	{
		WriteHelper(cbuff, src, bytes_to_end);
		bytes_to_write -= bytes_to_end;
		
		src = (const void *)((const char *)src + bytes_to_end);
	}
	WriteHelper(cbuff, src, bytes_to_write);
	
	return ret_value;
}

/********************************Read************************************/
static void ReadHelper(c_buff_t *cbuff, void *read_ptr, void *dest, size_t count)
{
	
	assert(NULL != cbuff);
	assert(NULL != dest);
	assert(NULL != read_ptr);
	
	memcpy(dest, read_ptr, count);
	cbuff->size -= count;
}

ssize_t CbuffRead(c_buff_t *cbuff, void *dest, size_t count)
{
	size_t bytes_to_read = 0;
	ssize_t ret_value = 0;
	ssize_t read_to_start_diff = 0;
	void *read_ptr = NULL;
	
	assert(NULL != cbuff);
	assert(NULL != dest);
	
	bytes_to_read = (count <= cbuff->size) ? count : cbuff->size;
	ret_value = bytes_to_read;
	read_to_start_diff = (cbuff->loc - cbuff->size) - cbuff->data;
	read_ptr = cbuff->loc - cbuff->size;
	
	if (read_to_start_diff < (ssize_t)0)
	{
		read_ptr = cbuff->data + cbuff->capacity + read_to_start_diff;
		
		if ((ssize_t)bytes_to_read < -read_to_start_diff)
		{
			read_to_start_diff = -bytes_to_read;
		}
		
		ReadHelper(cbuff, read_ptr, dest, -read_to_start_diff);

		bytes_to_read += read_to_start_diff;
		dest = (void *)((char *)dest - read_to_start_diff);
		read_ptr = cbuff->data;
	}
	
	ReadHelper(cbuff, read_ptr, dest, bytes_to_read);
	
	return ret_value;
}

/******************************FreeSpace********************************/
size_t CbuffGetFreeSpace(const c_buff_t *cbuff)
{
	assert(NULL != cbuff);
	
	return (cbuff->capacity - cbuff->size);
}

/*******************************IsEmpty*********************************/
int CbuffIsEmpty(const c_buff_t *cbuff)
{
	assert(NULL != cbuff);
	
	return (0 == cbuff->size);
}

/*******************************Capacity********************************/
size_t CbuffCapacity(const c_buff_t *cbuff)
{
	assert(NULL != cbuff);
	
	return cbuff->capacity;
}
