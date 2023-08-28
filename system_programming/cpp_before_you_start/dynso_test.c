/*----------------------------------------------------------------------------*/
/* DEVELOPER: Gali Aviyam                                                     */
/* LAST MODIFIED: 16/03/2023                                                  */
/* WORKSHEET NAME: C++ Before Start	                                          */
/* REVIEWER: Ariel K                                                          */
/*----------------------------------------------------------------------------*/
#include <dlfcn.h> /* dlopen */
#include <stdio.h> /* printf */

typedef void *(func)(void);

int main(int argc, char **argv)
{
	void *lib_ptr = NULL;
	func *chosen_func = NULL;
	
	lib_ptr = dlopen(argv[1], RTLD_LAZY);
	if (NULL == lib_ptr)
	{
		return -1;
	}
	
	chosen_func = dlsym(lib_ptr, argv[2]);
	if (NULL == chosen_func)
	{
		dlclose(lib_ptr);
		return -1;
	}
	
	chosen_func();
	
	dlclose(lib_ptr);
	lib_ptr = NULL;
	chosen_func = NULL;
	
	return 0;
}
