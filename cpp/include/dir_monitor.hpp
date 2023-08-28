/****************************************/
/*                                      */
/*   Developer: Gali Aviyam             */
/*   Project:   DLL Loader, Dir Monitor */
/*   Date:      12/06/23                */
/*   Reviewer:  Yuval                   */
/*                                      */
/****************************************/

#ifndef ILRD_RD136_7_DIR_MONITOR_HPP
#define ILRD_RD136_7_DIR_MONITOR_HPP

#include <string>                   //string
#include <thread>                   //thread
#include <unordered_map>            //unordered map

#include "dispatcher_callback.hpp"  //header file

namespace ilrd
{

class DirMonitor
{
public:
    DirMonitor(std::string folderPath);
    ~DirMonitor();
    void Register(CallbackBase<std::string> *callback);
    void Unregister(CallbackBase<std::string> *callback);
    void Run();
    void Stop();

private:
    void NotifyAll(std::string pluginName);
    void CloseAll();
    std::string m_folderPath;
    Dispatcher<std::string> m_disp;
    bool m_isRunning{false};
    int m_inotifyFd{0};
    int m_inotifyWatch{0};
    std::thread m_thread;
    static void ThreadRoutine(DirMonitor *monitor);
    void ReadDir();
};

class DllLoader
{
public:
    DllLoader();
    ~DllLoader();
    void Register(DirMonitor *dir);
    void Load(std::string pluginName);
    void Close();

private:
    Callback<DllLoader, std::string> m_callback;
    std::unordered_map<std::string, void *> m_plugins;     
};

}   // namespace ilrd

#endif /* ILRD_RD136_7_DIR_MONITOR_HPP */