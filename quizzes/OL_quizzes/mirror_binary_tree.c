#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define COUNT (10)

typedef enum child
{
	LEFT = 0,
	RIGHT = 1,
	NUM_OF_CHILD
} child_t;

typedef enum status
{
	SUCCESS = 0,
	FAIL
} status_t;

typedef struct node 
{
	void *data;
	struct node *child[NUM_OF_CHILD];
} node_t;

typedef struct tree
{
	node_t *root;
} tree_t;

typedef struct q_node
{
	void *data;
	struct q_node *next;
} q_node_t;

typedef struct queue
{
	q_node_t *front;
	q_node_t *back;
} queue_t;

static void MirrorTree(node_t *node);
void Print2DTree(node_t* root, int space);

int main(void)
{
	int data[5] = {8,4,10,2,6};
	node_t arr[5] = {0};
	
	arr[0].child[LEFT] = &arr[1];
	arr[0].child[RIGHT] = &arr[2];
	arr[0].data = &data[0];
	
	arr[1].child[LEFT] = &arr[3];
	arr[1].child[RIGHT] = &arr[4];
	arr[1].data = &data[1];
	
	arr[2].child[LEFT] = NULL;
	arr[2].child[RIGHT] = NULL;
	arr[2].data = &data[2];
	
	arr[3].child[LEFT] = NULL;
	arr[3].child[RIGHT] = NULL;
	arr[3].data = &data[3];
	
	arr[4].child[LEFT] = NULL;
	arr[4].child[RIGHT] = NULL;
	arr[4].data = &data[4];
	
	printf("Before Mirror:\n");
	Print2DTree(&arr[0], 0);
	
	MirrorTree(&arr[0]);
	
	printf("After Mirror:\n");
	Print2DTree(&arr[0], 0);

	return 0;
}

static void MirrorTree(node_t *node)
{
	node_t *tmp = NULL;
	
	if (NULL == node)
	{
		return;
	}
	
	MirrorTree(node->child[LEFT]);
	MirrorTree(node->child[RIGHT]);
	
	tmp = node->child[LEFT];
	node->child[LEFT] = node->child[RIGHT];
	node->child[RIGHT] = tmp;
}

void Print2DTree(node_t* root, int space)
{
	int i = 0;
	if (root == NULL)
	{
		return;
	}
 
    space += COUNT;
 
    Print2DTree(root->child[RIGHT], space);
 
    printf("\n");
    for (i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", *(int *)root->data);
 
    Print2DTree(root->child[LEFT], space);
}




