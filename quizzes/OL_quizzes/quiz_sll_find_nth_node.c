#include <stdio.h>	/* printf */
#include <assert.h>	/* assert */

typedef struct node
{
	void *data;
	struct node *next;
} node_t;

static node_t *FindNthFromEnd(node_t *head, size_t n);

int main(void)
{
	node_t node1 = {0};
	node_t node2 = {0};
	node_t node3 = {0};
	node_t node4 = {0};
	node_t node5 = {0};
	
	node5.next = NULL;
	
	node4.next = &node5;
	
	node3.next = &node4;
	
	node2.next = &node3;
	
	node1.next = &node2;
	
	printf("FindNthFromEnd: ");
	
	if (FindNthFromEnd(&node1, 2) == &node3)
	{
		printf("SUCCESS\n");
	}
	else
	{
		printf("FAIL\n");
	}
	
	return 0;
}

static node_t *FindNthFromEnd(node_t *head, size_t n)
{
	node_t *runner = head;
	size_t i = 0;
	
	while (NULL != runner->next && i < n)
	{
		runner = runner->next;
		++i;
	}
	
	while (NULL != runner->next)
	{
		head = head->next;
		runner = runner->next;
	}
	
	return head;
}
