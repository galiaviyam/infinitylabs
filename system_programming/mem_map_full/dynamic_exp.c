#include <stdlib.h>
#include <stdio.h>

static int ExpStaticFunction(void);

extern int ExpExternFunction(void);

int exp_global_variable = 0;
static int exp_static_global_variable = 0;
const int exp_const_global_variable = 0;
static const int exp_const_static_global_variable = 0;

int ExpFunc(int argc, char **argv, char **envp)
{
	void *exp_heap_variable = malloc(sizeof(size_t));
	const int exp_const_local_variable = 0;
	static const int exp_const_static_local_variable = 0;
	int exp_local_variable = 0;
	static int exp_static_local_variable = 0;
	char *exp_string_literal = "String literal";
	
	exp_static_global_variable = 5;
	
	ExpStaticFunction();
	ExpExternFunction();
	
	printf("**********explicit**********\n");
	printf("exp_heap_variable: %p\n", exp_heap_variable);
	printf("exp_const_local_variable: %p\n", &exp_const_local_variable);
	printf("exp_const_static_local_variable: %p\n", &exp_const_static_local_variable);
	printf("exp_local_variable: %p\n", &exp_local_variable);
	printf("exp_static_local_variable: %p\n", &exp_static_local_variable);
	printf("exp_string_literal: %p\n", exp_string_literal);
	printf("ExpStaticFunction: %p\n", &ExpStaticFunction);
	printf("ExpExternFunction: %p\n", &ExpExternFunction);
	printf("argc: %p\n", &argc);
	printf("argv: %p\n", &argv);
	printf("envp: %p\n", &envp);
		
	free(exp_heap_variable);
	return 0;
}

static int ExpStaticFunction(void)
{
	return 0;
}

extern int ExpExternFunction(void)
{
	return 0;
}
