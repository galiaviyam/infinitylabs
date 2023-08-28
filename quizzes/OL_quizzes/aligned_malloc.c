#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static void *AlignedMalloc(size_t bytes, size_t align);
static void AlignedFree(void *p);


int main (int argc, char *argv[])
{
	char **endptr = NULL;
	int *p = NULL;
	
	assert(NULL != argv);
	
	p = AlignedMalloc(100, strtol(argv[1], endptr, 10));

	printf ("%s: %p\n", argv[1], (void *)p);
	AlignedFree (p);
	
	return 0;
}


static void *AlignedMalloc(size_t bytes, size_t align)
{
	void *p1 = NULL;
	void **p2 = NULL;
	int offset = align - 1 + sizeof(void *);
	
	p1 = (void *)malloc(bytes + offset);
	if (NULL == p1)
	{
		return NULL;
	}
	
	p2 = (void **)(((size_t)(p1) + offset) & ~(align - 1));
	p2[-1] = p1;
	
	return p2;
}

static void AlignedFree(void *ptr)
{
	free(((void **)ptr)[-1]);
}
