/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Simple String           */
/*   Date:      23/03/23                */
/*   Reviewer:  Ariel K.                */
/*                                      */
/****************************************/

#include <iostream>				// cout

#include "simple_string.hpp"	// header file

using namespace ilrd;
using std::cout;
using std::endl;

int main()
{
	const char *str1 = "Gali";
	const char *str2 = "Aviyam";
	
	String s1("hello");
	String s2(s1);
	String s3("helloooo");
	String s4(str1);
	String s5(str2);
	
	(5 == s1.Length()) ? (cout << "Pass" << endl) : (cout << "Fail" << endl);
	cout << "s1: " << s1.Cstr() << endl;
	(5 == s2.Length()) ? (cout << "Pass" << endl) : (cout << "Fail" << endl);
	cout << "s2: " << s2.Cstr() << endl;
	
	s1 = s3;
	(8 == s1.Length()) ? (cout << "Pass" << endl) : (cout << "Fail" << endl);
	cout << "s1: " << s1.Cstr() << endl;
	
	cout << "Cout " << endl;
	cout << s1 << endl;

	cout << "operator ==" << endl;
	cout << (s1 == s3) << endl;
		
	cout << "operator ==" << endl;
	cout << ("123" == s3) << endl;
	
	cout << "operator >" << endl;
	(0 == (s2 > s3)) ? (cout << "Pass" << endl) : (cout << "Fail" << endl);

	cout << "operator <" << endl;
	(1 == (s2 < s3)) ? (cout << "Pass" << endl) : (cout << "Fail" << endl);

	cout << "operator ==" << endl;
	(0 == (s4 == s5)) ? (cout << "Pass" << endl) : (cout << "Fail" << endl);
	
	return 0;

}

