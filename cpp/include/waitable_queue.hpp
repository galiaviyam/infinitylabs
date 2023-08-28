/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Waitable Queue          */
/*   Date:      22/05/23                */
/*   Reviewer:  Aviv                    */
/*                                      */
/****************************************/

#ifndef ILRD_RD136_7_WAITABLE_QUEUE_HPP
#define ILRD_RD136_7_WAITABLE_QUEUE_HPP

#include <boost/noncopyable.hpp>    //noncopppyable

#include "semaphore.hpp"            //semaphore header
#include "priority_queue.hpp"       //pq header

namespace ilrd
{
template<class Container>
class WaitableQueue :  private boost::noncopyable
{
public:
    void Push(const typename Container::value_type& data);
    bool Pop(typename Container::reference ret_val);
    bool Pop(typename Container::reference ret_val, 
             std::chrono::milliseconds timeout);
    bool IsEmpty() const; //not thread safe

private:
    Container m_container;
    Semaphore m_sem;
    mutable std::mutex m_mutex;
};

template<class Container>
void WaitableQueue<Container>::Push(const typename Container::value_type& data)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    m_container.push(data);
    m_sem.Post();
}

template<class Container>
bool WaitableQueue<Container>::Pop(typename Container::reference ret_val)
{
    return Pop(ret_val, std::chrono::hours(INT32_MAX));
}

template<class Container>
bool WaitableQueue<Container>::Pop(typename Container::reference ret_val, 
                                   std::chrono::milliseconds timeout)
{
    if (m_sem.WaitFor(timeout))
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        ret_val = m_container.front();

        m_container.pop();

        return true;
    }

    return false;
}

template<class Container>
bool WaitableQueue<Container>::IsEmpty() const
{
    return m_container.empty();
}

}//ilrd

#endif    // ILRD_RD136_7_WAITABLE_QUEUE_HPP    
