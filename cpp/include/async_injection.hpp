/***************************************/
/*                                     */
/*  Developer: Gali Aviyam             */
/*  Project:   Async Injection         */
/*  Date:      21/06/23                */
/*  Reviewer:  Shauli                  */
/*                                     */
/***************************************/

#ifndef ILRD_RD136_7_ASYNC_INJECTION_HPP
#define ILRD_RD136_7_ASYNC_INJECTION_HPP

#include <memory>       // shared_ptr
#include <functional>   // function
#include <chrono>       // milliseconds

namespace ilrd
{

class AsyncInjection
{
public:
    AsyncInjection(const AsyncInjection&) = delete;
    AsyncInjection& operator=(const AsyncInjection&) = delete;
    
    static void Inject(std::function<bool(void)> action, std::chrono::milliseconds interval);
    bool operator()();

private:
    AsyncInjection(std::function<bool(void)> action, std::chrono::milliseconds interval);
    ~AsyncInjection();

    std::function<bool(void)> m_action;
};

}// namespace ilrd

#endif /* ILRD_RD136_7_ASYNC_INJECTION_HPP */