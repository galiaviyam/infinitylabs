/***************************************/
/*                                     */   
/*  Developer: Gali Aviyam             */
/*  Project:   Scheduler               */
/*  Date:      20/06/23                */
/*  Reviewer:  Or                      */
/*                                     */
/***************************************/

#ifndef ILRD_RD136_7_SCHEDULER_HPP
#define ILRD_RD136_7_SCHEDULER_HPP

#include <functional>           // std::function<>
#include <chrono>               // std::chrono  
#include <memory>               // shared ptr
#include <thread>               // thread
#include <mutex>                // mutex
#include <condition_variable>   // condition variable

#include "handleton.hpp"        // ilrd::handleton<>
#include "waitable_queue.hpp"   // waitable queue
#include "priority_queue.hpp"   // priority queue

namespace ilrd
{

class Scheduler
{
    
public:
    Scheduler(const Scheduler&) = delete;
    Scheduler& operator=(const Scheduler&) = delete;

    void AddTask(std::shared_ptr<std::function<bool(void)>> callback,
                 std::chrono::milliseconds interval);
    void Run();
    void Stop();
        
private:
    class Task;

    class TaskFunctLess
    {
    public:
        bool operator()(const std::shared_ptr<Task>& task1, 
                        const std::shared_ptr<Task>& task2) const;
    };

    Scheduler();
    ~Scheduler();
    void ThreadRoutine();
    void WakeThread();

    friend class Handleton<Scheduler>;
    
    static const constexpr int MAX_RERUNS = 3;
    WaitableQueue<PriorityQueue<std::shared_ptr<Task>,
                  std::vector<std::shared_ptr<Task>>,
                  TaskFunctLess>> m_tasks;
    bool m_isRunning;
    std::mutex m_mutex;
    std::condition_variable m_condVar;
    bool m_isWake;
    bool m_isShutdown;
    std::thread m_thread;
};

class Scheduler::Task
{
public:
    Task(std::shared_ptr<std::function<bool(void)>> callback,
         std::chrono::milliseconds interval);
    bool Run();
    std::chrono::time_point<std::chrono::system_clock> GetRunTime() const;
    bool operator<(const Task& other) const;
    
private:
    std::size_t m_runCount;
    const std::chrono::milliseconds m_interval;
    std::chrono::time_point<std::chrono::system_clock> m_runTime;  // absolute time to run task
    std::shared_ptr<std::function<bool(void)>> m_callback;
};

}   // namespace ilrd

#endif /* ILRD_RD136_7_SCHEDULER_HPP */




/*******************************************************************************
How to Use:|
-----------
- Scheduler starts to run in construction.
- Invoke Stop() in order to stop executing tasks*.
- Invoke Run() in order to continue executing tasks again.

--------------
Pay Attention:|
--------------
- Bool returned from the std::function: false = re-run task.
- Stop() mustn't be called from within a task.
-*In the destructor, all unfinished tasks will be executed, unless Stop() has
  been called before, in such case - the tasks will not be executed.
- Adding tasks during the shutdown of the scheduler is prohibited.
*******************************************************************************/
