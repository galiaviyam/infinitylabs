/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Complex                 */
/*   Date:      27/03/23                */
/*   Reviewer:  Eitan                   */
/*                                      */
/****************************************/

#ifndef ILRD_RD136_7_COMPLEX_HPP
#define ILRD_RD136_7_COMPLEX_HPP

#include <iosfwd> // ostream

using std::ostream;
using std::istream;

namespace ilrd
{

class Complex;

inline const Complex operator+(const Complex& comp1_, const Complex& comp2_);
inline const Complex operator-(const Complex& comp1_, const Complex& comp2_);
inline const Complex operator*(const Complex& comp1_, const Complex& comp2_);
inline const Complex operator/(const Complex& comp1_, const Complex& comp2_);
inline bool operator==(const Complex& comp1_, const Complex& comp2_);
inline bool operator!=(const Complex& comp1_, const Complex& comp2_);
std::ostream& operator<<(std::ostream& os, const Complex& comp_);
std::istream& operator>>(std::istream& is, Complex *comp_);

class Complex
{
public:
	inline Complex(double r_ = 0, double i_ = 0);
	
	inline Complex& operator+=(const Complex& other_);
	inline Complex& operator-=(const Complex& other_);
	inline Complex& operator*=(const Complex& other_);
	inline Complex& operator/=(const Complex& other_);
	
	inline void SetReal(double r_);
	inline void SetImaginary(double i_);
	inline double GetReal() const;
	inline double GetImaginary() const;

private:
	double m_r;
	double m_i;
};

inline Complex::Complex(double r_, double i_): m_r(r_), m_i(i_) {}

//------------------------------ Math Operators -------------------------------

inline const Complex operator+(const Complex& comp1_, const Complex& comp2_)
{
	Complex tmp(comp1_);
	
	return (tmp += comp2_);
}

inline const Complex operator-(const Complex& comp1_, const Complex& comp2_)
{
	Complex tmp(comp1_);
	
	return (tmp -= comp2_);
}

inline const Complex operator*(const Complex& comp1_, const Complex& comp2_)
{
	Complex tmp(comp1_);
	
	return (tmp *= comp2_);
}

inline const Complex operator/(const Complex& comp1_, const Complex& comp2_)
{
	Complex tmp(comp1_);
	
	return (tmp /= comp2_);
}

//-------------------------- Comparison Operators -----------------------------
inline bool operator==(const Complex& comp1_, const Complex& comp2_)
{
	return ((comp1_.GetReal() == (comp2_.GetReal())) && 
			(comp1_.GetImaginary() == (comp2_.GetImaginary())));
}

inline bool operator!=(const Complex& comp1_, const Complex& comp2_)
{
	return (!(comp1_ == comp2_));
}

//----------------------- Compound Assignment Operators -----------------------

inline Complex& Complex::operator+=(const Complex& other_)
{
	m_r += other_.m_r;
	m_i += other_.m_i;
	
	return (*this);	
}

inline Complex& Complex::operator-=(const Complex& other_)
{   
	m_r -= other_.m_r;
	m_i -= other_.m_i;
	
	return (*this);	
}

inline Complex& Complex::operator*=(const Complex& other_)
{
	m_r *= other_.m_r;
	m_i *= other_.m_i;
	
	return (*this);
}

inline Complex& Complex::operator/=(const Complex& other_)
{
	m_r /= other_.m_r;
	m_i /= other_.m_i;
	
	return (*this);
}

//---------------------------- Setter and Getter ------------------------------

inline void Complex::SetReal(double r_)
{
	m_r = r_;
}

inline void Complex::SetImaginary(double i_)
{
	m_i = i_;
}

inline double Complex::GetReal() const
{
	return m_r;
}

inline double Complex::GetImaginary() const
{
	return m_i;
}

}

#endif // ILRD_RD136_7_SIMPLE_STRING_HPP
