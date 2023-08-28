#include <iostream>	//cout

namespace useless
{ 
	unsigned int g_wasteful[400];
	extern int g_notthere;
	void Foo() {std::cout << "useless Foo()" << std::endl;}

	namespace wasteoftyme
	{
		void Foo() {std::cout << "wasteoftyme Foo()" << std::endl;}
	}//namespace wasteoftyme
}//namespace useless

namespace stupid
{
	void Foo() {std::cout << "stupid Foo()" << std::endl;}
	void Bar() {}
	void DoNothing(unsigned int) {}
}//namespace stupid

namespace useless
{
	void DoNothing(int) {}
}//namespace useless

using namespace useless;

void DoStuff()
{
    stupid::Bar();
    Foo();
    using stupid::Foo;
    Foo();
    DoNothing(g_wasteful[3] + 1);
}

void Foo() {std::cout << "regular Foo()" << std::endl;}

using namespace stupid;

namespace comeon = useless::wasteoftyme;

void DoMoreStuff()
{
    comeon::Foo();
    ::Foo(); //try uncommenting this line, solve the error
    Bar(); //why doesn't this line create an error?
    DoNothing(g_wasteful[3] + 1);
}

namespace useless
{
	void DoUselessStuff()
	{
		DoNothing(g_wasteful[3] + 1);
	}
}//namespace useless

int main(void)
{
	useless::Foo();
	wasteoftyme::Foo();
	stupid::Foo();
	DoStuff();
	DoMoreStuff();
	
	return 0;
}
