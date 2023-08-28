#include <iostream>   /* cout */
using namespace std;
/*----------------------------------------------------------------------------*/
class Type
{
public:
    Type(int add);
    int operator()(int num) const;

private:
	const int m_adder;
};
/*----------------------------------------------------------------------------*/
Type::Type(int add) : m_adder(add) {}

int Type::operator()(int num) const
{
    return num + m_adder;
}

Type make_adder(int num)
{
    return Type(num);
}

/*----------------------------------------------------------------------------*/
int main(void)
{	
	Type add_4 = make_adder(4);
	cout << add_4(5) << endl;
	cout << add_4(8) << endl;

	return 0;
}
/*----------------------------------------------------------------------------*/