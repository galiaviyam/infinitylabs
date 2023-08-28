
#ifndef ILRD_RD136_7_SEMAPHORE_HPP
#define ILRD_RD136_7_SEMAPHORE_HPP

#include <cstddef>              // size_t
#include <mutex>                //mutex
#include <condition_variable>   // condition_variable
#include <chrono>               // chrono_t
#include <atomic>               // atomic

namespace ilrd
{

class Semaphore
{
public:
    explicit Semaphore(std::size_t count = 0);
    Semaphore(const Semaphore&) = delete;
    Semaphore& operator=(const Semaphore&) = delete;

    void Wait();
    bool WaitFor(std::chrono::milliseconds timeout);
    void Post();


private:
    std::mutex m_mutex;
    std::condition_variable m_cond;
    std::atomic<size_t> m_count;
};

}

#endif // ILRD_RD136_7_SEMAPHORE_HPP
