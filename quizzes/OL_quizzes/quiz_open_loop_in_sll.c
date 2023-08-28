#include <stddef.h> /*NULL*/
#include <assert.h> /*assert*/
#include <stdio.h> /*printf*/
typedef struct node
{
	void *data;
	struct node *next;
} node_t;

typedef enum
{
	SUCCESS = 0,
	FAIL
} status_t;

typedef enum
{
	TRUE = 1,
	FALSE = 0
} bool_t;

int HasLoop(const node_t *head);
int OpenLoop(node_t *head);
void HasLoopTest(void);
void OpenLoopTest(void);
void PrintTestResult(int status);

int main(void)
{
	HasLoopTest();
	OpenLoopTest();
	return 0;
}

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

void HasLoopTest(void)
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
	
	PrintTestResult(status);
}

void OpenLoopTest(void)
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
	
	PrintTestResult(status);
}

void PrintTestResult(int status)
{
	if (SUCCESS == status)
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED\n");
	}
}
