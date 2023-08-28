/****************************************/
/*                                      */
/*   Developer: Gali Aviyam             */
/*   Project:   Bit Array               */
/*   Date:      15/05/23                */
/*   Reviewer:  Matan                   */
/*                                      */
/****************************************/

#include <iostream>         	//cout

#include "bit_array.hpp"    //bitarr header

using namespace ilrd;

void TestAssignment(void);
void TestOr(void);
void TestAnd(void);
void TestXor(void);
void TestSet(void);
void TestGet(void);
void TestFlip(void);
void TestCount(void);
void TestExcep(void);
void TestToString(void);
void TestShiftLeft(void);
void TestShiftRight(void);

static void TestBoolRes(int result);

int main()
{
    TestAssignment();
    TestOr();
	TestAnd();
    TestXor();
	TestSet();
	TestGet();
	TestFlip();
	TestCount();
	TestExcep();
	TestToString();
	TestShiftLeft();
	TestShiftRight();
	return 0;
}

void TestAssignment(void)
{
    BitArray<64> b1;
    BitArray<64> b2;
    BitArray<200> b3;
 
    b1[1] = true;
    
    b2[2] = b1[1];
    
    b3[1] = false;

   	std::cout << "------ operator= ------" << std::endl;
    TestBoolRes(true == b2[2]);
   	
	std::cout << "------ operator== ------" << std::endl;
	TestBoolRes(b2[2] == b1[1]);

   	std::cout << "------ operator!= ------" << std::endl;
	TestBoolRes(b2[2] != b3[1]);
}


void TestOr(void)
{
    BitArray<64> b1;
    BitArray<64> b2; 

   	std::cout << "------ operator|= ------" << std::endl;

	for (size_t i = 0; i < 64; ++i)
	{
    	b1[i] = true;
	}

    b2 |= b1;
    
    TestBoolRes(true == b2[1]);
}

void TestAnd(void)
{
    BitArray<64> b1;
    BitArray<64> b2; 
    BitArray<64> b3; 

   	std::cout << "------ operator&= ------" << std::endl;

	for (size_t i = 0; i < 64; ++i)
	{
    	b1[i] = true;
	}

	for (size_t i = 0; i < 64; ++i)
	{
    	b3[i] = true;
	}

    b2 &= b1;
    b3 &= b1;

    TestBoolRes(false == b2[1]);
    TestBoolRes(true == b3[1]);
}

void TestXor(void)
{
    BitArray<64> b1;
    BitArray<64> b2;
    BitArray<64> b3; 

   	std::cout << "------ operator^= ------" << std::endl;
 
	for (size_t i = 0; i < 64; ++i)
	{
    	b1[i] = true;
	}

	for (size_t i = 0; i < 64; ++i)
	{
    	b3[i] = true;
	}

    b1 ^= b2;
	b2 ^= b3;
    b3 ^= b1;

    TestBoolRes(true == b1[1]);
    TestBoolRes(true == b2[1]);
    TestBoolRes(false == b3[1]);
}

void TestSet(void)
{
    BitArray<64> b1;
    BitArray<64> b2; 

   	std::cout << "------ Set ------" << std::endl;

	b1.Set();
    b2.Set(5);

    TestBoolRes(true == b1[1]);
    TestBoolRes(true == b2[5]);
    TestBoolRes(false == b2[1]);
}

void TestGet(void)
{
    BitArray<64> b1;
    BitArray<64> b2; 

   	std::cout << "------ Get ------" << std::endl;

	b1.Set();
    b2.Set(5);

    TestBoolRes(b1.Get(1));
    TestBoolRes(b2.Get(5));
    TestBoolRes(!(b2.Get(1)));
}

void TestFlip(void)
{
    BitArray<64> b1;
    BitArray<64> b2; 

   	std::cout << "------ Flip ------" << std::endl;

	b1.Set();
	b1.Flip(1);
    TestBoolRes(!(b1.Get(1)));

	b2.Flip(5);
    TestBoolRes(b2.Get(5));

	b2.Flip();
    TestBoolRes(!(b2.Get(5)));
}

void TestCount(void)
{
    BitArray<64> b1;
    BitArray<100> b2;

   	std::cout << "------ Count ------" << std::endl;
   	b2.Set();
    TestBoolRes(100 == b2.Count());

	b1.Flip(1);
    TestBoolRes(1 == b1.Count());

	b1.Flip(5);
    TestBoolRes(2 == b1.Count());

	b1.Flip(6);
	b1.Flip(10);
	b1.Flip(30);

    TestBoolRes(5 == b1.Count());
}

void TestExcep(void)
{
    BitArray<64> b1;

   	std::cout << "------ Exception ------" << std::endl;

	try
	{
		b1[100];
	}
	catch(std::out_of_range&)
	{
   		std::cout << "\033[32mPass\033[0m" << std::endl;
	}
	catch(...)
	{
		std::cout << "\033[31mFail\033[0m" << std::endl;
	}

}

void TestToString(void)
{
    BitArray<64> b1;
    BitArray<20> b2; 

   	std::cout << "------ ToString ------" << std::endl;

	b1.Set();
	b1.Flip(1);

	b2.Flip(5);
	b2.Flip(8);
	b2.Flip(15);

	b2.Flip();

	std::cout << b1.ToString() << std::endl;	
	std::cout << b2.ToString() << std::endl;
}

void TestShiftLeft(void)
{
    BitArray<400> b1;
    BitArray<400> b2;

   	std::cout << "------ operator<< ------" << std::endl;

    b1.Set(0);
    b2.Set(300);

    b1 <<= 300;
    TestBoolRes(b1 == b2);
}

void TestShiftRight(void)
{
    BitArray<400> b1;
    BitArray<400> b2;

   	std::cout << "------ operator>> ------" << std::endl;

    b1.Set(0);
    b2.Set(300);

    b2 >>= 300;
    TestBoolRes(b1 == b2);
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
