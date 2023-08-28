/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Handleton               */
/*   Date:      05/06/23                */
/*   Reviewer:  Eitan                   */
/*                                      */
/****************************************/

#include "singleton.hpp"    // GetInstance
#include "handleton.hpp"    // handleton

using namespace ilrd;

class Plugin
{
public:

private:
    Plugin() = default;

    friend Singleton<Plugin>;
};

extern "C" Plugin *Fooo1(void)
{
    Plugin *exPlugin = Singleton<Plugin>::GetInstance();

    return exPlugin;
}