/****************************************/
/*                                      */
/*   Developer: Gali Aviyam             */
/*   Project:   c++11 concurrency       */
/*   Date:      18/05/23                */
/*                                      */
/****************************************/
#include <iostream>
#include <atomic>
#include <future>
#include <vector>
#include <thread>
#include <mutex>

class SpinLock
{
public:
    void Lock();
    void Unlock();

private:
    std::atomic<bool> m_lock = {false};
};

void TestSpinLock(void);
void TestLockGuard(void);
void TestConditionVariable(void);
void TestAdoptLock(void);
void TestAtomicInt(void);

int main(void)
{
    TestSpinLock();
    TestLockGuard();
    TestConditionVariable();
    TestAdoptLock();
    TestAtomicInt();

    return 0;
}

void SpinLock::Lock()
{
    while (m_lock.exchange(true, std::memory_order_acquire))
    {
        while (m_lock.load(std::memory_order_relaxed));
    }
}

void SpinLock::Unlock()
{
    m_lock.store(false, std::memory_order_release);
}

void TestSpinLock(void)
{
    std::vector<std::future<void>> futures;
    SpinLock lock;

    std::cout << "SpinLock: " << std::endl;

    for (std::size_t i = 0; i < 10; ++i)
    {
        futures.push_back(std::async(std::launch::async, 
        [&lock, i]()
        {
            lock.Lock();
            std::cout << "Locked from: " << i << std::endl;
            lock.Unlock();
            std::cout << "Unlocked from: " << i << std::endl;
        }));
    }
}

void TestLockGuard(void)
{
    std::size_t countr = 0;
    std::mutex m;
    std::vector<std::future<void>> futures;

    std::cout << "\nLockGuard: " << std::endl;

    for (std::size_t i = 0; i < 10; ++i)
    {
        futures.push_back(std::async(std::launch::async,
        [&m, &countr, i]()
        {
            std::lock_guard<std::mutex> lock(m);
            ++countr;
            std::cout << "counter: " << countr << " from: " << i << std::endl;
        }));
    }
}

void TestConditionVariable(void)
{
    std::vector<std::future<void>> futures;
    std::condition_variable cv;
    std::mutex m;
    
    std::cout << "\nConditionVariable: " << std::endl;

    for (std::size_t i = 0; i < 10; ++i)
    {
        futures.push_back(std::async(std::launch::async,
        [&m, &cv, i]()
        {
            std::unique_lock<std::mutex> lock(m);
            std::cout << "Waiting from: " << i << std::endl;
            cv.wait(lock);

            std::cout << "Notified from: " << i << std::endl;
            
        }));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::unique_lock<std::mutex> lock(m);
    std::cout << "Notifying all" << std::endl;
    cv.notify_all();
}

void TestAdoptLock(void)
{
    std::vector<std::future<void>> futures;
    std::mutex mutex1, mutex2, mutex3;
    std::mutex *mutexes[] = {&mutex1, &mutex2, &mutex3};
    
    std::cout << "\nAdoptLock: " << std::endl;

    for (std::size_t i = 0; i < 10; ++i)
    {
        futures.push_back(std::async(std::launch::async,
        [&mutexes, i]()
        {
            std::lock(*mutexes[0], *mutexes[1], *mutexes[2]);
            std::lock_guard<std::mutex> lock1{*mutexes[0], std::adopt_lock};
            std::lock_guard<std::mutex> lock2{*mutexes[1], std::adopt_lock};
            std::lock_guard<std::mutex> lock3{*mutexes[2], std::adopt_lock};

            std::cout << "Locked from: " << i << std::endl;
        }));
    }
}

void TestAtomicInt(void)
{
    std::vector<std::future<void>> futures;
    std::atomic_int counter(0);

    std::cout << "\nAtomicInt: " << std::endl;

    for (std::size_t i = 0; i < 10; ++i)
    {
        futures.push_back(std::async(std::launch::async,
        [&counter, i]()
        {
            counter.fetch_add(i, std::memory_order_relaxed);
        }));
    }

    for (auto &f : futures)
    {
        f.wait();
    }

    std::cout << "Final counter: " << counter; 
    (45 == counter) ? 
    std::cout << " SUCCESS\n" :  std::cout << " FAIL\n";
}

