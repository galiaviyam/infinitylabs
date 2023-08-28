#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

static void TestNumResultEqual(size_t result, size_t expected_result);
static void TestBoolResult(int result);

/*----------------------------- Question 1 ----------------------------------*/

typedef struct int_array
{
    int *data;
    size_t *data_vers;
    size_t size;
    int all_data;
    size_t all_vers;
} int_array_t;

void SetVal(int_array_t *array, int indx, int val)
{
    assert(array);
    *(array->data + indx) = val;
    *(array->data_vers + indx) = array->all_vers;
}

int GetVal(int_array_t *array, int indx)
{
    int val = 0;
    
    assert(array);
    val = array->data[indx];
    
    if (array->all_vers > array->data_vers[indx])
    {
    	val = array->all_data;
    }
    
    return val;
}

void SetAll(int_array_t *array, int val)
{
    assert(array);
    
	array->all_data = val;
	++array->all_vers;
}

int_array_t *CreateIntArray(int size)
{
    int_array_t *arr = (int_array_t *)malloc(sizeof(int_array_t));
	if (NULL == arr)
	{
		return NULL;
	}
	
	arr->data = (int *)calloc(size, sizeof(int));
    if (NULL == arr->data)
	{
		free(arr);
		arr = NULL;
		
		return NULL;
	}
	
	arr->data_vers = (size_t *)calloc(size, sizeof(size_t));
    if (NULL == arr->data_vers)
	{
		free(arr->data);
		arr->data = NULL;
		
		free(arr);
		arr = NULL;
		
		return NULL;
	}
	arr->size = size;
	arr->all_data = 0;
	arr->all_vers = 0;
	
	return arr;
}

void DestroyIntArray(int_array_t *arr)
{
	assert(NULL != arr);
	
	free(arr->data);
	arr->data = NULL;
	
	free(arr->data_vers);
	arr->data_vers = NULL;
	
	free(arr);	
	arr = NULL;
}

void TestQuestion1(void)
{
    int_array_t *arr = CreateIntArray(10);
	if (NULL == arr)
	{
		printf("error!\n");
		return;
	}

	SetVal(arr, 4, 100);

    printf("---------- Question 1 ----------\n");

	TestNumResultEqual(100, GetVal(arr, 4));

	SetAll(arr, 50);

	TestNumResultEqual(50, GetVal(arr, 4));
	
	DestroyIntArray(arr);
}


/*----------------------------- Question 2 ----------------------------------*/
int Cmp(const void *a, const void *b)
{
	return (*(unsigned int *)a > *(unsigned int *)b ? 1 : -1);
}

int FindSumElem(unsigned int *arr, size_t size, unsigned int sum_of_two, 
				unsigned int *elem1, unsigned int *elem2)
{
	unsigned int curr_sum = 0;
	unsigned int *start = NULL;
	unsigned int *end = NULL;
	
	assert(NULL != arr);
	assert(NULL != elem1);
	assert(NULL != elem2);
	assert(0 < size);
	
	qsort(arr, size, sizeof(unsigned int), &Cmp);
	
	start = arr;
	end = arr + size -1;
	
	while (start < end)
	{
		curr_sum = (*start + *end);
		
		if (curr_sum < sum_of_two)
		{
			++start;
		}
			
		else if (curr_sum > sum_of_two)
		{
			--end;
		}
		
		else
		{
			*elem1 = *start;
			*elem2 = *end;
			
			return 0;
		}
	}
	
	return 1;
}


void TestQuestion2(void)
{
	unsigned int arr[5] = {14, 2, 7, 12, 4};
	unsigned int sum = 21;
	unsigned int result[2] = {0};
	
	printf("---------- Question 2 ----------\n");
	FindSumElem(arr, 5, sum, result, (result + 1));
	TestBoolResult(7 == result[0] && 14 == result[1]);
		
}

/*----------------------------- Question 3 ----------------------------------*/
int Find(char *arr, size_t size, char c)
{
	size_t i = 0;
	char check = 1;
	
	for (i = 0; i < size; ++i)
	{
		check *= (arr[i] ^ c);
	}
	
	return (0 == check);
}

void TestQuestion3(void)
{
	char arr[] = {'a', 'b', 'c', 'a', 'w', 'r', 'l'};
	
	printf("---------- Question 3 ----------\n");
	
	TestBoolResult(Find(arr, 7, 'c'));
	TestBoolResult(Find(arr, 7, 'w'));
	TestBoolResult(!Find(arr, 7, 'e'));
	
}

/*----------------------------- Question 4 ----------------------------------*/

void ReverseArray(int *arr, size_t start, size_t end)
{ 
	int tmp = 0;
	
	assert(NULL != arr);
	
	while (start < end) 
	{
		tmp = arr[start]; 
		arr[start] = arr[end]; 
		arr[end] = tmp; 
		++start; 
		--end;
	}
}

void CircularRotate(int *arr, size_t size, size_t rotate)
{ 
	assert(NULL != arr);
	
	ReverseArray(arr, 0, size - 1); 
	ReverseArray(arr, 0, rotate - 1); 
	ReverseArray(arr, rotate, size - 1); 
}
     
void PrintArray(int *arr, size_t size)
{ 
	size_t i = 0;
	
	assert(NULL != arr);
	
	for (i = 0; i < size; i++) 
	{
		printf("%d ", arr[i]);
	}
	
	printf("\n");
}

void TestQuestion4(void)
{
	int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	
	printf("---------- Question 4 ----------\n");
	
	printf("before shift:\n");
	PrintArray(arr1, 9);
	CircularRotate(arr1, 9, 3);
	printf("\nafter shift:\n");
	PrintArray(arr1, 9);
}

/*----------------------------- Question 5 ----------------------------------*/
 
#define ROW 5
#define COL 5
 
int IsSafe(int matrix[][COL], int row, int col, int visited[][COL])
{
    return (row >= 0) && (row < ROW) && (col >= 0)
           && (col < COL)
           && (matrix[row][col] && !visited[row][col]);
}
 
void DFS(int matrix[][COL], int row, int col, int visited[][COL])
{
    static int row_nbr[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    static int col_nbr[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    size_t i = 0;
 
    visited[row][col] = 1;
 
    for (i = 0; i < 8; ++i)
    {    	
        if (IsSafe(matrix, row + row_nbr[i], col + col_nbr[i], visited))
        {
            DFS(matrix, row + row_nbr[i], col + col_nbr[i], visited);        
        }
    }
}
 
int CountIslands(int matrix[][COL])
{
    int visited[ROW][COL] = {0};
    int count = 0;
    size_t i = 0;
    size_t j = 0;
    
    memset(visited, 0, sizeof(visited));
 
    for (i = 0; i < ROW; ++i)
    {    
        for (j = 0; j < COL; ++j)
        {        
            if (matrix[i][j] && !visited[i][j])
            {
                DFS(matrix, i, j, visited);
                ++count;
            }
        }
    }
 
    return count;
}
 
void TestQuestion5(void)
{
	int matrix[][COL] =   { { 1, 1, 0, 0, 0 },
							{ 0, 1, 0, 0, 1 },
							{ 1, 0, 0, 1, 1 },
							{ 0, 0, 0, 0, 0 },
							{ 1, 0, 1, 0, 1 } };

	int matrix1[][COL] =  { { 1, 1, 0, 0, 0 },
							{ 0, 0, 0, 0, 1 },
							{ 1, 0, 0, 1, 1 },
							{ 0, 0, 0, 0, 0 },
							{ 1, 0, 1, 0, 1 } };
							
	printf("---------- Question 5 ----------\n");

	TestNumResultEqual(CountIslands(matrix), 5);
	TestNumResultEqual(CountIslands(matrix1), 6);
}
/*----------------------------- Question 6 ----------------------------------*/
typedef struct mstack
{
	stack_t *stack;
	stack_t *min_stack;
} mstack_t;

void MinStackPush(mstack_t *mstack, int *data)
{
	assert(NULL != mstack);
	assert(NULL != data);
	
	StackPush(mstack->stack, data);
	
	if (StackIsEmpty(mstack->min_stack) || *data < *(int *)StackPeek(mstack->min_stack))
	{
		StackPush(mstack->min_stack, data);
	}
}

void *MinStackPop(mstack_t *mstack)
{
	assert(NULL != mstack);
	
	if (StackPeek(mstack->stack) == StackPeek(mstack->min_stack)) 
	{
		StackPop(mstack->min_stack);
	}
	
	return (StackPop(mstack->stack));
}


void TestQuestion6(void)
{
	mstack_t test_stack = {0};
	size_t capacity = 10;
	int test_buffer[10] = {1, 6, -4, 4, 6 -8, 9, 4, 3, 0};
	size_t i = 0;
	
	test_stack.stack = StackCreate(capacity);
	test_stack.min_stack = StackCreate(capacity);

	printf("---------- Question 6 ----------\n");
	for (i = 0; i < capacity; ++i)
	{
		MinStackPush(&test_stack, &test_buffer[i]);
	}
	
	for (i = 0; i < capacity/2; ++i)
	{
		MinStackPop(&test_stack);
	}
	
	(*(int *)StackPeek(test_stack.min_stack) == -4) ? 
			printf("\033[0;32mPASS\033[0m\n"): printf("\033[0;31mFAIL\033[0m\n");
	
	StackDestroy(test_stack.stack); 
	StackDestroy(test_stack.min_stack);
}

/*----------------------------- Question 7 ----------------------------------*/
int CheckParenthesis(const char *str)
{
	char *runner = NULL;
	stack_t *stack = NULL;
	int res = 0;
	
	assert(NULL != str);
	
	runner = (char *)str;
	
	stack = StackCreate(strlen(str));
	
	while ('\0' != *runner)
	{
		switch (*runner)
		{
			case '{':
			case '(':
			case '[':
			case '<':
			{
				StackPush(stack, runner);
				++runner;
				break;
			}
			case ')':
            {
            	if ('(' == *(char *)StackPeek(stack))
            	{
            		StackPop(stack);
            	}
            	++runner;
            	break;
            }
            case '}':
            {
                if('{' == *(char *)StackPeek(stack))
                {
                    StackPop(stack);
                }
                ++runner;
                break;
            }
            case ']':
            {
                 if('[' == *(char *)StackPeek(stack))
                {
                    StackPop(stack);
                }
                ++runner;
                break;
            }
            case '>':
            {
                 if('<' == *(char *)StackPeek(stack))
                {
                    StackPop(stack);
                }
                ++runner;
                break;
            }
            default:
            {
            	++runner;
            	break;
            }
            	
        }
    }
    res = ((StackIsEmpty(stack)) ? 1 : 0);
    
    StackDestroy(stack);
    
    return res;
}

void TestQuestion7(void)
{
	printf("---------- Question 7 ----------\n");
	
	TestBoolResult(CheckParenthesis("(x + 3 * [4 + 6]) <>"));
	TestBoolResult(CheckParenthesis("{}{[]}{()}"));
	TestBoolResult(!CheckParenthesis("{}{}{([)]}"));	
	TestBoolResult(CheckParenthesis("(a{a}cd)"));
}

/*----------------------------- Question 8 b --------------------------------*/
int RecMult(int num_a, int num_b)
{
	if (0 == num_b)
	{
		return 0;
	}
	else if (0 < num_b)
	{
		return (num_a + RecMult(num_a, num_b - 1));
	}
	else
	{
		return (-RecMult(num_a, -num_b));
	}
}

int RecDiv(int num_a, int num_b)
{
	if (0 == num_a || 0 == num_b)
	{
		return num_a;
	}
	else if (-1 == num_b)
	{
		return -num_a;
	}
	else if (num_a < num_b)
	{
		return 0;
	}
	else
	{
		return (1 + RecDiv(num_a - num_b, num_b));
	}
}

void TestQuestion8b(void)
{	
	printf("---------- Question 8 b --------\n");
	
	TestNumResultEqual(RecMult(1, 10), 10);
	TestNumResultEqual(RecMult(7, 2), 14);
	TestNumResultEqual(RecMult(0, 3), 0);
	
	TestNumResultEqual(RecDiv(1, 10), 0);
	TestNumResultEqual(RecDiv(14, 2), 7);
	TestNumResultEqual(RecDiv(0, 3), 0);
}

/*----------------------------- Question 8 c --------------------------------*/
int RecInc(int num)
{
	if (0 == num)
	{
		return 1;
	}
	else if (0 > num)
	{
		return -(RecInc(-num - 1) - 1);
	}
	else
	{
		return -(~RecInc(num - 1));
	}
}

void TestQuestion8c(void)
{	
	printf("---------- Question 8 c --------\n");
	
	TestNumResultEqual(RecInc(-3), -2);
	TestNumResultEqual(RecInc(7), 8);
	TestNumResultEqual(RecInc(0), 1);	
}

/*----------------------------- Question 9 c --------------------------------*/
typedef struct node
{
	int data;
	struct node *next;
} node_t;

node_t *ListPivotArrange(node_t *head, int pivot)
{
	node_t *smaller = NULL;
	node_t *bigger = NULL;
	node_t *next_node = NULL;
	node_t *end = NULL;
	
	while (NULL != head)
	{
		next_node = head->next;
		
		if (head->data < pivot)
		{
			head->next = smaller;
			smaller = head;
		}
		else
		{
			head->next = bigger;
			bigger = head;
		}
		
		head = next_node;
	}
		
	if (NULL == smaller)
	{
		return bigger;
	}
	
	end = smaller;
	while (NULL != end->next)
	{
		end	= end->next;
	}
	
	end->next = bigger;
	
	return smaller;
}

void TestQuestion9(void)
{	
	node_t arr[5] = {{5, NULL}, {7, NULL}, {1, NULL}, {2, NULL}, {9, NULL}};
	node_t *runner = NULL;
	int pivot = 3;
	int i = 0;
	
	printf("---------- Question 9 c --------\n");
	arr[0].next = &arr[1];
	arr[1].next = &arr[2];
	arr[2].next = &arr[3];
	arr[3].next = &arr[4];
	
	runner = ListPivotArrange(&arr[0], pivot);
	
	for (i = 0; i < 5; ++i)
	{
		printf("|%d| -> ", runner->data);
		runner = runner->next;
	}
	printf("NULL\n");
}

/*----------------------------- Question 10 ---------------------------------*/

void SwapChar(char *a, char *b)
{
	char tmp = 0;
	
	assert(NULL != a);
	assert(NULL != b);
	
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void PrintPermutations(char *str, size_t begin, size_t end)
{
	size_t i = 0;
	
	assert(NULL != str);
	
	if (begin == end)
	{
		printf("%s\n", str);
	}
	else
	{
		for (i = begin; i <= end; ++i)
		{
			SwapChar((str + begin), (str + i));
			PrintPermutations(str, begin + 1, end);
			SwapChar((str + begin), (str + i));
		}
	}
}

void TestQuestion10(void)
{
	char str[] = "live";
	printf("---------- Question 10 ---------\n");
	printf("The permutations of \"%s\" are:\n", str);
	
	PrintPermutations(str, 0 , 3);
}

/*-------------------------- Question 13 Iter -------------------------------*/
typedef enum status
{
	SUCCESS = 0,
	FAIL
} status_t;

typedef enum direction
{
	LEFT = 0,
	RIGHT,
	NUM_OF_CHILD
}direction_t;

typedef struct bst_node bst_node_t;
struct bst_node
{
	int data;
	bst_node_t *parent;
	bst_node_t *children[NUM_OF_CHILD];
};

typedef struct bst
{
	bst_node_t *root;
	bst_node_t *end;
} bst_t;

bst_node_t *BSTInsert(bst_t *bst, int data)
{
	bst_node_t *runner = NULL;
	bst_node_t *parent = NULL;
	bst_node_t *new_node = NULL;
	int direction = LEFT;
	
	assert(NULL != bst);
	
	new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
	if (NULL == new_node)
	{
		return NULL;
	}
	
	runner = bst->root;
	parent = bst->end;
	
	while (NULL != runner)
	{
		parent = runner;

		if (data > runner->data)
		{
			direction = RIGHT;
			runner = runner->children[RIGHT];
		}
		else
		{
			direction = LEFT;
			runner = runner->children[LEFT];
		}
	}
	
	parent->children[direction] = new_node;
	new_node->parent = parent;
	new_node->data = data;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	
	return new_node;
}

void Print2DTree(bst_node_t* root, int space)
{
	int i = 0;
	if (root == NULL)
	{
		return;
	}
 
    space += 10;
 
    Print2DTree(root->children[RIGHT], space);
 
    printf("\n");
    for (i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);
 
    Print2DTree(root->children[LEFT], space);
}

void TestQuestion13Iter(void)
{
	int data[5] = {8,4,10,2,6};
	bst_node_t arr[5] = {0};
	bst_node_t *new_node = NULL;
	bst_t bst = {0};
	size_t i = 0;
	
	bst.end = arr;
	bst.root = bst.end;
	
	for (i = 0; i < 5; ++i)
	{
		new_node = BSTInsert(&bst, data[i]);		
	}
	(void)new_node;
	
	printf("-------- Question 13 iter --------\n");
	Print2DTree(bst.root, 0);
}

/*-------------------------- Question 13 Rec --------------------------------*/
bst_node_t *RecInsertHelper(bst_node_t *node, bst_node_t *curr)
{
	direction_t direction = LEFT;
	
	assert(NULL != node);
	
	if (NULL == curr)
	{
		return node;
	}
	
	direction = (node->data > curr->data);
	curr->children[direction] = RecInsertHelper(node, curr->children[direction]);
	
	return curr;
}

int RecInsert(bst_t *bst, int data)
{
	bst_node_t *new_node = NULL;
	
	assert(NULL != bst);
	
	new_node = (bst_node_t *)malloc(sizeof(bst_node_t));	
	if (NULL == new_node)
	{
		return FAIL;
	}
	
	new_node->data = data;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	
	bst->root = RecInsertHelper(new_node, bst->root);

	return SUCCESS;
}

void TestQuestion13Rec(void)
{
	int data[5] = {8,4,10,2,6};
	bst_node_t arr[5] = {0};
	int status = 0;
	bst_t bst = {0};
	size_t i = 0;
	
	bst.end = arr;
	bst.root = bst.end;
	
	for (i = 0; i < 5; ++i)
	{
		status = RecInsert(&bst, data[i]);		
	}
	(void)status;
	
	printf("-------- Question 13 rec ---------\n");
	Print2DTree(bst.root, 0);
}

static void TestNumResultEqual(size_t result, size_t expected_result)
{
	if (result == expected_result)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}

static void TestBoolResult(int result)
{
	if (result)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}

int main(void)
{
    TestQuestion1();
	TestQuestion2();
	TestQuestion3();
	TestQuestion4();
	TestQuestion5();
	TestQuestion6();
	TestQuestion7();
	TestQuestion8b();
	TestQuestion8c();
	TestQuestion9();
	TestQuestion10();
/*	TestQuestion13Iter();*/
/*	TestQuestion13Rec();*/
	
    return 0;
}
