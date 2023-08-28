#include <dlfcn.h>	/* dlopen */
#include <stddef.h>	/*  NULL  */
#include <stdio.h>	/* printf */

/*#include "header.h"*/

typedef void *(func)(void);

int main(void)
{
	void *lib1_ptr  = NULL;
	void *lib2_ptr  = NULL;
	func *foo_func  = NULL;
	func *foo2_func = NULL;
	
	printf("static:\n");
	PrintGlobalVariableAddress();

	lib1_ptr = dlopen("./lib_dynamic1.so", RTLD_LAZY | RTLD_GLOBAL);
	if (NULL == lib1_ptr)
	{
		return -1;
	}

	lib2_ptr = dlopen("./lib_dynamic2.so", RTLD_LAZY | RTLD_GLOBAL);
	if (NULL == lib2_ptr)
	{
		return -1;
	}
	
	*(void **)&foo_func = dlsym(lib1_ptr, "Foo");
	if (NULL == foo_func)
	{
		return -1;
	}
	
	*(void **)&foo2_func = dlsym(lib2_ptr, "Foo2");
	if (NULL == foo2_func)
	{
		return -1;
	}
	
	printf("dynamic:\n");
	foo_func();
	foo2_func();
	
	dlclose(lib1_ptr);
	dlclose(lib2_ptr);

	return 0;
}
