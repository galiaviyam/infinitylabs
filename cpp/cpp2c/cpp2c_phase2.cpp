#include <iostream>

struct A
{

};

struct B
{
	int x;
	int y;
};

int main(void)
{
	std::cout << sizeof(struct A) << std::endl;
	std::cout << sizeof(struct B) << std::endl;
	
	return 0;
}
