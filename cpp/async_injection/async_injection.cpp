/***************************************/
/*                                     */
/*  Developer: Gali Aviyam             */
/*  Project:   Async Injection         */
/*  Date:      21/06/23                */
/*  Reviewer:  Shauli                  */
/*                                     */
/***************************************/

#include "scheduler.hpp"        // ilrd::scheduler
#include "handleton.hpp"        // ilrd::handleton

#include "async_injection.hpp"  // ilrd::async_injection


namespace ilrd
{
// INSTANTIATE_HANDLETON(Singleton)
AsyncInjection::AsyncInjection(std::function<bool(void)> action, 
                    std::chrono::milliseconds interval) : m_action(action)
{
    auto sched = Handleton<Scheduler>::GetInstance();

    std::shared_ptr<std::function<bool(void)>> 
        asyncPtr(reinterpret_cast<std::function<bool(void)> *>(this),
    [] 
    (std::function<bool(void)> *ptr)
    {
        delete ptr;
    });

    sched->AddTask(asyncPtr, interval);
}

void AsyncInjection::Inject(std::function<bool(void)> action, 
                                        std::chrono::milliseconds interval)
{
    if (false == action())
    {
        new AsyncInjection(action, interval);
    }
}
    
bool AsyncInjection::operator()()
{
    return (m_action());
}

}// namespace ilrd