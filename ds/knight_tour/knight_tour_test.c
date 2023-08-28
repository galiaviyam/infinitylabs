/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Knight Tour      		*/
/*   Date:		14/02/23				*/
/*	 Reviewer:	Moriah					*/
/*										*/
/****************************************/

#include <stdio.h> /* printf */
#include <assert.h> /* assert */

#include "knight_tour.h" /* knight tour header */

typedef enum status
{
	SUCCESS = 0,
	FAIL
} status_t;

static void PrintPath(size_t *path, size_t size);
static void TestStatusResult(int result);

int main(void)
{
	size_t path[64] = {0};
	
	TestStatusResult(KnightTour(path, 0));
	PrintPath(path, 64);
	
	TestStatusResult(KnightTour(path, 3));
	PrintPath(path, 64);
	
	TestStatusResult(KnightTour(path, 7));
	PrintPath(path, 64);
	
	
	TestStatusResult(KnightTourWarnsdorff(path, 0));
	PrintPath(path, 64);
	
	TestStatusResult(KnightTourWarnsdorff(path, 3));
	PrintPath(path, 64);
	
	TestStatusResult(KnightTourWarnsdorff(path, 7));
	PrintPath(path, 64);
	
	return 0;
}

static void PrintPath(size_t *path, size_t size)
{
	size_t i = 0;
		
	assert(NULL != path);
	
	printf("the path is:\n");
	
	for (i = 0; i < size; ++i)
	{
		printf("%lu  ", path[i]);
		
		if (7 == (i % 8))
		{
			printf("\n");
		}
	}
	printf("\n");
}


static void TestStatusResult(int result)
{
	if (result == SUCCESS)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}
