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
#include "plugins_header.hpp"
#include "factory_singleton.hpp"

namespace ilrd
{
class FileAttr1
{
public:    
    FileAttr1();
    ~FileAttr1();
};

class Plugin1: public BasePlugin
{
public:    
    Plugin1() = default;
    virtual ~Plugin1() = default;
private:
};

FileAttr1::FileAttr1()
{
    auto ptr = Handleton<FactorySingleton<BasePlugin, std::string>>::GetInstance();

    ptr->Add("Plugin1", std::function<BasePlugin *(void)>([]()
    {
        return (new Plugin1());
    }));

    std::cout << "Plugin1 address:\t" << ptr << std::endl;
}

FileAttr1::~FileAttr1()
{
    auto ptr = Handleton<FactorySingleton<BasePlugin, std::string>>::GetInstance();

    ptr->Remove("Plugin1");
}

FileAttr1 obj1;

} //namespace ilrd