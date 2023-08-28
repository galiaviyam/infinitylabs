#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <typeinfo>

using namespace std; 

class X
{
public:
    X(): m_a(0) {}
    ~X();
    
private:
    int m_a;
};

int Foo(int) throw(bad_alloc)
{
    cout << "foo" << endl;
    int *will_throw = new int[10000000000000000];
    return *will_throw;
}

void Bar() throw(bad_cast)
{
    
}

X::~X()
{
    cerr << Foo(m_a) << endl;
}

void Fishi()
{
    X x1;
    
    Bar();
}

int main(void)
{
    Fishi();
    cout << "finished" << endl;
    return 0;
}
