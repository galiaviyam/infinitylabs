/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   RCstring                */
/*   Date:      31/03/23                */
/*   Reviewer:  Itay                    */
/*                                      */
/****************************************/

#include <iosfwd>       // ostream
#include <cstddef>      // size_t
#include <cstring>      // strcmp

#include "rcstring.hpp" // header file

using namespace ilrd;
using std::cout;
using std::endl;

static void RCStringTest(void);
static void TestBoolResult(int result);
static void TestNotNull(const void *result);

int main()
{
	RCStringTest();
	
	return 0;
}

void RCStringTest(void)
{
	const char *string1 = "Gali Aviyam";
    
	cout << "------- Default Constructor -------" << endl;
    
    RCString str1(string1);
    const char *ptr1 = str1.Cstr();
	TestNotNull(ptr1);
	cout << "------- Shared Constructor -------" << endl;
	TestBoolResult(0 == ::strcmp(ptr1, "Gali Aviyam"));

	cout << "------- Copy Constructor -------" << endl;

    RCString str2(str1);
    const char *ptr2 = str2.Cstr();
	TestBoolResult(ptr1 == ptr2);

    size_t len1 = str1.Length();
	cout << "------------ Length ------------" << endl;
	TestBoolResult(::strlen(string1) == len1);

	cout << "---------- operator == ---------" << endl;
	TestBoolResult(str1 == str2);
	
	cout << "---------- operator > ----------" << endl;
	RCString str3("Gali");
	TestBoolResult(str1 > str3);
	
	cout << "---------- operator < ----------" << endl;
	TestBoolResult(str3 < str1);
	
	cout << "------- ostream operator -------" << endl;
	cout << str1 << endl;
	
	cout << "---------- operator = ----------" << endl;
	str1 = "Gali";
	TestBoolResult(str1 == str3);
	
	str1 = str2;
	TestBoolResult(str1 == str2);
	
	cout << "---------- operator [] ---------" << endl;
	TestBoolResult(str3[1] == 'a');
	str3[1] = 'A';
	TestBoolResult(str3 == "GAli");
}

static void TestBoolResult(int result)
{
	if (result)
	{
		cout << "\033[0;32mPASS\033[0m" << endl;
	}
	else
	{
		cout << "\033[0;31mFAIL\033[0m" << endl;
	}
}

static void TestNotNull(const void *result)
{
	if (result)
	{
		cout << "\033[0;32mPASS\033[0m" << endl;
	}
	else
	{
		cout << "\033[0;31mFAIL\033[0m" << endl;
	}
}
