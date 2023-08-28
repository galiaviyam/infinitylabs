/***************************************/
/*                                     */
/*  Developer: Gali Aviyam             */
/*  Project:   Async Injection         */
/*  Date:      21/06/23                */
/*  Reviewer:  Shauli                  */
/*                                     */
/***************************************/

#include <iostream>  

#include "scheduler.hpp"        // scheduler class
#include "async_injection.hpp"  // async_injection class


using namespace ilrd;

void AsyncTest(void);

int main(void)
{
    AsyncTest(); 
    return 0;
}


void AsyncTest(void)
{
    int counter = 0;
    AsyncInjection::Inject(std::function<bool()>
    ([&counter]()
    {
       if (counter < 3)
        {
            std::cout << "Action injected" << std::endl;
            ++counter;
            return false;
        }
        return true;
    }), std::chrono::milliseconds(0));

    std::this_thread::sleep_for(std::chrono::seconds(5));

    AsyncInjection::Inject(std::function<bool(void)>
    ([&counter]()
    {
        if ((3) == counter)
        {
            std::cout << "Async PASS" << std::endl;
        }
        else
        {
            std::cout << "Async FAIL" << std::endl;
        }
        return true;
    }), std::chrono::seconds(2));
    
}
