#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

typedef enum status
{
	SUCCESS = 0,
	FAIL
} status_t;

typedef struct node
{
	void *data;
	struct node *next;
} node_t;


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

typedef struct arr_tree
{
	int *arr;
	size_t last_idx;
} arr_tree_t;

typedef int (*cmp_func_t)(void *, void *);

static node_t *Flip(node_t *head);
static node_t *RecFlip(node_t *head);
static void Question1Test(void);

static int MaxSubArray(int *arr, size_t size, size_t *start, size_t *end);
static void Question2Test(void);

static void StackSort(stack_t *stack, cmp_func_t cmp);
static void StackSortInsert(stack_t *stack, void *data, cmp_func_t cmp);
static void Question3Test(void);

static int SortCharsInFile(const char *file_name, char *result);
static void Question4Test(void);

static bst_node_t *BSTInsert(bst_t *bst, int data);
static void Print2DTree(bst_node_t* root, int space);
static void Question5aTest(void);

static int RecInsert(bst_t *bst, int data);
static bst_node_t *RecInsertHelper(bst_node_t *node, bst_node_t *curr);
static void Question5bTest(void);

static void FixedSizeArrInsert(arr_tree_t *tree, int data);
static void HeapifyUp(int *arr, size_t idx);
static void SwapInt(int *p1, int *p2);
static void Question5cTest(void);

static void RecReverseStr(char *str, size_t begin, size_t end);
static void SwapChar(char *a, char *b);
static void Question7Test(void);

static void PrintPermutations(char *str, size_t l, size_t r);
static void Question8Test(void);

static void Question10Test(void);

static int CmpFunc(void *num1, void *num2);
static int CmpChar(const void *c1, const void *c2);
static void PrintTestResult(int status);
static void TestNumResultEqual(size_t result, size_t expected_result);
static void TestBoolResult(int result);

int main(void)
{
	Question1Test();
	
	Question2Test();
	
	Question3Test();
	
	Question4Test();
	
	Question5aTest();
	Question5bTest();
	Question5cTest();
	
	Question7Test();
	
	Question8Test();
	
	Question10Test();
	
	return 0;
}

/*----------------------------- Question 1 ----------------------------------*/
static node_t *Flip(node_t *head)
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

static node_t *RecFlip(node_t *head)
{
	node_t *new_head = NULL;
	
	if (NULL == head || NULL == head->next)
	{
		return head;
	}
	
	new_head = RecFlip(head->next);
	head->next->next = head;
	head->next = NULL;
	
	return new_head;
}

static void Question1Test(void)
{
	int status = FAIL;	
	
	node_t node1 = {0};
    node_t node2 = {0};
    node_t node3 = {0};
    node_t node4 = {0};
	node_t node5 = {0};
    node_t node6 = {0};
    node_t node7 = {0};
    node_t node8 = {0};
	
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = NULL;
	
	node5.next = &node6;
	node6.next = &node7;
	node7.next = &node8;
	node8.next = NULL;
	
	if (&node4 == Flip(&node1))
	{
		status = SUCCESS;
	}
	
	printf("Question 1 iterative: ");
	PrintTestResult(status);
	
	status = FAIL;
	if (&node8 == RecFlip(&node5))
	{
		status = SUCCESS;
	}
	
	printf("Question 1 recursive: ");
	PrintTestResult(status);
}

/*----------------------------- Question 2 ----------------------------------*/
static int MaxSubArray(int *arr, size_t size, size_t *start, size_t *end)
{
	int max_sum = 0;
	int current_sum = 0;
	int current_start = 0;
	int current_end = 0;
	size_t i;
	
	assert(arr);
	assert(start);
	assert(end);
	
	*start = 0;
	
	for(i = 0; i < size; ++i)
	{
		current_sum += *(arr + i);
		current_end = i;
    
		if (current_sum < 0)
		{
			current_sum = 0;
			current_start = current_end;
		}

		if (max_sum < current_sum)
		{
			max_sum = current_sum;
			*start = current_start;
			*end = current_end;
		}
	}
	return max_sum;  
}

static void Question2Test(void)
{
	size_t i = 0;
	int arr1[9] = {-2, 1, -3, 4, -1, 2, 3, -5, 4};
    size_t *start = &i;
    size_t *end = &i;
    
   	printf("Question 2: ");
	
	TestNumResultEqual(8, MaxSubArray(arr1, 9, start, end));
}

/*--------------------------- Question 3 + 10 -------------------------------*/
static void StackSort(stack_t *stack, cmp_func_t cmp)
{
	void *top = NULL;
	
	assert(stack);
	
	if (!StackIsEmpty(stack))
	{
		top = StackPop(stack);
		StackSort(stack, cmp);
		StackSortInsert(stack, top, cmp);
	}
}

static void StackSortInsert(stack_t *stack, void *data, cmp_func_t cmp)
{
	void *top = NULL;
	
	assert(stack);
	
	if (StackIsEmpty(stack) || 0 > cmp(data, StackPeek(stack)))
	{
		StackPush(stack, data);
	}
	else
	{
		top = StackPop(stack);
		StackSortInsert(stack, data, cmp);
		StackPush(stack, top);
	}
}

static void Question3Test(void)
{
	int data1 = 5;
	int data2 = 10;
	int data3 = 15;
	int data4 = 20;
	void *pop = NULL;
	size_t i = 0;
	int status = SUCCESS;
	
	stack_t *stack = StackCreate(10);
	
	StackPush(stack, &data3);
	StackPush(stack, &data1);
	StackPush(stack, &data4);	
	StackPush(stack, &data2);
	
	printf("Question 3: ");
	StackSort(stack, &CmpFunc);
	
	for (i = 0; i < 3; ++i)
	{
		pop = StackPop(stack); 
		status += (*(int *)pop >= *(int *)StackPeek(stack));
	}
	
	PrintTestResult(status);
	
	StackDestroy(stack);
}

static void Question10Test(void)
{
	int data1 = 5;
	int data2 = 10;
	int data3 = 15;
	int data4 = 20;
	void *pop = NULL;
	size_t i = 0;
	int status = SUCCESS;
	
	stack_t *stack = StackCreate(10);
	
	StackPush(stack, &data3);
	StackPush(stack, &data1);
	StackPush(stack, &data4);	
	
	printf("Question 10: ");
	StackSort(stack, &CmpFunc);
	StackSortInsert(stack, &data2, &CmpFunc);
	
	for (i = 0; i < 3; ++i)
	{
		pop = StackPop(stack); 
		status += (*(int *)pop >= *(int *)StackPeek(stack));
	}
	
	PrintTestResult(status);
	StackDestroy(stack);
}

static int CmpFunc(void *num1, void *num2) 
{
	return (*(int *)num1 - *(int *)num2);
}

/*----------------------------- Question 4 ----------------------------------*/

static int SortCharsInFile(const char *file_name, char *result)
{
	size_t count = 0;
	FILE *fp = NULL;
	char c = 0;
	
	assert(file_name);
	assert(result);
	
	fp = fopen(file_name, "r");
	if (NULL == fp)
	{
		return FAIL;
	}
	
	do
	{
		c = fgetc(fp);
		result[count] = c;
		++count;
	} while (EOF != c);
	
	fread(result, count, sizeof(char), fp);
	fclose(fp);
	
	qsort(result, count, sizeof(char), CmpChar);
	
	return SUCCESS;
}

static void Question4Test(void)
{
	char result[50] = {0};
	
	printf("Question 4: ");
	
	PrintTestResult(SortCharsInFile("q4_file.txt", result));
	printf("%s\n", result);
}

static int CmpChar(const void *c1, const void *c2) 
{
	return (*(char *)c1 - *(char *)c2);
}
/*---------------------------- Question 5 a ---------------------------------*/

static bst_node_t *BSTInsert(bst_t *bst, int data)
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

static void Question5aTest(void)
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
	
	printf("Question 5 a: ");
	Print2DTree(bst.root, 0);
}

static void Print2DTree(bst_node_t* root, int space)
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

/*---------------------------- Question 5 b ---------------------------------*/
static int RecInsert(bst_t *bst, int data)
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

static bst_node_t *RecInsertHelper(bst_node_t *node, bst_node_t *curr)
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

static void Question5bTest(void)
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
	
	printf("Question 5 b: ");
	Print2DTree(bst.root, 0);
}

/*---------------------------- Question 5 c ---------------------------------*/
static void FixedSizeArrInsert(arr_tree_t *tree, int data)
{
	assert(tree);
	
	tree->arr[tree->last_idx] = data;
	HeapifyUp(tree->arr, tree->last_idx);
	++tree->last_idx;
}

static void HeapifyUp(int *arr, size_t idx)
{
	size_t parent_idx = (idx - 1) / 2;
	
	assert(arr);
	
	while ((0 < idx) && (arr[parent_idx] < arr[idx]))
	{
		SwapInt((arr + parent_idx), (arr + idx));
		idx = parent_idx;
		parent_idx = (idx - 1) / 2;
	}
}

static void SwapInt(int *p1, int *p2)
{
	int tmp = 0;
	
	assert(p1);
	assert(p2);
	
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}


static void Question5cTest(void)
{
	int data[5] = {8,4,10,2,6};
	int arr[10] = {0};
	arr_tree_t tree = {0};
	size_t i = 0;
	
	tree.arr = arr;
	tree.last_idx = 0;
	
	for (i = 0; i < 5; ++i)
	{
		FixedSizeArrInsert(&tree, data[i]);		
	}
	
	printf("Question 5 c: ");
	
	for (i = 0; i < 5; ++i)
	{
		printf("%d ", tree.arr[i]);		
	}
	
	printf("\n");
}

/*----------------------------- Question 7 ----------------------------------*/
static void RecReverseStr(char *str, size_t begin, size_t end)
{
	assert(str);
	
	if (begin >= end)
	{
		return;
	}
	
	SwapChar((str + begin), (str + end));
	
	RecReverseStr(str, begin + 1, end - 1);
}

static void SwapChar(char *a, char *b)
{
	char tmp = 0;
	
	assert(NULL != a);
	assert(NULL != b);
	
	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void Question7Test(void)
{
	char str1[10] = "abcde";
	char str2[10] = "edcba";
	
	printf("Question 7: ");
	RecReverseStr(str1, 0, 4);
	
	TestBoolResult(0 == strcmp(str1, str2));
}

/*----------------------------- Question 8 ----------------------------------*/
static void PrintPermutations(char *str, size_t l, size_t r)
{
	size_t i = 0;
	
	assert(NULL != str);
	
	if (l == r)
	{
		printf("%s\n", str);
		return;
	}
	
	for (i = l; i <= r; ++i)
	{
		SwapChar((str + l), (str + i));
		PrintPermutations(str, l + 1, r);
		SwapChar((str + l), (str + i));
	}
}

static void Question8Test(void)
{
	char str[10] = {'A', 'B', 'C', '\0'};
	printf("Question 8: ");
	printf("The permutations of \"%s\" are:\n", str);
	
	PrintPermutations(str, 0 , 3);
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

static void PrintTestResult(int status)
{
	if (SUCCESS == status)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}
