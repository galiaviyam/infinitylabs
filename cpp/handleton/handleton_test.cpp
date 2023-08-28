/****************************************/
/*                                      */
/*   Developer: Gali Aviyam             */
/*   Project:   Handleton               */
/*   Date:      05/06/23                */
/*   Reviewer:  Eitan                   */
/*                                      */
/****************************************/

#include <string>                   // string
#include <iostream>                 // ostream
#include <cstddef>                  // size_t
#include <dlfcn.h>                  // dlopen

#include "handleton.hpp"            // Class
#include "singleton.hpp"            // singleton
#include "factory_singleton.hpp"    // singleton
#include "plugins_header.hpp"       // singleton

using namespace ilrd;
using std::cout;
using std::cerr;
using std::endl;

const char *g_default = "\033[0m";
const char *g_green = "\033[32m";
const char *g_red = "\033[31m";


void Exercise1(void);
void Exercise2(void);
void Exercise3(void);

void CheckTestResult(std::string testName, bool checkCondition);
void CheckTestResult(std::string testName, bool checkCondition, 
                     std::size_t testNum);
void TryObj(std::string key);

/*----------------------------------- Test -----------------------------------*/
int main()
{
    Exercise1();
    Exercise2();
    Exercise3();
    
    return 0;
}

typedef Plugin *(*plugin_void_func)();
typedef FactorySingleton<BasePlugin, std::string> *(*base_void_func)();

void Exercise1(void)
{
	cout << "\n------- Exercise 1 -------" << endl;

    Plugin *exProcess = Singleton<Plugin>::GetInstance();

    void *handle = dlopen("./lib_plugin_main.so", RTLD_LAZY);
    if (0 == handle)
    {
        cerr << "Failed to load shared library: " << dlerror() << endl;
        return;
    }

    plugin_void_func foo = (plugin_void_func)dlsym(handle, "Foo1");
    if (0 == foo)
    {
        cerr << "Failed to load function: " << dlerror() << endl;
        dlclose(handle);
        return;
    }

    Plugin *exPlugin = foo();

    dlclose (handle);

    std::cout << "Process address:\t" << exProcess << std::endl;
    std::cout << "Plugin address:\t\t" << exPlugin << std::endl;

    CheckTestResult("\nCheck Addresses", exProcess == exPlugin);
    cout << endl;
}

void Exercise2(void)
{

	cout << "\n------- Exercise 2 -------" << endl;
    Plugin *exProcess = Handleton<Plugin>::GetInstance();

    void *handle = dlopen("./lib_plugin_main.so", RTLD_LAZY);
    if (0 == handle)
    {
        cerr << "Failed to load shared library: " << dlerror() << endl;
        return;
    }

    plugin_void_func foo = (plugin_void_func)dlsym(handle, "Foo2");
    if (0 == foo)
    {
        cerr << "Failed to load function: " << dlerror() << endl;
        dlclose(handle);
        return;
    }

    Plugin *exPlugin = foo();

    std::cout << "Process address:\t" << exProcess << std::endl;
    std::cout << "Plugin address:\t\t" << exPlugin << std::endl;

    CheckTestResult("\nCheck Addresses", exProcess == exPlugin);
    cout << endl;

    dlclose(handle);
}

void Exercise3(void)
{
	cout << "\n------- Exercise 3 -------" << endl;

    auto processPtr = Handleton<FactorySingleton<BasePlugin, 
                      std::string>>::GetInstance();
    cout << "Process address:\t" << processPtr << endl;

	std::string i;
	std::cin >> i;

	while (i != "exit")
	{
        void *handle = dlopen("./lib_plugins.so", RTLD_LAZY);
		if (handle == 0)
		{
			cerr << "Failed to load Shared Object" << dlerror() << endl;
			return;
		}

        TryObj(i);
		
		dlclose(handle);

		std::cin >> i;
	}

    cout << endl;
}

void TryObj(std::string key)
{
    try
    {
        Handleton<FactorySingleton<BasePlugin, std::string>>::
                                   GetInstance()->Create(key);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << endl;
    }
}

/*------------------------------- Test Status --------------------------------*/
void CheckTestResult(std::string testName, bool checkCondition)
{
    cout << testName << " test:";

    int status = (!checkCondition);
    
    if (status)
	{
		cout << g_red << " FAIL" << g_default << endl;
	}
	else
	{
		cout << g_green << " PASS" << g_default << endl;
	}
}

void CheckTestResult(std::string testName, bool checkCondition, 
                     std::size_t testNum)
{
    
    cout << testName << " test no. " << testNum << ":";
    
    int status = (!checkCondition);
    
    if (status)
	{
		cout << g_red << " FAIL" << g_default << endl;
	}
	else
	{
		cout << g_green << " PASS" << g_default << endl;
	}
}
