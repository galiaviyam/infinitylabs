/****************************************/
/*                                      */
/*   Developer: Gali Aviyam             */
/*   Project:   Thread Pool             */
/*   Date:      28/05/23                */
/*   Reviewer:  Yuval                   */
/*                                      */
/****************************************/

#ifndef ILRD_RD136_7_THREAD_POOL_HPP
#define ILRD_RD136_7_THREAD_POOL_HPP

#include <thread>                           // hardware_concurrency
#include <functional>                       // function
#include <unordered_map>                    // unordered map
#include <atomic>                           // atomic

#include "semaphore.hpp"                    // Semaphore
#include "priority_queue.hpp"               // PriorityQueue
#include "waitable_queue.hpp"               // WaitableQueue
#include "thread_safe_unordered_map.hpp"    //unordered map

namespace ilrd
{
class ThreadPool
{
public:
    class TaskFuture;

    enum Status : int
    {
        WAIT = 0,
        RUN,
        DONE
    };

    enum Priority : int
    {
        HIGH = 0,
        MID,
        LOW
    };

    explicit ThreadPool(unsigned int threadsNum = 
                        std::thread::hardware_concurrency());
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ~ThreadPool();

    TaskFuture AddTask(std::shared_ptr<std::function<int(void)>> func, 
                       Priority priority);
    void Pause();
    void Resume();
    void SetNumOfThreads(unsigned int threadsNum = 
                        std::thread::hardware_concurrency());
    void ShutDown();
    void AwaitTermination();

private:
    class Task;
    class TaskLessFunctor
    {
    public:
        bool operator()(std::shared_ptr<Task> task1,
                        std::shared_ptr<Task> task2);
    };

    ThreadSafeUnorderedMap<std::thread::id,
                           std::shared_ptr<std::thread>> m_threads;

    WaitableQueue<PriorityQueue<std::shared_ptr<Task>,
                                std::vector<std::shared_ptr<Task>>,
                                TaskLessFunctor>> m_tasksQueue;
    Status m_status;
    std::atomic<bool> m_is_terminated;
    size_t m_threads_num;
    Semaphore m_sem_pause;
    static thread_local Status s_status;

    const static Priority LEAST_PRIORITY = static_cast<Priority>(LOW + 1);
    const static Priority TOP_PRIORITY = static_cast<Priority>(HIGH - 1);

    static void ThreadRoutine(ThreadPool *tp);

    void CheckShut() const;
    void CheckNotShut() const;
    void CheckPaused() const;
    void CheckRunning() const;
    static unsigned int CheckNumOfThreads(unsigned int threadsNum);
    void RemoveThreads(unsigned int threadsNum);
    void AddThreads(unsigned int threadsNum);
};

class ThreadPool::TaskFuture
{
public:
    explicit TaskFuture(std::shared_ptr<Task> task);
    ~TaskFuture() = default;

    int WaitResult(std::chrono::milliseconds timeout = 
                  std::chrono::milliseconds(INT32_MAX)) const;
    int GetStatus() const;

private:
    std::shared_ptr<Task> m_task;
};

class ThreadPool::Task
{
public:
    explicit Task(std::shared_ptr<std::function<int(void)>> func,
                  int priority);
    ~Task() = default;

    bool operator<(const Task& other) const;
    void Run();
    int WaitResult(std::chrono::milliseconds timeout = 
                  std::chrono::milliseconds(INT32_MAX)) const;
    int GetStatus() const;

private:
    std::shared_ptr<std::function<int(void)>> m_func;
    mutable Semaphore m_sem;
    int m_priority;
    int m_result;
    int m_status;
};

} //namespace ilrd

#endif /* ILRD_RD136_7_THREAD_POOL_HPP */
