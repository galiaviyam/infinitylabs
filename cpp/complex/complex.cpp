/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Complex                 */
/*   Date:      27/03/23                */
/*   Reviewer:  Eitan                   */
/*                                      */
/****************************************/

#include <iostream> // cout

#include "complex.hpp"		// header file 


//------------------------------ I/O Operators --------------------------------
namespace ilrd
{

std::ostream& operator<<(std::ostream& os, const Complex& comp_)
{
	os << comp_.GetReal() << std::showpos << comp_.GetImaginary() 
	<< std::noshowpos << "i" << std::endl;
	
	return os; 
}

std::istream& operator>>(std::istream& is, Complex *comp_)
{
	double input = 0;
	
	is >> input;
	comp_->SetReal(input);
	
	is >> input;
	comp_->SetImaginary(input);
	
	return is;
}
}


