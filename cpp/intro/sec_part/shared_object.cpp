#include <iostream>	//cout

void Foo()
{
	std::cout << "Foo()" << std::endl;
}
void Foo(int i)
{
	std::cout << "Foo(int " << i << ")" << std::endl;
}
void Foo(char c)
{
	std::cout << "Foo(char " << c << ")" << std::endl;
}

