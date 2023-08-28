/***************************************/
/*                                     */   
/*  Developer: Gali Aviyam             */
/*  Project:   Scheduler               */
/*  Date:      20/06/23                */
/*  Reviewer:  Or                      */
/*                                     */
/***************************************/

#include <iostream>         // cout
#define IMPL_HANDLETON

#include "scheduler.hpp"    // scheduler class

using namespace ilrd;

void SchedTest(void);

int main(void)
{
    SchedTest(); 
    return 0;
}

void SchedTest(void)
{
    auto sched = Handleton<Scheduler>::GetInstance();
    int counter = 0;

    sched->AddTask(std::make_shared<std::function<bool(void)>>
    ([&counter]()
    {
        if (counter < 3)
        {
            std::cout << "Task added" << std::endl;
            ++counter;
            return false;
        }
        return true;
    }), std::chrono::milliseconds(1));

    sched->Stop();

    sched->AddTask(std::make_shared<std::function<bool(void)>>
    ([&counter]()
    {
        if ((3) == counter)
        {
            std::cout << "test PASS" << std::endl;
        }
        else
        {
            std::cout << "test FAIL" << std::endl;
        }
        return true;
    }), std::chrono::seconds(2));


    sched->Run();

    sched->Stop();
    sched->Run();
    sched->Run();
    std::this_thread::sleep_for(std::chrono::seconds(3));
}