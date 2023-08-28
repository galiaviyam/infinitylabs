#include <stdlib.h>
#include <stdio.h>

static int ImpStaticFunction(void);

extern int ImpExternFunction(void);

int imp_global_variable = 0;
static int imp_static_global_variable = 0;
const int imp_const_global_variable = 0;
static const int imp_const_static_global_variable = 0;

int ImpFunc(int argc, char **argv, char **envp)
{
	void *imp_heap_variable = malloc(sizeof(size_t));
	const int imp_const_local_variable = 0;
	static const int imp_const_static_local_variable = 0;
	int imp_local_variable = 0;
	static int imp_static_local_variable = 0;
	char *imp_string_literal = "String literal";
	
	(void)argc;
	(void)argv;
	(void)envp;
	
	imp_static_global_variable = 5;
	ImpStaticFunction();
	ImpExternFunction();
	
	printf("**********Implicit**********\n");
	printf("imp_heap_variable: %p\n", imp_heap_variable);
	printf("imp_const_local_variable: %p\n", &imp_const_local_variable);
	printf("imp_const_static_local_variable: %p\n", &imp_const_static_local_variable);
	printf("imp_local_variable: %p\n", &imp_local_variable);
	printf("imp_static_local_variable: %p\n", &imp_static_local_variable);
	printf("imp_string_literal: %p\n", imp_string_literal);
	printf("ImpStaticFunction: %p\n", &ImpStaticFunction);
	printf("ImpExternFunction: %p\n", &ImpExternFunction);
	printf("argc: %p\n", &argc);
	printf("argv: %p\n", &argv);
	printf("envp: %p\n", &envp);
	
	free(imp_heap_variable);
	return 0;
}

static int ImpStaticFunction(void)
{
	return 0;
}

extern int ImpExternFunction(void)
{
	return 0;
}
