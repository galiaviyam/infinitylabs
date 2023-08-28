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

#define I_AM_THE_HANDLETON_IMPLEMENTER
#include "handleton.hpp"    // Handleton
#include "plugins_header.hpp"
#include "factory_singleton.hpp"
typedef ilrd::FactorySingleton<ilrd::BasePlugin, std::string> BaseFactory_t;
INSTANTIATE_HANDLETON(BaseFactory_t)

namespace ilrd
{
class FileAttrBase
{
public:    
    FileAttrBase();
    ~FileAttrBase();
};

FileAttrBase::FileAttrBase()
{
    auto ptr = Handleton<FactorySingleton<BasePlugin, std::string>>::GetInstance();

    ptr->Add("Base", std::function<BasePlugin *(void)>([]()
    {
        return (new BasePlugin());
    }));
    std::cout << "Base address:\t\t" << ptr << std::endl;
}

FileAttrBase::~FileAttrBase()
{
    auto ptr = Handleton<FactorySingleton<BasePlugin, std::string>>::GetInstance();

    ptr->Remove("Base");
}

extern "C" Plugin *Foo1(void)
{
    Plugin *exPlugin = Singleton<Plugin>::GetInstance();
    return exPlugin;
}

extern "C" Plugin *Foo2(void)
{
    Plugin *exPlugin = Handleton<Plugin>::GetInstance();
    return exPlugin;
}

extern "C" Plugin *Foo3(void)
{
    Plugin *exPlugin = Handleton<Plugin>::GetInstance();
    return exPlugin;
}

FileAttrBase objBase;
}