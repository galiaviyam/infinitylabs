#include <dlfcn.h> /* dlopen */
#include <stdio.h> /* printf */

typedef void *(func)(int);

int main(void)
{
	int num = 9;
	void *lib_ptr = NULL;
	func *foo_func = NULL;
	
	lib_ptr = dlopen("./lib_dynamic.so", RTLD_LAZY);
	if (NULL == lib_ptr)
	{
		return -1;
	}
	
	foo_func = dlsym(lib_ptr, "Foo");
	if (NULL == foo_func)
	{
		return -1;
	}
	
	foo_func(num);
	
	dlclose(lib_ptr);
	
	return 0;
}
