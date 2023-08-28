/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Heap               		*/
/*   Date:		06/02/23				*/
/*	 Reviewer:	Gal Ventura				*/
/*										*/
/****************************************/

#include <stdlib.h>		/* malloc */
#include <assert.h>		/* assert */

#include "heap.h"		/* heap header file*/
#include "d_vector.h"	/* vector file*/

#define MIN_CAPACITY (64)
#define ELEM_SIZE (sizeof(size_t))

typedef enum status
{
	SUCCESS = 0,
	FAIL
} status_t;

typedef enum bool
{
	FALSE = 0,
	TRUE
} bool_t;

struct heap
{
	vector_t *vector;
	heap_cmp_t cmp;
	void *param;
};

static heap_t *InitHeap(heap_t *heap, heap_cmp_t cmp, void *param);

static vector_t *GetVector(const heap_t *heap);
static void *GetValue(vector_t *vec, size_t index);
static void *HeapGetElem(heap_t *heap, size_t index);

static void HeapifyUp(heap_t *heap, size_t idx);
static void HeapifyDown(heap_t *heap, size_t idx);
static void Swap(void *elem_a, void *elem_b);

static size_t GetParentIdx(size_t index);
static size_t GetLeftIdx(size_t index);
static size_t GetRightIdx(size_t index);

static int FindIsMatch(heap_t *heap, void *data, heap_is_match_t is_match, 
					size_t *idx);

/*-------------------------------HeapCreate----------------------------*/
heap_t *HeapCreate(heap_cmp_t cmp, void *param)
{
	heap_t *heap = NULL;
	
	assert(NULL != cmp);
	
	heap = (heap_t *)malloc(sizeof(heap_t));
	if (NULL == heap)
	{
		return NULL;
	}
	
	heap = InitHeap(heap, cmp, param);
	
	return heap;
}

/*-------------------------------HeapDestroy----------------------------*/
void HeapDestroy(heap_t *heap)
{
	assert(NULL != heap);
	
	VectorDestroy(GetVector(heap));
	
	free(heap);
	heap = NULL;
}

/*-------------------------------HeapPush----------------------------*/
int HeapPush(heap_t *heap, void *data)
{
	vector_t *tmp_vec = NULL;
	
	assert(NULL != heap);
	
	tmp_vec = VectorPushBack(GetVector(heap), &data);
	if (NULL == tmp_vec)
	{
		return FAIL;
	}
	
	heap->vector = tmp_vec;
	HeapifyUp(heap, HeapSize(heap) - 1);
	
	return SUCCESS;
}

/*-------------------------------HeapPop----------------------------*/
void *HeapPop(heap_t *heap)
{
	vector_t *tmp_vec = NULL;
	void *peek = NULL;
	size_t idx = 0;
	
	assert(NULL != heap);
	assert(!HeapIsEmpty(heap));
	
	peek = HeapPeek(heap);
	idx = HeapSize(heap) - 1;
	
	Swap(HeapGetElem(heap, 0), HeapGetElem(heap, idx));
	
	tmp_vec = VectorPopBack(GetVector(heap));
	if (NULL == tmp_vec)
	{
		return NULL;
	}
	
	heap->vector = tmp_vec;
	
	HeapifyDown(heap, 0);
	
	return peek;
}

/*-------------------------------HeapPeek----------------------------*/
void *HeapPeek(const heap_t *heap)
{
	vector_t *vector = NULL;
	
	assert(NULL != heap);
	assert(!HeapIsEmpty(heap));
	
	vector = GetVector(heap);
	
	return (GetValue(vector, 0));
}

/*-------------------------------HeapRemove----------------------------*/
void *HeapRemove(heap_t *heap, void *data, heap_is_match_t is_match, 
				void *param)
{
	size_t idx = 0;
	void *removed_data = NULL;
	vector_t *tmp_vec = NULL;
	
	assert(NULL != heap);
	assert(NULL != is_match);
	
	if (FindIsMatch(heap, data, is_match, &idx))
	{
		--idx;
		removed_data = GetValue(GetVector(heap), idx);
		
		Swap(HeapGetElem(heap, idx), HeapGetElem(heap, HeapSize(heap) - 1));
			
		tmp_vec = VectorPopBack(GetVector(heap));
		if (NULL == tmp_vec)
		{
			return NULL;
		}
		
		heap->vector = tmp_vec;
		
		HeapifyDown(heap, idx);
	}
	
	(void)param;
	
	return removed_data;
}

/*-------------------------------HeapIsEmpty----------------------------*/
int HeapIsEmpty(const heap_t *heap)
{
	vector_t *vector = NULL;
	
	assert(NULL != heap);
	
	vector = GetVector(heap);
	
	return (0 == VectorSize(vector));
}

/*-------------------------------HeapSize----------------------------*/
size_t HeapSize(const heap_t *heap)
{
	vector_t *vector = NULL;
	
	assert(NULL != heap);
	
	vector = GetVector(heap);
	
	return (VectorSize(vector));
}

/*-----------------------------------------------------------------------*/
/*-----------------------------Static Functions--------------------------*/
/*-----------------------------------------------------------------------*/

static void HeapifyUp(heap_t *heap, size_t idx)
{
	void *heap_data = NULL;
	void *new_data = NULL;
	size_t parent_idx = 0;
	
	assert(NULL != heap);
	
	if (0 >= idx)
	{
		return;
	}
	
	parent_idx = GetParentIdx(idx);
	heap_data = GetValue(GetVector(heap), parent_idx);
	new_data = GetValue(GetVector(heap), idx);
	
	if (0 >= heap->cmp(heap_data, new_data, heap->param))
	{
		return;
	}
	
	Swap(HeapGetElem(heap, idx), HeapGetElem(heap, parent_idx));
	HeapifyUp(heap, parent_idx);
}

static void HeapifyDown(heap_t *heap, size_t idx)
{
	void *max_data = NULL;
	size_t max_idx = idx;
	size_t left_idx = GetLeftIdx(idx);
	size_t right_idx = GetRightIdx(idx);
	size_t size = 0;
	
	assert(NULL != heap);
	
	size = HeapSize(heap);

	max_data = GetValue(GetVector(heap), max_idx);
	
	if (left_idx < size && 0 < heap->cmp(max_data, 
							GetValue(GetVector(heap), left_idx), heap->param))
	{
		max_idx = left_idx;
	}
	if (right_idx < size && 0 < heap->cmp(max_data, 
							GetValue(GetVector(heap), right_idx), heap->param))
	{
		max_idx = right_idx;
	}
	
	if (idx != max_idx)
	{
		Swap(HeapGetElem(heap, idx), HeapGetElem(heap, max_idx));
		
		HeapifyDown(heap, max_idx);
	}
}

static heap_t *InitHeap(heap_t *heap, heap_cmp_t cmp, void *param)
{
	assert(NULL != heap);
	assert(NULL != cmp);
	
	heap->vector = VectorCreate(MIN_CAPACITY, ELEM_SIZE);
	if (NULL == heap->vector)
	{
		free(heap);
		heap = NULL;
		return NULL;
	}
	
	heap->cmp = cmp;
	heap->param = param;
	
	return heap;
}

static int FindIsMatch(heap_t *heap, void *data, heap_is_match_t is_match, 
						size_t *idx)
{
	size_t size = 0;
	bool_t found = FALSE;
	
	assert(NULL != heap);
	assert(NULL != is_match);
	
	size = HeapSize(heap);
	
	while (!found && *idx < size)
	{
		found = is_match(GetValue(GetVector(heap), *idx), data);
		++(*idx);
	}
	
	return found;
}

static vector_t *GetVector(const heap_t *heap)
{
	assert(NULL != heap);
	
	return heap->vector;
}

static void *HeapGetElem(heap_t *heap, size_t index)
{
	assert(NULL != heap);

	return (VectorGetAccessElement(GetVector(heap), index));
}

static void *GetValue(vector_t *vec, size_t index)
{
	assert(NULL != vec);
	
	return (*(void **)VectorGetAccessElement(vec, index));
}

static size_t GetParentIdx(size_t index)
{
	assert(0 < index);
	
	return ((index - 1) / 2);
}

static size_t GetLeftIdx(size_t index)
{	
	return (2 * index + 1);
}

static size_t GetRightIdx(size_t index)
{
	return (2 * index + 2);
}

static void Swap(void *elem_a, void *elem_b)
{
	size_t *elem1 = NULL;
	size_t *elem2 = NULL;
	
	assert(NULL != elem_a);
	assert(NULL != elem_b);
	
	elem1 = (size_t *)elem_a;
	elem2 = (size_t *)elem_b;
	
	*elem1 = *elem1 ^ *elem2;
	*elem2 = *elem1 ^ *elem2;
	*elem1 = *elem1 ^ *elem2;
}
