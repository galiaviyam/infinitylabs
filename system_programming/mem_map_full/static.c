#include <stdlib.h>
#include <stdio.h>

/*#include "header.h"*/

static int StatStaticFunction(void);

extern int StatExternFunction(void);

int stat_global_variable = 0;
static int stat_static_global_variable = 0;
const int stat_const_global_variable = 0;
static const int stat_const_static_global_variable = 0;

int StatFunc(int argc, char **argv, char **envp)
{
	void *stat_heap_variable = malloc(sizeof(size_t));
	const int stat_const_local_variable = 0;
	static const int stat_const_static_local_variable = 0;
	int stat_local_variable = 0;
	static int stat_static_local_variable = 0;
	char *stat_string_literal = "String literal";
	
	stat_static_global_variable = 5;
	
	StatStaticFunction();
	StatExternFunction();
	
	printf("**********Static**********\n");
	printf("stat_heap_variable: %p\n", stat_heap_variable);
	printf("stat_const_local_variable: %p\n", &stat_const_local_variable);
	printf("stat_const_static_local_variable: %p\n", &stat_const_static_local_variable);
	printf("stat_local_variable: %p\n", &stat_local_variable);
	printf("stat_static_local_variable: %p\n", &stat_static_local_variable);
	printf("stat_string_literal: %p\n", stat_string_literal);
	printf("StatStaticFunction: %p\n", &StatStaticFunction);
	printf("StatExternFunction: %p\n", &StatExternFunction);
	printf("argc: %p\n", &argc);
	printf("argv: %p\n", &argv);
	printf("envp: %p\n", &envp);
	
	free(stat_heap_variable);
	return 0;
}

static int StatStaticFunction(void)
{
	return 0;
}

extern int StatExternFunction(void)
{
	return 0;
}
