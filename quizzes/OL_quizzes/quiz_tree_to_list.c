#include <stdio.h>	/* printf */
#include <assert.h>	/* assert */

typedef enum
{
	SUCCESS = 0,
	FAIL
} status_t;

typedef enum
{
	LEFT = 0,
	RIGHT,
	NUM_OF_CHILD
} children_t;

typedef struct node node_t;

struct node
{
	int data;
	node_t *parent;
	node_t *child[NUM_OF_CHILD];
};

static node_t *BSTToSortedList(node_t *root);
static node_t *BSTEnd(node_t *root);
static node_t *BSTBegin(node_t *root);

int main(void)
{
	node_t root = {20, NULL, {NULL}};
	node_t node1 = {12, NULL, {NULL}};
	node_t node2 = {28, NULL, {NULL}};
	node_t node3 = {8, NULL, {NULL}};
	node_t node4 = {16, NULL, {NULL}};
	node_t node5 = {24, NULL, {NULL}};
	node_t node6 = {32, NULL, {NULL}};
	node_t *runner = NULL;
	
	root.child[LEFT] = &node1;
	root.child[RIGHT] = &node2;
	
	node1.child[LEFT] = &node3;
	node1.child[RIGHT] = &node4;
	node1.parent = &root;
	
	node2.child[LEFT] = &node5;
	node2.child[RIGHT] = &node6;
	node2.parent = &root;
	
	node3.parent = &node1;
	node4.parent = &node1;
	
	node5.parent = &node2;
	node6.parent = &node2;

	runner = BSTToSortedList(&root);
	
	while (NULL != runner->child[LEFT])
	{
		runner = runner->child[LEFT];
	}
	
	while (NULL != runner->child[RIGHT])
	{
		printf("%d -> ", runner->data);
		runner = runner->child[RIGHT];
	}
	
	printf("%d\n", runner->data);	
	
	while (NULL != runner->child[LEFT])
	{
		printf("%d <- ", runner->data);
		runner = runner->child[LEFT];
	}
	
	printf("%d", runner->data);
	printf("\n");

	return 0;
}



static node_t *BSTToSortedList(node_t *root)
{
	node_t *min_right = NULL;
	node_t *max_left = NULL;
	
	if (NULL == root)
	{
		return NULL;
	}
	
	root->child[LEFT] = BSTToSortedList(root->child[LEFT]);
	root->child[RIGHT] = BSTToSortedList(root->child[RIGHT]);
	
	max_left = BSTEnd(root->child[LEFT]);
	if (max_left)
	{	
		max_left->child[RIGHT] = root;
		root->child[LEFT] = max_left;
	}
	
	min_right = BSTBegin(root->child[RIGHT]);
	if (min_right)
	{
		min_right->child[LEFT] = root;
		root->child[RIGHT] = min_right;
	}
	
	return root;
}

static node_t *BSTEnd(node_t *root)
{
	if (root && root->child[RIGHT])
	{
		return BSTEnd(root->child[RIGHT]);
	}
	
	return root;
}

static node_t *BSTBegin(node_t *root)
{
	if (root && root->child[LEFT])
	{
		return BSTBegin(root->child[LEFT]);
	}
	
	return root;
}
