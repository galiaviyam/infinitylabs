/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Singleton               */
/*   Date:      04/06/23                */
/*   Reviewer:  Ariel                   */
/*                                      */
/****************************************/

#ifndef ILRD_RD136_7_SINGLETON_HPP
#define ILRD_RD136_7_SINGLETON_HPP

#include <atomic>   // atomic
#include <mutex>    // mutex

namespace ilrd
{

template <class T>
class Singleton
{
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static T *GetInstance();

private:
    Singleton() = default;

    static std::mutex m_mutex;
};

template <class T>
std::mutex Singleton<T>::m_mutex;

template <class T>
T *Singleton<T>::GetInstance()
{
    static std::atomic<T *> instance(0);

    T *tmp = instance.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire);

    if (0 == tmp)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::atomic_thread_fence(std::memory_order_relaxed);
        
        if (0 == tmp)
        {
            tmp = new T;
            std::atomic_thread_fence(std::memory_order_release);
            instance.store(tmp, std::memory_order_relaxed);

            std::atexit([]()
            {
                delete instance.load();
            });
        }
    }

    return tmp;
}
}   // namespace ilrd

#endif /* ILRD_RD136_7_SINGLETON_HPP */
