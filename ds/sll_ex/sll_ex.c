/*****************************************/
/*   Developer: Gali Aviyam	           	 */
/*   Project: SList Exercises            */				         
/*   Date: 11/12/22	                	 */
/*   Reviewer: Yuval                     */
/*****************************************/

#include <stddef.h> /*NULL*/
#include <assert.h> /*assert*/

#include "sll_ex.h" /*header file*/

typedef enum
{
	TRUE = 1,
	FALSE = 0
} bool;

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


