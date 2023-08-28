/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Handleton               */
/*   Date:      05/06/23                */
/*   Reviewer:  Eitan                   */
/*                                      */
/****************************************/

// #include <iostream>         // cout
// #include <dlfcn.h>	        // dlopen

#include "singleton.hpp"    // GetInstance
#include "handleton.hpp"    // handleton

using namespace ilrd;

class Plugin
{
public:

private:
    Plugin() = default;

    friend Singleton<Plugin>;
    // friend Handleton<Plugin>;
};

extern "C" Plugin *Foo1(void)
{
    Plugin *exPlugin = Singleton<Plugin>::GetInstance();

    return exPlugin;
}