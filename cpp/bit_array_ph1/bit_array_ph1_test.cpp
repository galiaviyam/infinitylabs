/****************************************/
/*                                      */
/*   Developer: Gali Aviyam             */
/*   Project:   Bit Array               */
/*   Date:      14/05/23                */
/*   Reviewer:  Matan                   */
/*                                      */
/****************************************/

#include <iostream>         //cout

#include "bit_array_ph1.hpp"    //bitarr header

using namespace ilrd;

void TestPhase1(void);
static void TestBoolRes(int result);

int main()
{
    TestPhase1();
    
    return 0;
}

void TestPhase1(void)
{
    BitArray b1;
    BitArray b2;
    BitArray b3(10);
    const BitArray b4(4);
    BitArray b5(4);
   	std::cout << "------ Phase 1 ------" << std::endl;
 
    b1[1] = true;
    
    b2[2] = b1[1];
    
    TestBoolRes(true == b2[2]);
	TestBoolRes(true == b1[1]);

    TestBoolRes((true == b3[1]) && (true == b3[3]));
    
    TestBoolRes((true == b4[2]) && (true == b5[2]));
}

static void TestBoolRes(int result)
{
	if (result)
	{
		std::cout << "\033[32mPass\033[0m" << std::endl;
	}
	else
	{
		std::cout << "\033[31mFail\033[0m" << std::endl;
	}
}
