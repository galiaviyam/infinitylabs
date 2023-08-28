/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Logger                  */
/*   Date:      07/06/23                */
/*   Reviewer:  Eliran                  */
/*                                      */
/****************************************/

#ifndef ILRD_RD136_7_LOGGER_HPP
#define ILRD_RD136_7_LOGGER_HPP

#include <string>   //std::string
#include <queue>    //std::vector
#include <thread>   //std::threads

#include "handleton.hpp"
#include "waitable_queue.hpp"

namespace ilrd
{

class Logger
{
public:
    void Log(const std::string& stringToLog);
    Logger(const Logger& other) = delete;
    Logger& operator=(const Logger& other) = delete;

private:
    Logger();
    ~Logger();

    WaitableQueue<std::queue<std::string>> m_queue;
    bool m_isRunning;
    std::thread m_thread;
    static constexpr const char* PATH = "./";
    static constexpr const char* FILE_NAME = "log.txt";

    friend Handleton<Logger>;

    static std::string MakeTimeStamp();
    static void ThreadRoutine(Logger *logger);
};

} //ilrd

#endif //ILRD_RD136_7_LOGGER_HPP