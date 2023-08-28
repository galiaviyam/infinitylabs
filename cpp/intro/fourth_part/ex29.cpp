#include <iostream>

class X
{
public:
    explicit X();
    X(int a_);
    explicit X(int a_, int b_);

    operator int() const;
    void Print() const;

private:
    int m_a;
}; 

X::X() : m_a(0) { }
X::X(int a_) : m_a(a_) { }
X::X(int a_, int b_) : m_a(a_ + b_) { }

X::operator int()const 
{ 
    return m_a;
}

void X::Print() const
{ 
    std::cout << "X::Print() " << m_a << std::endl;
}

void Fifi(const X& x_)
{
    std::cout << "Fifi() " << x_ << std::endl;
    x_.Print();
}


int main()
{
    X x1(7);
    X x2(3, 4);

    Fifi(x1);     // (1)
    Fifi(X(7));   // (2)
    Fifi(static_cast<X>(7));   // (2)
	Fifi((X)7);   // (2)
    Fifi(9);      // (3)
    Fifi(x2); // (4)
	std::cout << "return " << x1 * 3 << std::endl;
    return x1 * 3; //(5)
}
