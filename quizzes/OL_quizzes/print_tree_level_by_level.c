#include <assert.h>	/* assert */
#include <stdlib.h>	/* malloc */
#include <stdio.h>	/* printf */

typedef enum status
{
	SUCCESS = 0,
	FAIL
} status_t;

typedef enum child
{
	LEFT = 0,
	RIGHT = 1,
	NUM_OF_CHILD
} child_t;

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

static int QueueEnqueue(queue_t *queue, void *data);
static void *QueueDequeue(queue_t *queue);
static int QueueIsEmpty(queue_t *queue);
static void LevelBLevelPrint(tree_t *tree, queue_t *queue);

int main(void)
{
	int test[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	node_t tree[8] = {0};
	tree_t bst = {0};
	queue_t queue = {0};
	
	bst.root = &tree[7];
	queue.front = NULL;
	queue.back = NULL;
	
	tree[0].data = &test[0];
	tree[0].child[LEFT] = NULL;
	tree[0].child[RIGHT] = NULL;

	tree[1].data = &test[1];
	tree[1].child[LEFT] = &tree[0];
	tree[1].child[RIGHT] = &tree[2];

	tree[2].data = &test[2];
	tree[2].child[LEFT] = NULL;
	tree[2].child[RIGHT] = NULL;

	tree[3].data = &test[3];
	tree[3].child[LEFT] = &tree[1];
	tree[3].child[RIGHT] = &tree[5];

	tree[4].data = &test[4];
	tree[4].child[LEFT] = NULL;
	tree[4].child[RIGHT] = NULL;

	tree[5].data = &test[5];
	tree[5].child[LEFT] = &tree[4];
	tree[5].child[RIGHT] = &tree[6];

	tree[6].data = &test[6];
	tree[6].child[LEFT] = NULL;
	tree[6].child[RIGHT] = NULL;

	tree[7].data = &test[7];
	tree[7].child[LEFT] = &tree[3];
	tree[7].child[RIGHT] = NULL;
		
			
	LevelBLevelPrint(&bst, &queue);
	
	return 0;
}

static void LevelBLevelPrint(tree_t *tree, queue_t *queue)
{
	node_t *node = NULL;
	
	assert(NULL != tree);
	assert(NULL != queue);
	
	if (NULL != tree->root)
	{
		QueueEnqueue(queue, tree->root);
	}
	
	while (!QueueIsEmpty(queue))
	{
		node = (node_t *)QueueDequeue(queue);
	
		if (NULL != node->child[LEFT])
		{
			QueueEnqueue(queue, node->child[LEFT]);
		}
		if (NULL != node->child[RIGHT])
		{
			QueueEnqueue(queue, node->child[RIGHT]);
		}
		printf("%d ", *(int *)node->data);
	}
	
	printf("\n");
}

static int QueueEnqueue(queue_t *queue, void *data)
{
	q_node_t *node = NULL;

	assert(NULL != queue);

	node = (q_node_t *)malloc(sizeof(q_node_t));
	if (NULL == node)
	{
		return FAIL;
	}
	
	if (NULL != queue->front)
	{
		queue->back->next = node;
		queue->back = node;
	}
	else
	{
		queue->front = node;
		queue->back = node;
	}
	
	node->data = data;
	node->next = NULL;
	
	return SUCCESS;
}

static void *QueueDequeue(queue_t *queue)
{
	void *ret_val = NULL;
	q_node_t *tmp = NULL;
	
	assert(NULL != queue);
	
	tmp = queue->front;		
	queue->front = queue->front->next;
	if (NULL == queue->front)
	{
		queue->back = NULL;
	}
	
	ret_val = tmp->data;
	free(tmp);
	tmp = NULL;
	
	return ret_val;
}

static int QueueIsEmpty(queue_t *queue)
{
	assert(NULL != queue);
	
	return (NULL == queue->front);
}


