#include <iostream>
#include <vector>
#include <atomic>
#include <chrono>
#include <future>

#include "thread_pool.hpp"

void TestThreadPool(void);

int main(void)
{
    for (int i = 0; i < 100; ++i)
    {
        TestThreadPool();
    }
    
    return 0;
}

void TestThreadPool(void)
{
    ilrd::ThreadPool pool(8);
    std::vector<ilrd::ThreadPool::TaskFuture> futures;
    std::atomic<std::size_t> taskCounter(0);

    std::cout << "TestThreadPool: " << std::endl;

    pool.Pause();

    for (std::size_t i = 0; i < 100; ++i)
    {
        futures.push_back(pool.AddTask(std::make_shared<std::function<int()>>(
        [i, &taskCounter]
        { 
            std::cout << "task " << i  << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            ++taskCounter;
            return 1;
        }), static_cast<ilrd::ThreadPool::Priority>(i % 3)));
    }

    pool.Resume();

    // pool.SetNumOfThreads(16);
    // pool.SetNumOfThreads(12);
    
    pool.Pause();
    for (auto& future : futures)
    {
        std::cout << "status: ";
        switch (future.GetStatus())
        {
            case ilrd::ThreadPool::WAIT:
                std::cout << "WAIT" << '\n';
                break;
            case ilrd::ThreadPool::RUN:
                std::cout << "RUN" << '\n';
                break;
            case ilrd::ThreadPool::DONE:
                std::cout << "DONE" << '\n';
                break;
            default:
                std::cout << "UNKNOWN" << '\n';
                break;
        }
    }
    pool.Resume();
    
    // pool.SetNumOfThreads(4);
    // pool.SetNumOfThreads(16);

    std::size_t counter = 0;
    
    pool.ShutDown();
    pool.AwaitTermination();
    for (auto& future : futures)
    {
        counter += ((0 == future.WaitResult()) ?  1 : 0);
    }

    std::cout << "test: ";
    (100 == taskCounter) ? 
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";
    (100 == counter) ? std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";

}