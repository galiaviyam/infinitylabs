/****************************************/
/*                                      */
/*   Developer: Gali Aviyam             */
/*   Project:   Reactor                 */
/*   Date:      15/06/23                */
/*   Reviewer:  Gal                     */
/*                                      */
/****************************************/

#include <stdexcept>    // runtime_error
#include <algorithm>    // for_each
#include <sys/select.h> // select
#include <iostream>     // cout

#include "reactor.hpp"

namespace ilrd
{
/*------------------------------ class Reactor ------------------------------*/
Reactor::Reactor(): m_isRunning(false) {}

Reactor::~Reactor() {}

void Reactor::Add(int fd, Reactor::Mode mode, 
                  const std::function<void ()> &callback)
{
    auto key = std::pair<int, Mode>(fd, mode);

    if (m_callbacks.end() == m_callbacks.find(key))
    {
        m_fds.push_back(key);
    }

    m_callbacks[key] = callback;
}

void Reactor::Remove(int fd, Reactor::Mode mode)
{
    auto key = std::pair<int, Mode>(fd, mode);

    try
    {
        m_callbacks.at(key);
    }
    catch(const std::out_of_range& e)
    {
        throw std::invalid_argument("argument is not in the reactor");
    }
    
    m_fds.erase(std::find(m_fds.begin(), m_fds.end(), key));
    m_callbacks.erase(key);

}

void Reactor::Run()
{
    if (true == m_isRunning)
    {
        throw std::runtime_error("Reactor is already running");
    }

    m_isRunning = true;

    while (m_isRunning)
    {
        FDListener listener(1);
        std::vector<std::pair<int, Mode>> changedFds = 
                                                std::move(listener.Wait(m_fds));

        std::find_if_not(changedFds.begin(), changedFds.end(),
        [this](std::pair<int, Mode>& element)
        {
            if (m_callbacks.end() != m_callbacks.find(element))
            {
                m_callbacks[element]();
            }

            return m_isRunning;
        });
    }

}

void Reactor::Stop()
{
    m_isRunning = false;
}

/*----------------------------- class FDListener -----------------------------*/
Reactor::FDListener::FDListener(int timeoutSec): m_timeoutSec(timeoutSec) {}

std::vector<Reactor::FDListener::fd_mode_t> Reactor::FDListener::
                Wait(const std::vector<Reactor::FDListener::fd_mode_t> &fd)
{
    fd_set fdSet[NUM_OF_MODES];
    timeval timeout;

    FD_ZERO(&fdSet[READ]);
    FD_ZERO(&fdSet[WRITE]);
    FD_ZERO(&fdSet[EXCEPT]);

    int maxFd = 0;

    auto end = fd.end();
    std::for_each(fd.begin(), end, [&](const fd_mode_t& element)
    {
        FD_SET(element.first, &fdSet[element.second]);

        maxFd = std::max(maxFd, element.first);
    });

    timeout.tv_sec = m_timeoutSec;
    timeout.tv_usec = 0;

    int retVal = select(maxFd + 1, &fdSet[READ], &fdSet[WRITE], &fdSet[EXCEPT],
                        &timeout);
    if (-1 == retVal)
    {
        throw std::runtime_error("select() faild.");
    }
    
    std::vector<fd_mode_t> retVec;
    if (0 == retVal)
    {
        return retVec;
    }

    std::for_each(fd.begin(), end, [&](const fd_mode_t& element)
    {
        if (FD_ISSET(element.first, &fdSet[element.second]))
        {
            retVec.push_back(element);
        }
    });

    return retVec;

}

} //namespace ilrd