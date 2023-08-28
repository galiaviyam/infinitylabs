/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Handleton               */
/*   Date:      05/06/23                */
/*   Reviewer:  Eitan                   */
/*                                      */
/****************************************/

#include <iostream>         // cout

#include "handleton.hpp"    // Handleton
#include "singleton.hpp"    

namespace ilrd
{
class BasePlugin
{
public:
    BasePlugin() = default;
    virtual ~BasePlugin() = default;
private:
};

class Plugin
{
public:

private:
    Plugin() = default;

    friend Singleton<Plugin>;
    friend Handleton<Plugin>;
};

}//namespace ilrd