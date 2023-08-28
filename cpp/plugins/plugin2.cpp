/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Handleton               */
/*   Date:      05/06/23                */
/*   Reviewer:  Eitan                   */
/*                                      */
/****************************************/

#include <string>
#include <functional>

#include "handleton.hpp"    // Handleton
#include "plugins.hpp"
#include "factory_singleton.hpp"

namespace ilrd
{
class FileAttr2
{
public:    
    FileAttr2();
    ~FileAttr2();
};

class Plugin2: public BasePlugin
{
public:    
    Plugin2() = default;
    virtual ~Plugin2() = default;
private:
};

FileAttr2::FileAttr2()
{
    auto ptr = Handleton<FactorySingleton<BasePlugin, std::string>>::GetInstance();

    ptr->Add("Plugin2", std::function<BasePlugin *(void)>([]()
    {
        return (new Plugin2());
    }));

    std::cout << "Plugin2 address:\t" << ptr << std::endl;
}

FileAttr2::~FileAttr2()
{
    auto ptr = Handleton<FactorySingleton<BasePlugin, std::string>>::GetInstance();

    ptr->Remove("Plugin2");
}

FileAttr2 obj2;

} //namespace ilrd