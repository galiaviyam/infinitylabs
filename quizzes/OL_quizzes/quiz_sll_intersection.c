#include <stdio.h>	/* printf */
#include <assert.h>	/* assert */

typedef struct node
{
	void *data;
	struct node *next;
} node_t;

static int IsIntersected(node_t *head_1, node_t *head_2);
static void SeparateLists(node_t *head_1, node_t *head_2);
static node_t *FindIntersection(node_t *head_1, node_t *head_2);

int main(void)
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
		
	printf("IsIntersected: ");
	if (IsIntersected(&head3, &head1) && !IsIntersected(&head2, &head1))
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED\n");
	}
	
	printf("SeparateLists: ");
	SeparateLists(&head3, &head1);
	if (IsIntersected(&head3, &head1))
	{
		printf("PASSED\n");
	}
	else
	{
		printf("PASSED\n");
	}
	
	return 0;
}

static int IsIntersected(node_t *head_1, node_t *head_2)
{
	assert(head_1);
	assert(head_2);
	
	return ((FindIntersection(head_1, head_2)) ? 1 : 0);
}

static void SeparateLists(node_t *head_1, node_t *head_2)
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

static node_t *FindIntersection(node_t *head_1, node_t *head_2)
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
