/****************************************/
/*                                      */
/*   Developer: Gali Aviyam             */
/*   Project:   DLL Loader, Dir Monitor */
/*   Date:      12/06/23                */
/*   Reviewer:  Yuval                   */
/*                                      */
/****************************************/
#include <iostream>
#include <vector>

#include "singleton.hpp"
#include "factory_singleton.hpp"
#include "handleton.hpp"
#include "plugins.hpp"
#include "dir_monitor.hpp"

using namespace ilrd;
using namespace std;

void FactoryTest(void);

int main() 
{
    DirMonitor publisher("../libs/debug/");
    DllLoader loader;

    loader.Register(&publisher);
    publisher.Run();

    std::this_thread::sleep_for(std::chrono::seconds(3));

    FactoryTest();

    return 0;
}

void FactoryTest(void)
{
    auto fac = Handleton<FactorySingleton<BasePlugin, std::string>>::GetInstance();

    DirMonitor dirM("../plugins/");
    DllLoader dllL;
    dllL.Register(&dirM);
    std::vector<BasePlugin *> objVec;
    dirM.Run();

    cout << "Enter 'q' to Quit loop," << endl;
    cout << "any other key to continue" << endl << endl;
    char input = 'x';
    while ('q' != input)
    {
        try
        {
            objVec.push_back(fac->Create("Base"));
        }
        catch(const std::exception& e)
        {
            cout << "Base not loaded" << endl;
        }
        
        try
        {
            objVec.push_back(fac->Create("Plugin1"));
        }
        catch(const std::exception& e)
        {
            cout << "Plugin1 not loaded" << endl;
        }

        try
        {
            objVec.push_back(fac->Create("Plugin2"));
        }
        catch(const std::exception& e)
        {
            cout << "Plugin2 not loaded" << endl;
        }

        cout << endl;
        for (auto &objIt : objVec)
        {
            delete objIt;
            objIt = nullptr;
        }
        cout << endl;

        objVec.clear();

        std::cin >> input;
        cout << endl;
    }
}
