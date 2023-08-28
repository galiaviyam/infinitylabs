/****************************************/
/*                                      */
/*   Developer: Gali Aviyam             */
/*   Project:   Shared Pointer          */
/*   Date:      13/03/23                */
/*   Reviewer:  Eliran                  */
/*                                      */
/****************************************/

#include <iostream>         // ostream

#include "shared_ptr.hpp"   // shared_ptr header file

using namespace ilrd;
using std::cout;
using std::endl;

class Base
{
public:
	Base(int x = 0): m_a(x) {}

	int GetA() {return m_a;}

private:
	int m_a;
};

class Derived: public Base
{
public:
	Derived(int x = 0, int y = 0): Base(x), m_b(y) {}

	int GetB() {return m_b;}

private:
	int m_b;
};

void SharedPtrTest();
static void TestResEqual(int result, int expected);

int main()
{
	SharedPtrTest();
	
	return 0;
}


void SharedPtrTest()
{
	SharedPtr<Derived> derived(new Derived(3,4));
	
	for (int i = 0; i < 3; ++i)
	{
		SharedPtr<Base> base(derived);

		TestResEqual(base->GetA(), 3);
	}
	
	SharedPtr<Base> base2[3];
	for (int i = 0; i < 3; ++i)
	{
		base2[i] = derived;

		TestResEqual(base2[i]->GetA(), 3);
	}

	SharedPtr<Derived> derived2[3];
	for (int i = 0; i < 3; ++i)
	{
		derived2[i] = derived;

		TestResEqual(derived2[i]->GetA(), 3);
		TestResEqual(derived2[i]->GetB(), 4);
	}

	for (int i = 0; i < 3; ++i)
	{
		derived2[i] = derived2[i];

		TestResEqual((*derived2[i]).GetA(), 3);
		TestResEqual((*derived2[i]).GetB(), 4);
	}
}

static void TestResEqual(int result, int expected)
{
	if (expected == result)
	{
		cout << "\033[32mPass\033[0m" << endl;
	}
	else
	{
		cout << "\033[31mFAILURE\033[0m" << endl;
	}
}