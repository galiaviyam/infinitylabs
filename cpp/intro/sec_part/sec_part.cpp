#include <iostream>	//cout
#include <dlfcn.h> // dlopen

typedef void *(func)(int);

//void Foo()
//{
//	std::cout << "Foo()" << std::endl;
//}
//void Foo(int i)
//{
//	std::cout << "Foo(int " << i << ")" << std::endl;
//}
//void Foo(char c)
//{
//	std::cout << "Foo(char " << c << ")" << std::endl;
//}

int main(int argc, char **argv)
{
	int i = 3;
	char c = 'g';
	int *p = NULL;
	float f = 3.33;
	unsigned char uc = 'u';
	size_t s = 3;
	
//	Foo(c);
//	Foo(i);
//	Foo();

//	Foo(p);
//	Foo(f);
//	Foo(NULL);
//	Foo(uc);
//	Foo(s);
	
	void *lib_ptr = NULL;
	func *chosen_func = NULL;
	
	lib_ptr = dlopen(argv[1], RTLD_LAZY);
	if (NULL == lib_ptr)
	{
		printf("Error dlopen\n");
		return -1;
	}
	
	chosen_func = (func *)dlsym(lib_ptr, "_Z3Fooi");
	if (NULL == chosen_func)
	{
		printf("Error dlsym\n");
		dlclose(lib_ptr);
		return -1;
	}
	
	chosen_func(i);
	
	dlclose(lib_ptr);
	lib_ptr = NULL;
	chosen_func = NULL;
	
	return 0;
}


