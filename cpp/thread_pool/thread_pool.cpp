/****************************************/
/*                                      */
/*   Developer: Gali Aviyam             */
/*   Project:   Thread Pool             */
/*   Date:      28/05/23                */
/*   Reviewer:  Yuval                   */
/*                                      */
/****************************************/

#include "thread_pool.hpp"      // header file

namespace ilrd
{
thread_local ThreadPool::Status ThreadPool::s_status = ThreadPool::Status::WAIT;

/*----------------------------------------------------------------------------*/
/*-------------------------------- ThreadPool --------------------------------*/
/*----------------------------------------------------------------------------*/

ThreadPool::ThreadPool(unsigned int threadsNum): m_status(RUN), 
                                                 m_is_terminated(false),
                                                 m_threads_num(0UL)
{
    AddThreads(CheckNumOfThreads(threadsNum));
}

/*-------------------------------- ~ThreadPool -------------------------------*/
ThreadPool::~ThreadPool()
{
    if (!m_is_terminated)
    {
        ShutDown();
    }
    AwaitTermination();
}

/*--------------------------------- AddTask ----------------------------------*/
ThreadPool::TaskFuture ThreadPool::AddTask(std::shared_ptr<std::
                          function<int ()>> func, ThreadPool::Priority priority)
{
    CheckShut();

    auto task_ptr = std::shared_ptr<Task>(new Task(func, priority));
    m_tasksQueue.Push(task_ptr);

    return ThreadPool::TaskFuture(task_ptr);
}

/*---------------------------------- Pause -----------------------------------*/
void ThreadPool::Pause()
{
    CheckShut();
    CheckPaused();

    for (unsigned int i = 0; i < m_threads_num; ++i)
    {
        AddTask(std::make_shared<std::function<int(void)>>([&]()
                {m_sem_pause.Wait(); return 0;}), TOP_PRIORITY);
    }
    m_status = WAIT;
}

/*--------------------------------- Resume -----------------------------------*/
void ThreadPool::Resume()
{
    CheckShut();
    CheckRunning();

    for (unsigned int i = 0; i < m_threads_num; ++i)
    {
        m_sem_pause.Post();
    }

    m_status = RUN;
}

/*----------------------------- SetNumOfThreads ------------------------------*/
void ThreadPool::SetNumOfThreads(unsigned int threadsNum)
{
    CheckShut();
    CheckNumOfThreads(threadsNum);

    if (m_threads_num <= threadsNum)
    {
        AddThreads(threadsNum - m_threads_num);
    }
    else
    {
        RemoveThreads(m_threads_num - threadsNum);
    }
}

/*-------------------------------- AddThreads --------------------------------*/
void ThreadPool::AddThreads(unsigned int threadsNum)
{
    for (unsigned int i = 0; i < threadsNum; ++i)
    {
        std::shared_ptr<std::thread> new_thread = 
             std::shared_ptr<std::thread>(new std::thread(ThreadRoutine, this));
        m_threads.insert(new_thread->get_id(), new_thread);
        ++m_threads_num;
    }
}

/*------------------------------ RemoveThreads -------------------------------*/
void ThreadPool::RemoveThreads(unsigned int threadsNum)
{
    for (unsigned int i = 0; i < threadsNum; ++i)
    {
        AddTask(std::make_shared<std::function<int(void)>>([this]()
            { 
                ThreadPool::s_status = DONE;
                std::shared_ptr<std::thread> thread_ptr;
                m_threads.find(std::this_thread::get_id(), thread_ptr);
                if (thread_ptr)
                {
                    thread_ptr->detach();
                    m_threads.erase(std::this_thread::get_id());
                }
                return 0;
            }), TOP_PRIORITY);
        --m_threads_num;
    }
}

/*--------------------------------- ShutDown ---------------------------------*/
void ThreadPool::ShutDown()
{
    CheckShut();
    
    for (unsigned int i = 0; i < m_threads_num; ++i)
    {
        AddTask(std::make_shared<std::function<int(void)>>([]()
                {s_status = DONE; return 0;}), LEAST_PRIORITY);
    }

    m_is_terminated = true;
}

/*----------------------------- AwaitTermination -----------------------------*/
void ThreadPool::AwaitTermination()
{
    CheckNotShut();
    
    m_threads.for_each([](const std::thread::id& key,
            const std::shared_ptr<std::thread>& value)
    {
        (void)key;
        if(value->joinable())
        {
            value->join();
        }
    });
}

/*------------------------------ ThreadRoutine -------------------------------*/
void ThreadPool::ThreadRoutine(ThreadPool *tp)
{
    while (DONE != s_status)
    {
        std::shared_ptr<Task> task;
        tp->m_tasksQueue.Pop(task);
        task->Run();
    }
}

/*----------------------------------------------------------------------------*/
/*-------------------------------- exceptions --------------------------------*/
/*----------------------------------------------------------------------------*/

void ThreadPool::CheckShut() const
{
    if (true == m_is_terminated)
    {
        throw std::invalid_argument("ThreadPool is down!");
    }
}

void ThreadPool::CheckNotShut() const
{
    if (true != m_is_terminated)
    {
        throw std::invalid_argument("ThreadPool is not down!");
    }
}

void ThreadPool::CheckPaused() const
{
    if (RUN != m_status)
    {
        throw std::invalid_argument("ThreadPool is paused!");
    }
}

void ThreadPool::CheckRunning() const
{
    if (RUN == m_status)
    {
        throw std::invalid_argument("ThreadPool is not paused!");
    }
}

unsigned int ThreadPool::CheckNumOfThreads(unsigned int threadsNum)
{
    if (0 == threadsNum)
    {
        throw std::invalid_argument("num of threads is 0");
    }

    return threadsNum;
}

/*----------------------------------------------------------------------------*/
/*-------------------------------- TaskFuture --------------------------------*/
/*----------------------------------------------------------------------------*/

ThreadPool::TaskFuture::TaskFuture(std::shared_ptr<Task> task): m_task(task) {}

/*-------------------------------- WaitResult --------------------------------*/
int ThreadPool::TaskFuture::WaitResult(std::chrono::milliseconds timeout) const
{
    return m_task->WaitResult(timeout);
}

/*-------------------------------- GetStatus ---------------------------------*/
int ThreadPool::TaskFuture::GetStatus() const
{
    return m_task->GetStatus();
}

/*----------------------------------------------------------------------------*/
/*----------------------------------- Task -----------------------------------*/
/*----------------------------------------------------------------------------*/

ThreadPool::Task::Task(std::shared_ptr<std::function<int ()>> func, 
                       int priority): m_func(func), m_sem(size_t(0)), 
                       m_priority(priority), m_result(1), m_status(WAIT) {}

/*-------------------------------- operator< ---------------------------------*/
bool ThreadPool::Task::operator<(const ThreadPool::Task &other) const
{
    return bool(m_priority > other.m_priority);
}

/*----------------------------------- Run ------------------------------------*/
void ThreadPool::Task::Run()
{
    m_status = RUN;

    try
    {
        (*m_func)();
    }
    catch(...)
    {
    }
    
    m_status = DONE;
    m_result = 0;
    m_sem.Post();
}

/*-------------------------------- WaitResult --------------------------------*/
int ThreadPool::Task::WaitResult(std::chrono::milliseconds timeout) const
{
    m_sem.WaitFor(timeout);
    
    return m_result;
}

/*-------------------------------- GetStatus ---------------------------------*/
int ThreadPool::Task::GetStatus() const
{
    return m_status;
}

/*----------------------------- TaskLessFunctor ------------------------------*/
bool ThreadPool::TaskLessFunctor::operator()(std::shared_ptr<Task> task1,
                                             std::shared_ptr<Task> task2)
{
    return (*task1) < (*task2);
}

} //namespace ilrd

