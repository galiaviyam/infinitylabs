/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Waitable Queue          */
/*   Date:      22/05/23                */
/*   Reviewer:  Aviv                    */
/*                                      */
/****************************************/

#include <iostream>
#include <future>

#include "waitable_queue.hpp"   //header file


using namespace ilrd;
using std::cout;
using std::endl;

static void WQTest(void);

int main(void)
{
    WQTest();

    return 0;
}

static void WQTest(void)
{
	std::vector<std::future<void>> future_push;
	std::vector<std::future<void>> future_pop;
	ilrd::WaitableQueue<ilrd::PriorityQueue<int>> queue;
	std::chrono::milliseconds deadline(1000);
	int counter = 0;

	(queue.IsEmpty()) ? std::cout << "Success\n" : std::cout << "Fail\n";

	(false == queue.Pop(counter, deadline)) ? std::cout << "Success\n" : 
											  std::cout << "Fail\n";

	for (int i = 0; i < 100; ++i)
    {
        future_push.push_back(std::async(std::launch::async, [&counter, &queue, i]
        {
			queue.Push(i);
			++counter;
        }));

		future_pop.push_back(std::async(std::launch::async, [&counter, &queue, i]
        {
			int temp = 0;
			queue.Pop(temp);

			--counter;
        }));
    }

	for (auto &fut : future_push)
    {
        fut.wait();
    }
	for (auto &fut : future_pop)
    {
        fut.wait();
    }
	
	(0 == counter) ? std::cout << "Success\n" : std::cout << "Fail\n";
	(queue.IsEmpty()) ? std::cout << "Success\n" : std::cout << "Fail\n";
}
