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

static void TestBoolResult(int result);
static void TestNumResultEqual(size_t result, size_t expected);
static void BenchmarkTest(void);
/*----------------------------------------------------------------------------*/
using namespace ilrd;
using namespace std;

int main(void)
{
	Complex c1;	//(3,2)
	Complex c2(8, 10);
	Complex c3(20, 14);
	Complex c4(28, 24);
	Complex c5(2,10);
	Complex c6(8,8);
	Complex c7(8,8);
	Complex input;
	
	cout << "Insert numbers: " << endl;
	cin >> &input;
	cout << input;
	
	cout << "GetReal: \t";
	TestNumResultEqual(c1.GetReal(), 0);
	cout << "GetImaginary: \t";
	TestNumResultEqual(c1.GetImaginary(), 0);
	
	cout << "SetReal: \t";
	c1.SetReal(3);
	TestNumResultEqual(c1.GetReal(), 3);
	cout << "SetImaginary: \t";
	c1.SetImaginary(2);
	TestNumResultEqual(c1.GetImaginary(), 2);

	cout << "\n ------- + operator -------"<< endl;
	c2 = c3 + c2;
	TestNumResultEqual(c2.GetReal(), 28);
	TestNumResultEqual(c2.GetImaginary(), 24);
	
	cout << "\n ------- - operator -------"<< endl;
	c2 = c2 - c3;
	TestNumResultEqual(c2.GetReal(), 8);
	TestNumResultEqual(c2.GetImaginary(), 10);
	
	cout << "\n ------- += operator -------"<< endl;
	c1 += c3;
	TestNumResultEqual(c1.GetReal(), 23);
	TestNumResultEqual(c1.GetImaginary(), 16);
	
	cout << "\n ------- -= operator -------"<< endl;
	c1 -= c3;
	TestNumResultEqual(c1.GetReal(), 3);
	TestNumResultEqual(c1.GetImaginary(), 2);
	
	cout << "\n ------- == operator -------"<< endl;
	TestBoolResult((c6 == c7));
	
	cout << "\n ------- != operator -------"<< endl;
	TestBoolResult((c1 != c7));
	
	cout << "\n ------- << operator -------"<< endl;
	cout << c2;
		
	cout << "\n ------- * operator -------"<< endl;
	c1 = c1 * c5;
	cout << c1;
	
	cout << "\n ------- / operator -------"<< endl;
	c1 = c1 / c5;
	cout << c1;
	
	cout << "\n ------- *= operator -------"<< endl;
	c2 *= c3;
	cout << c2;
	
	cout << "\n ------- /= operator -------"<< endl;
	c2 /= c3;
	cout << c2;
	
	BenchmarkTest();
	
	return 0;
}


//----------------------------------------------------------------------------
static void BenchmarkTest(void)
{
	Complex c1(8, 10);
	cout << "benchmark test:" << endl;
	struct timespec start;
	clock_gettime(CLOCK_MONOTONIC, &start);
	
	for (size_t i = 0; i < 10000000; ++i)
	{
		c1 += 1;
	}

	struct timespec end;
	clock_gettime(CLOCK_MONOTONIC, &end);
	
	const double D_10E9 = 1000000000.0;
	double test_time = (end.tv_sec - start.tv_sec) +
					(end.tv_nsec - start.tv_nsec) / D_10E9;;

	cout << "time: " << test_time << endl;
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

static void TestNumResultEqual(size_t result, size_t expected)
{
	if (result == expected)
	{
		cout << "\033[0;32mPASS\033[0m" << endl;
	}
	else
	{
		cout << "\033[0;31mFAIL\033[0m" << endl;
	}
}



