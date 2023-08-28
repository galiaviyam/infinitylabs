/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Logger                  */
/*   Date:      07/06/23                */
/*   Reviewer:  Eliran                  */
/*                                      */
/****************************************/

#include <fstream>      //logFile
#include <iomanip>      //put_time
#include <sstream>      //ostringstream

#include "logger.hpp"   //logger header

namespace ilrd
{

Logger::Logger(): m_isRunning(true)
{
    m_thread = std::thread(&Logger::ThreadRoutine, this);
}

Logger::~Logger()
{
    m_isRunning = false;
    Log("Logger is shutdown\n");
    m_thread.join();
}

void Logger::Log(const std::string &stringToLog)
{
    std::string log_message = MakeTimeStamp() + stringToLog;

    m_queue.Push(log_message);
}

std::string Logger::MakeTimeStamp()
{
    auto now = std::time(nullptr);
    auto local_time = std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(local_time, "%d/%m/%Y:%H:%M:%S ");
    
	return oss.str();
}

void Logger::ThreadRoutine(Logger *logger)
{
    std::string fileName = (std::string(PATH) + FILE_NAME);

    while (logger->m_isRunning || !logger->m_queue.IsEmpty())
    {
        std::string log_message;
        logger->m_queue.Pop(log_message);

        std::ofstream logFile;
        logFile.open(fileName, std::ios::app);
        logFile << log_message << std::endl;
        logFile.close();
    }
}
} //namespace ilrd