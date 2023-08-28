#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


#define SIZE 1024
#define Q_SIZE 5

typedef struct node
{
	void *data;
	struct node *next;
} node_t;

typedef struct slist
{
	node_t *head;
	node_t *end;
} slist_t;

typedef struct d_node d_node_t;
struct d_node
{
	void *data;
	d_node_t *prev;
	d_node_t *next;
};

typedef struct Queue
{
	char m_queue[Q_SIZE];
	size_t m_element_in_queue;
	size_t m_first_element_index;
} queue_t;

typedef enum bool
{
	TRUE = 1,
	FALSE = 0
} bool_t;

typedef enum status
{
	SUCCESS = 0,
	FAIL
} status_t;


node_t *Flip(node_t *head);
int HasLoop(const node_t *head);
int OpenLoop(node_t *head);
int IsIntersected(node_t *head_1, node_t *head_2);
void SeparateLists(node_t *head_1, node_t *head_2);
node_t *FindIntersection(node_t *head_1, node_t *head_2);
int FindMissingNum(int *arr);
int QueuePushChar(queue_t *queue, char c);
int QueuePopChar(queue_t *queue);

static void PrintTestResult(int status);
static void FlipTest(void);
static void HasLoopTest(void);
static void OpenLoopTest(void);
static void TestIntersection(void);
static void FindMissingNumTest(void);
static void QueueTest(void);

int main(void)
{
	FlipTest();
	HasLoopTest();
	OpenLoopTest();
	TestIntersection();
	FindMissingNumTest();
	QueueTest();
	
	return 0;
}

/*********************************Question 1**********************************/
typedef struct fsa
{
	size_t first_free;
} fsa_t;

/*--------------------------------FSAAllocate--------------------------------*/
void *FSAAllocate(fsa_t *fsa)
{
	void *block = NULL;
	
	assert(NULL != fsa);
	
	if (0 != fsa->first_free)
	{
		block = (char *)fsa + fsa->first_free;
		fsa->first_free = *(size_t *)block;
	}
	
	return block;
}

/*----------------------------------FSAFree----------------------------------*/
void FSAFree(fsa_t *fsa, void *block)
{
	assert(NULL != fsa);
	assert(NULL != block);
	
	*(size_t *)block = fsa->first_free;
	fsa->first_free = (char *)block - (char *)fsa;
}

typedef struct vsa
{
	size_t pool_size;
} vsa_t;

typedef struct block
{
	size_t block_size;
	#ifndef NDEBUG
		vsa_t *vsa;
	#endif
} block_t;
#define	WORD_SIZE sizeof(size_t)
#define MIN_POOL_SIZE 64
#define ADDR_END_OF_POOL(vsa) (((char *)vsa) + (vsa->pool_size))
#define START_OF_POOL(vsa) (((char *)vsa) + (sizeof(vsa_t)))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define START_OF_BLOCK(block) (((char *)block) + (sizeof(block_t)))
static size_t GetPadding(size_t block_size);
static block_t *InitBlock(block_t *block, size_t block_size, vsa_t *vsa);
static int IsFreeBlock(block_t *block);
static block_t *NextBlock(block_t *block);
static void SetBlockFree(block_t *block);
static void SetBlockNotFree(block_t *block);
static int IsBlockInPool(vsa_t *vsa, char *block);
static size_t GetBlockSize(block_t *block);
static void SetBlockSize(block_t *block, size_t new_size);
static void SplitBlock(block_t *block, size_t block_size, vsa_t *vsa);
static int IsEndOfPool(vsa_t *vsa, block_t *block);
static void Defrag(vsa_t *vsa, block_t *block);
static block_t *GetBlockHeader(char *block);
static block_t *NextFreeBlock(vsa_t *vsa, block_t *block);
/*--------------------------------VSAAllocate--------------------------------*/
void *VSAAllocate(vsa_t *vsa, size_t block_size)
{
	block_t *block_runner = NULL;
	
	assert(NULL != vsa);
	
	block_size += GetPadding(block_size);
	block_runner = (block_t *)START_OF_POOL(vsa);
	block_runner = NextFreeBlock(vsa, block_runner);
	Defrag(vsa, block_runner);
	
	while (IsBlockInPool(vsa, (char *)block_runner) && 
			GetBlockSize(block_runner) < block_size)
	{
		block_runner = NextBlock(block_runner);
		block_runner = NextFreeBlock(vsa, block_runner);
		Defrag(vsa, block_runner);
	}
	if (!IsBlockInPool(vsa, (char *)block_runner))
	{
		return NULL;
	}
	
	if (GetBlockSize(block_runner) >= (block_size + sizeof(block_t)))
	{
		SplitBlock(block_runner, block_size, vsa);
	}
	SetBlockNotFree(block_runner);
	
	return (START_OF_BLOCK(block_runner));
}

static size_t GetPadding(size_t block_size)
{
	return ((WORD_SIZE - (block_size % WORD_SIZE)) % WORD_SIZE);
}

static block_t *InitBlock(block_t *block, size_t block_size, vsa_t *vsa)
{
	SetBlockSize(block, block_size);
	SetBlockFree(block);;
	
	#ifndef NDEBUG
		block->vsa = vsa;
	#endif
	
	return block;
}

static int IsFreeBlock(block_t *block)
{
	assert(NULL != block);
	
	return (0 == ((block->block_size) & ((size_t)1)));
}

static block_t *NextBlock(block_t *block)
{
	block_t *next_block = NULL;
	
	assert(NULL != block);
	
	next_block = (block_t *)((char *)block + sizeof(block_t) + 
									GetBlockSize(block));
	
	return next_block;

}

static void SetBlockFree(block_t *block)
{
	assert(NULL != block);

	block->block_size = ((((block->block_size) >> 1) << 1));
}

static void SetBlockNotFree(block_t *block)
{
	assert(NULL != block);
	
	block->block_size = ((block->block_size) | ((size_t)1));
}

static size_t GetBlockSize(block_t *block)
{
	assert(NULL != block);
	
	return (((block->block_size) >> 1) << 1);
}

static void SetBlockSize(block_t *block, size_t new_size)
{
	assert(NULL != block);
	
	block->block_size = new_size;
}

static int IsBlockInPool(vsa_t *vsa, char *block)
{
	assert(NULL != vsa);
	assert(NULL != block);
	
	return (block < ADDR_END_OF_POOL(vsa) && ((char *)vsa < block));
}

static int IsEndOfPool(vsa_t *vsa, block_t *block)
{
	assert(NULL != vsa);
	assert(NULL != block);
	
	return ((ADDR_END_OF_POOL(vsa)) == ((char *)block));
}

static void SplitBlock(block_t *block, size_t block_size, vsa_t *vsa)
{
	block_t *new_block = NULL;
	size_t new_block_size = 0;	

	assert(NULL != vsa);
	assert(NULL != block);
	
	new_block_size = GetBlockSize(block) - block_size - sizeof(block_t);
	SetBlockSize(block, block_size);
	new_block = NextBlock(block);
	InitBlock(new_block, new_block_size, vsa);
}

static block_t *GetBlockHeader(char *block)
{
	assert(NULL != block);
	
	block -= sizeof(block_t);
	return ((block_t *)block);
}

static void Defrag(vsa_t *vsa, block_t *block)
{
	block_t *next_block = NULL;

	assert(NULL != block);	
	assert(NULL != vsa);
	
	if (!IsEndOfPool(vsa, block))
	{
		next_block = NextBlock(block);

		while ((!IsEndOfPool(vsa, next_block)) && (IsFreeBlock(next_block))) 
		{
			block->block_size += (sizeof(block_t) + GetBlockSize(next_block));
			next_block = NextBlock(next_block);
		}
	}
}

static block_t *NextFreeBlock(vsa_t *vsa, block_t *block)
{
	assert(NULL != block);
		
	while (IsBlockInPool(vsa, (char *)block) && !IsFreeBlock(block))
	{
		block = NextBlock(block);
	}
	
	return block;
}
/*----------------------------------VSAFree----------------------------------*/
void VSAFree(void *block)
{
	block_t *block_to_free = NULL;
	
	assert(NULL != block);
	
	block_to_free = GetBlockHeader((char *)block);
	assert(IsBlockInPool(block_to_free->vsa, (char *)block_to_free));
	
	SetBlockFree(block_to_free);
}
/*********************************Question 2**********************************/
node_t *Flip(node_t *head)
{
	node_t *prev = NULL;
	node_t *curr = NULL;
	node_t *next = NULL;
	
	assert(NULL != head);
	curr = head;
	
	while (NULL != curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	head = prev;
	
	return head;
}

/********************************Question 4 a*********************************/
int HasLoop(const node_t *head)
{
	node_t *slow = NULL;
	node_t *fast = NULL;
	int is_loop = FALSE;
	
	assert(NULL != head);
		
	slow = (node_t *)head;
	fast = (node_t *)head->next;

	while (NULL != fast && NULL != fast->next && !is_loop)
	{
		if (slow == fast)
		{
			is_loop = TRUE;
		}
		slow = slow->next;
		fast = fast->next->next;
	}
	
	return is_loop;
}

/********************************Question 4 b*********************************/
int OpenLoop(node_t *head)
{

	node_t *slow = NULL;
	node_t *fast = NULL;
	
	assert(NULL != head);
		
	slow = (node_t *)head;
	fast = (node_t *)head->next;

	while (NULL != fast && NULL != fast->next)
	{
		if (slow->next == fast->next)
		{
			slow->next = NULL;
			return SUCCESS;
		}
		slow = slow->next;
		fast = fast->next->next;
	}
	
	return FAIL;
}

/********************************Question 5 a*********************************/
int IsIntersected(node_t *head_1, node_t *head_2)
{
	assert(head_1);
	assert(head_2);
	
	return ((FindIntersection(head_1, head_2)) ? 1 : 0);
}

/********************************Question 5 b*********************************/
void SeparateLists(node_t *head_1, node_t *head_2)
{
	node_t *intersection = NULL;
	node_t *runner2 = NULL;
	
	assert(head_1);
	assert(head_2);
	
	intersection = FindIntersection(head_1, head_2);
	runner2 = head_2;
	
	while (runner2->next != intersection)
	{
		runner2 = runner2->next;
	}
	
	runner2->next = NULL;
}

node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	node_t *runner1 = NULL;
	node_t *runner2 = NULL;
	node_t *mutual = NULL;
		
	assert(NULL != head_1);
	assert(NULL != head_2);

	if (head_1 == head_2)
    {
        mutual = head_1;
    }
	
	runner1 = head_1;
	runner2 = head_2;
	
	
	while (runner1 != runner2 && !mutual)
	{
		runner1 = runner1->next;
		runner2 = runner2->next;
		
		if (runner1 == runner2)
		{
			mutual = runner1;
		}
		else
		{
			if (NULL == runner1)
			{
				runner1 = head_2;
			}
			
			if (NULL == runner2)
			{
				runner2 = head_1;
			}
		}
	}
	return mutual;
}

/*********************************Question 6**********************************/
node_t *SlistRemove(node_t *where)
{
	node_t *tmp = NULL;
	
	assert(NULL != where);
	
	tmp = where->next;
	
	where->data = tmp->data;
	where->next = tmp->next;
	
	if (NULL == where->next)
	{
		((slist_t *)(where->data))->end = where;
	}

	free(tmp);
	tmp = NULL;
	
	return where;
}

/*********************************Question 7**********************************/
void InsertBefore(d_node_t *where, d_node_t *node)
{
	assert(where);
	assert(node);
	
	where->prev->next = node;
	node->prev = where->prev;
	node->next = where;
	where->prev = node;
}

void DlistRemove(d_node_t *node)
{
	assert(node);
	
	node->prev->next = node->next;
	node->next->prev = node->prev;
}

/*********************************Question 8**********************************/
int FindMissingNum(int *arr)
{
	int mask = 0;
	int i = 0;
	
	assert(arr);
	
	for (i = 0; i < SIZE; ++i)
	{
		mask ^= i;
		mask ^= arr[i];
	}
	
	return (mask ^ SIZE);

}

/*********************************Question 9**********************************/
typedef size_t bitmap_t;

static int CountSet(bitmap_t bitmap);

int IsIn(bitmap_t bitmap, int index)
{
	if (bitmap & ((bitmap_t)1 << index))
	{
		return 1;
	}
	
	bitmap &= (((bitmap_t)1 << index) - 1); 
	
	return (CountSet(bitmap) & 1);
}

static int CountSet(bitmap_t bitmap)
{
	int counter = 0;
	
	while (bitmap)
	{
		bitmap &= (bitmap - 1);
		++counter;
	}
	
	return counter;
}

/*********************************Question 10*********************************/
int QueuePushChar(queue_t *queue, char c)
{
	int status = SUCCESS;
	size_t i = 0;
	
	assert(queue);
	
	if (queue->m_element_in_queue < Q_SIZE)
	{
		i = (queue->m_first_element_index + queue->m_element_in_queue) % Q_SIZE;
		queue->m_queue[i] = c;
		++queue->m_element_in_queue;
	}
	else
	{
		status = FAIL;
	}
	
	return status;
}

int QueuePopChar(queue_t *queue)
{
	int status = SUCCESS;
	
	assert(queue);
	
	if (queue->m_element_in_queue)
	{
		--queue->m_element_in_queue;
		queue->m_first_element_index = ((queue->m_first_element_index + 1) % Q_SIZE);
	}
	else
	{
		status = FAIL;
	}
	
	return status;
}




/*********************************TESTS*********************************/

static void PrintTestResult(int status)
{
	if (SUCCESS == status)
	{
		printf("\033[0;32mPASSED\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAILED\033[0m\n");
	}
}

static void FlipTest(void)
{
	int status = FAIL;	
	
	node_t node1 = {0};
    node_t node2 = {0};
    node_t node3 = {0};
    node_t node4 = {0};

	
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = NULL;
	
	if (&node4 == Flip(&node1))
	{
		status = SUCCESS;
	}
	
	printf("Question 2: ");
	PrintTestResult(status);
}

static void HasLoopTest(void)
{
	int status = FAIL;	
	
	node_t node1 = {(void *)1, NULL};
    node_t node2 = {(void *)2, NULL};
    node_t node3 = {(void *)3, NULL};
    node_t node4 = {(void *)4, NULL};
    
    node_t node5 = {(void *)5, NULL};
    node_t node6 = {(void *)6, NULL};
    node_t node7 = {(void *)7, NULL};
    node_t node8 = {(void *)8, NULL};

	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = NULL;

	node5.next = &node6;
	node6.next = &node7;
	node7.next = &node8;
	node8.next = &node6;
	
	if (1 == HasLoop(&node5) && 0 == HasLoop(&node1))
	{
		status = SUCCESS;
	}
	printf("Question 4 a: ");
	PrintTestResult(status);
}

static void OpenLoopTest(void)
{
	int status = FAIL;	
	
	node_t node5 = {(void *)5, NULL};
    node_t node6 = {(void *)6, NULL};
    node_t node7 = {(void *)7, NULL};
    node_t node8 = {(void *)8, NULL};

	node5.next = &node6;
	node6.next = &node7;
	node7.next = &node8;
	node8.next = &node6;
	
	OpenLoop(&node5);
	
	if (0 == HasLoop(&node5))
	{
		status = SUCCESS;
	}
	printf("Question 4 b: ");
	PrintTestResult(status);
}

static void TestIntersection(void)
{
	node_t head1 = {(void *)1, NULL};
	node_t second1 = {(void *)2, NULL};
	node_t third1 = {(void *)3, NULL};
	
	node_t head2 = {(void *)4, NULL};
	node_t second2 = {(void *)5, NULL};
	node_t third2 = {(void *)6, NULL};
	node_t fourth2 = {(void *)7, NULL};
	
	node_t head3 = {(void *)8, NULL};
	node_t second3 = {(void *)9, NULL};
	node_t third3 = {(void *)10, NULL};
	node_t fourth3 = {(void *)11, NULL};
	
	head1.next = &second1;
	second1.next = &third1;
	third1.next = &fourth3;

	head2.next = &second2;
	second2.next = &third2;
	third2.next = &fourth2;
	fourth2.next = NULL;

	head3.next = &second3;
	second3.next = &third3;
	third3.next = &fourth3;
	fourth3.next = NULL;
	
	printf("Question 5 IsIntersected: ");
	if (IsIntersected(&head3, &head1) && !IsIntersected(&head2, &head1))
	{
		printf("\033[0;32mPASSED\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAILED\033[0m\n");
	}
	
	printf("Question 5 SeparateLists: ");
	SeparateLists(&head3, &head1);
	if (IsIntersected(&head3, &head1))
	{
		printf("\033[0;31mFAILED\033[0m\n");
	}
	else
	{
		printf("\033[0;32mPASSED\033[0m\n");
	}
}

static void FindMissingNumTest(void)
{
	int arr[SIZE] = {0};
	size_t i = 0;
	
	for (i = 0; i < SIZE; ++i)
	{
		arr[i] = i;
	}
	printf("Question 8 Find Missing Number:\n");
	
	printf("%d\n", FindMissingNum(arr));
	
	arr[123] = 1024;
	printf("%d\n", FindMissingNum(arr));
	
	arr[38] = 123;
	printf("%d\n", FindMissingNum(arr));
	
	arr[906] = 38;
	printf("%d\n", FindMissingNum(arr));
}

static void QueueTest(void)
{
	queue_t queue = {0};
	size_t i = 0;
	char ch = 0;
	int status = SUCCESS;
	
	printf("Question 10 Queue:\n");
	
	for	(i = 0; i < Q_SIZE; ++i)
	{
		ch = (i % 26) + 'A';
		status += QueuePushChar(&queue, ch);
	}
	printf("Push: ");
	PrintTestResult(status);
	
	status = SUCCESS;

	for	(i = 0; i < Q_SIZE; ++i)
	{
		status += QueuePopChar(&queue);
	}
	
	printf("Pop: ");
	PrintTestResult(status);
}

