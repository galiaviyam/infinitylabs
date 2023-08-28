/***************************************/
/*                                     */   
/*  Developer: Gali Aviyam             */
/*  Project:   Scheduler               */
/*  Date:      20/06/23                */
/*  Reviewer:  Or                      */
/*                                     */
/***************************************/

#define I_AM_THE_HANDLETON_IMPLEMENTER
#include "scheduler.hpp"   // scheduler class

INSTANTIATE_HANDLETON(ilrd::Scheduler)

namespace ilrd
{
/*------------------------------ Scheduler Class -----------------------------*/
Scheduler::Scheduler(): m_isRunning(true),
                        m_isWake(false),
                        m_isShutdown(false),
                        m_thread(&Scheduler::ThreadRoutine, this) {}

Scheduler::~Scheduler()
{
    m_isShutdown = true;
    Stop();
}

void Scheduler::AddTask(std::shared_ptr<std::function<bool(void)>> callback,
                        std::chrono::milliseconds interval)
{
    if (m_isShutdown)
    {
        throw std::runtime_error("You cannot add tasks during shutdown!");
    }
    
    m_tasks.Push(std::make_shared<Task>(Task(callback, interval)));
    WakeThread();
}

void Scheduler::Run()
{
    if (!m_isRunning)
    {
        m_isRunning = true;
        m_thread = std::thread(&Scheduler::ThreadRoutine, this);
    }
}

void Scheduler::Stop()
{
    m_isRunning = false;
    
    m_tasks.Push(std::make_shared<Task>(Task
        (std::make_shared<std::function<bool(void)>>
        (std::function<bool(void)>([]()
    {
        return true;
    })), std::chrono::milliseconds(0))));
    WakeThread();

    if (m_thread.joinable())
    {
        m_thread.join();
    }
}

void Scheduler::ThreadRoutine()
{
    while (m_isRunning ||
          (m_isShutdown && (!m_tasks.IsEmpty())))
    {
        std::shared_ptr<Scheduler::Task> curTask(0);
        m_tasks.Pop(curTask);
        
        std::chrono::time_point<std::chrono::system_clock> runTime =
                                                        curTask->GetRunTime();
        
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_condVar.wait_until(lock, runTime,[this]()
            {
                return m_isWake;
            });
        }
        m_isWake = false;
        
        if ((curTask->GetRunTime() > std::chrono::system_clock::now()) ||
             !curTask->Run())
        {
            m_tasks.Push(curTask);
        }
    }
}

void Scheduler::WakeThread()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_isWake = true;
    m_condVar.notify_one();
}

/*-------------------------------- Task Class --------------------------------*/
Scheduler::Task::Task(std::shared_ptr<std::function<bool(void)>> callback,
         std::chrono::milliseconds interval): m_runCount(0),
         m_interval(interval),
         m_runTime(std::chrono::system_clock::now() + interval),
         m_callback(callback) {}

bool Scheduler::Task::Run()
{
    bool isDone = (*m_callback)();
    ++m_runCount;

    if (MAX_RERUNS == m_runCount)
    {
        isDone = true;
    }
    else if (!isDone)
    {
        m_runTime = std::chrono::system_clock::now() + m_interval;
    }

    return isDone;
}

std::chrono::time_point<std::chrono::system_clock>
                                            Scheduler::Task::GetRunTime() const
{
    return m_runTime;
}

bool Scheduler::Task::operator<(const Task& other) const
{
    return (m_runTime > other.m_runTime);
}

bool Scheduler::TaskFunctLess::operator()(const std::shared_ptr<Task>& task1, 
                        const std::shared_ptr<Task>& task2) const
{
    return (*task1 < *task2);
}

}   // namespace ilrd