#include <iostream> //cout
using std::cout;
using std::endl;

class X
{
public:
    virtual ~X() {cout << "X::Dtor " << this << endl;}

private:
    double m_a;
};

class Y: public X
{
private:
    int m_b;
};
//void Foo(X x);


int main()
{
//    Y y1;
//    Foo(y1);
    X *xp= new Y[5];

    delete[] xp;

    return 0;
}
