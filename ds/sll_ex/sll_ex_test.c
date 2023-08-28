/*****************************************/
/*   Developer: Gali Aviyam	           	 */
/*   Project: SList Exercises            */				         
/*   Date: 11/12/22	                	 */
/*   Reviewer: Yuval                     */
/*****************************************/

#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "sll_ex.h"/*header file*/

typedef enum
{
	SUCCESS = 0,
	FAIL
} status_t;

int FlipTest(void);
int HasLoopTest(void);
int FindIntersectionTest(void);
void RunTests(void);
void TestResult(int status);

int main(void)
{
	RunTests();
	return 0;
}
void RunTests(void)
{
	printf("Flip:\t\t\t");
	TestResult(FlipTest());
	printf("HasLoop:\t\t");
	TestResult(HasLoopTest());
	printf("FindIntersection:\t");
	TestResult(FindIntersectionTest());
}

void TestResult(int status)
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

int FlipTest(void)
{
	int status = 1;	
	
	node_t node1 = {(void *)1, NULL};
    node_t node2 = {(void *)2, NULL};
    node_t node3 = {(void *)3, NULL};
    node_t node4 = {(void *)4, NULL};

	
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = NULL;
	
	if (&node4 == Flip(&node1))
	{
		status = 0;
	}
	
	return status;
}

int HasLoopTest(void)
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
	
	return status;
}

int FindIntersectionTest(void)
{
	int status = 1;	
	
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
		
	if (&fourth3 == FindIntersection(&head3, &head1) &&
		NULL == FindIntersection(&head2, &head1))
	{
		status = 0;
	}
	
	return status;
}
