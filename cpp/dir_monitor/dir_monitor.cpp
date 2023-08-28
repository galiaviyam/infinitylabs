/****************************************/
/*                                      */
/*   Developer: Gali Aviyam             */
/*   Project:   DLL Loader, Dir Monitor */
/*   Date:      12/06/23                */
/*   Reviewer:  Yuval                   */
/*                                      */
/****************************************/

#include <sys/inotify.h>    // inotify API
#include <unistd.h>         // close()
#include <limits.h>         // MAX_NAME
#include <dlfcn.h>          // dlopen() dlclose()
#include <algorithm>        // for_each
#include <sys/select.h>     // fd_set
#include <sys/time.h>       // struct timeval

#include "dir_monitor.hpp"  //header file

namespace ilrd
{

/*----------------------------- class DirMonitor -----------------------------*/
DirMonitor::DirMonitor(std::string folderPath): m_folderPath(folderPath),
                                                m_inotifyFd(inotify_init())
{
    if (-1 == m_inotifyFd)
    {
        std::__throw_runtime_error("inotify failed\n");
    }

    m_inotifyWatch = inotify_add_watch(m_inotifyFd, m_folderPath.c_str(), 
                  IN_CLOSE_WRITE);

    if (-1 == m_inotifyWatch)
    {
        std::__throw_runtime_error("inotify_add_watch failed\n");
    }
}

DirMonitor::~DirMonitor()
{
    if (m_isRunning)
    {
        Stop();
    }
    
    close(m_inotifyFd);

    inotify_rm_watch(m_inotifyFd, m_inotifyWatch);
    m_inotifyWatch = 0;

    CloseAll();
}

void DirMonitor::Register(CallbackBase<std::string> *callback)
{
    m_disp.Register(callback);
}

void DirMonitor::Unregister(CallbackBase<std::string> *callback)
{
    m_disp.Unregister(callback);
}

void DirMonitor::Run()
{
    m_isRunning = true;

    m_thread = std::thread(&ThreadRoutine, this);
}

void DirMonitor::ThreadRoutine(DirMonitor *monitor)
{
    fd_set read_set;
    struct timeval timeout;

    while (monitor->m_isRunning)
    {
        FD_ZERO(&read_set);
        FD_SET(monitor->m_inotifyFd, &read_set);

        timeout.tv_sec = 3;
        timeout.tv_usec = 0;

        int ready = select(monitor->m_inotifyFd + 1, &read_set, 
                                                    nullptr, nullptr, &timeout);
        if (-1 == ready)
        {
            throw std::runtime_error("Run failed to read fd\n");
        }
        else if (ready)
        {
            monitor->ReadDir();
        }     
    }
}

void DirMonitor::ReadDir()
{
    const size_t BUFF_LEN (10 * (sizeof(inotify_event) + NAME_MAX + 1));
    char buffer[BUFF_LEN] = {0};
    int bytes_read = 0;

    int read_byte_length = read(m_inotifyFd, buffer, BUFF_LEN);
    if (-1 == read_byte_length)
    {
        throw std::runtime_error("Run(): read directory failed");
    }

    while (bytes_read < read_byte_length)
    {
        inotify_event *event = reinterpret_cast<inotify_event *>(buffer);
        NotifyAll(std::string(m_folderPath) + std::string(event->name));
        bytes_read += sizeof(inotify_event) + event->len;
    }
}

void DirMonitor::Stop()
{
    m_isRunning = false;

    m_thread.join();
}

void DirMonitor::NotifyAll(std::string pluginName)
{
    m_disp.NotifyAll(pluginName);
}

void DirMonitor::CloseAll()
{
    m_disp.CloseAll();
}

/*----------------------------- class DllLoader ------------------------------*/
DllLoader::DllLoader(): m_callback(this, &DllLoader::Load, &DllLoader::Close) {}

DllLoader::~DllLoader()
{
    Close();
}

void DllLoader::Register(DirMonitor *dir)
{
    dir->Register(&m_callback);
}

void DllLoader::Load(std::string pluginName)
{
    if (pluginName.find(".so") != std::string::npos)
    {
        auto iter = m_plugins.find(pluginName);
        if (m_plugins.end() != iter)
        {
            dlclose(m_plugins[pluginName]);
        }
        
        void *newHandle = dlopen(pluginName.c_str(), RTLD_LAZY);
        if (nullptr == newHandle)
        {
            throw std::runtime_error("Loading plugin failed.");
        }
        m_plugins[pluginName] = newHandle;
    }
}

void DllLoader::Close()
{
    std::for_each(m_plugins.begin(), m_plugins.end(), 
    [](std::pair<std::string, void*>plugin)
    {
        dlclose(plugin.second);
    });

    m_plugins.clear();
}

}   // namespace ilrd
