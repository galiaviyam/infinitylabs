#include <stdlib.h>
#include <stdio.h>

static int StaticFunction(void);

int ExternFunction(void);

int RecursiveFunction(void *heap_variable,
						const int *const_local_variable,
						const int *const_static_local_variable,
						int *local_variable,
						int *static_local_variable,
						char *string_literal);

int global_variable = 0;
static int static_global_variable = 0;
const int const_global_variable = 0;
static const int const_static_global_variable = 0;

int main(int argc, char **argv, char **envp)
{
	void *heap_variable = malloc(sizeof(size_t));
	const int const_local_variable = 0;
	static const int const_static_local_variable = 0;
	int local_variable = 0;
	static int static_local_variable = 0;
	char *string_literal = "String literal";
	
	(void)argc;
	(void)argv;
	(void)envp;
	
	static_global_variable = 5;
	
	RecursiveFunction(heap_variable, &const_local_variable, 																																				
						&const_static_local_variable,
						&local_variable,
						&static_local_variable,
						string_literal);
	
	free(heap_variable);
	return 0;
}

int RecursiveFunction(void *heap_variable,
						const int *const_local_variable,
						const int *const_static_local_variable,
						int *local_variable,
						int *static_local_variable,
						char *string_literal)
{
	void *recursive_heap_variable = malloc(sizeof(size_t));
	const int recursive_const_local_variable = 0;
	static const int recursive_const_static_local_variable = 0;
	int recursive_local_variable = 0;
	static int recursive_static_local_variable = 0;
	char *recursive_string_literal = "String literal";
	
	--static_global_variable;
	
	StaticFunction();
	ExternFunction();
	
	if (static_global_variable)
	{
		RecursiveFunction(recursive_heap_variable, 
						&recursive_const_local_variable,
						&recursive_const_static_local_variable, 
						&recursive_local_variable,
						&recursive_static_local_variable,
						recursive_string_literal);
	}
	scanf("%d ", &static_global_variable);
	
	(void)heap_variable;
	(void)const_local_variable;
	(void)const_static_local_variable;
	(void)local_variable;
	(void)static_local_variable;
	(void)string_literal;
	
	
	free(recursive_heap_variable);
	return 0;
}

static int StaticFunction(void)
{
	return 0;
}

int ExternFunction(void)
{
	return 0;
}
