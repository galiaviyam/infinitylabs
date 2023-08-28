#include <iostream>
#include <cstdlib>
#include <ctime>

#include "priority_queue.hpp"

void TestPQ(void);

int main(void)
{
    TestPQ();

    return 0;
}

void TestPQ(void)
{
    ilrd::PriorityQueue<int> pq;

    std::cout << "------- PQ -------" << std::endl;

    (pq.empty()) ? 
    std::cout << "SUCCESS\n" : std::cout << "FAIL\n";
    srand(time(NULL));

    bool status = true;
    for (std::size_t i = 0; (i < 10000) && status; ++i)
    {
        int rand_num = rand() % 10000;
        pq.push(rand_num);
        status = (rand_num <= pq.front());
    }

    std::cout << "push:\n";
    (!pq.empty()) ? std::cout << "SUCCESS\n" : std::cout << "FAIL,";
    (status) ? std::cout << "SUCCESS\n" : std::cout << "FAIL\n";

    for (std::size_t i = 0; (i < 10000) && status; ++i)
    {
        int temp = pq.front();
        pq.pop();
        status = (temp >= pq.front());
    }

    std::cout << "\npop:\n";
    status ? std::cout << "SUCCESS\n" : std::cout << "FAIL,";
    (pq.empty()) ? std::cout << "SUCCESS\n" : std::cout << "FAIL\n";
}
