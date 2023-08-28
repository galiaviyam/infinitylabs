/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Calculator              */
/*   Date:      23/01/23                */
/*   Reviewer:  Or                      */
/*                                      */
/****************************************/

#include <stdio.h>		/* printf */

#include "calculator.h"	/* header file */

static void TestBoolResult(int result);
static void TestCalculatePlusMinus(void);
static void TestCalculateMulti(void);
static void TestCalculateDiv(void);
static void TestCalculateBrackets(void);

int main(void)
{
	TestCalculatePlusMinus();
	TestCalculateMulti();
	TestCalculateDiv();
	TestCalculateBrackets();
	
	return 0;
}

static void TestCalculatePlusMinus(void)
{
	status_t test_status1 = SUCCESS;
	status_t test_status2 = SUCCESS;
	status_t test_status3 = SUCCESS;
	status_t test_status4 = SUCCESS;
	status_t test_status5 = SUCCESS;
	double result1 = 0;
	double result2 = 0;
	double result3 = 0;
	double result4 = 0;
	double result5 = 0;
	
	printf("---Addition + Substruction---\n");
	
	test_status1 = Calculate("3 + 5", &result1);
	printf("Test 1: ");
	TestBoolResult(SUCCESS == test_status1 && 8 == result1);

	test_status2 = Calculate("1 + 2 + 3", &result2);
	printf("Test 2: ");
	TestBoolResult(SUCCESS == test_status2 && 6 == result2);

	test_status3 = Calculate("10 + 5 + -2", &result3);
	printf("Test 3: ");
	TestBoolResult(SUCCESS == test_status3 && 13 == result3);

	test_status4 = Calculate("10 - -6", &result4);
	printf("Test 4: ");
	TestBoolResult(SUCCESS == test_status4 && 16 == result4);
	
	test_status5 = Calculate("10 +5", &result5);
	printf("Test 5: ");
	TestBoolResult(SUCCESS == test_status5 && 15 == result5);
}

static void TestCalculateMulti(void)
{
	status_t test_status1 = SUCCESS;
	status_t test_status2 = SUCCESS;
	status_t test_status3 = SUCCESS;
	status_t test_status4 = SUCCESS;
	status_t test_status5 = SUCCESS;
	double result1 = 0;
	double result2 = 0;
	double result3 = 0;
	double result4 = 0;
	double result5 = 0;
	
	printf("-------Multiplication-------\n");
	
	test_status1 = Calculate("3 * 5", &result1);
	printf("Test 1: ");
	TestBoolResult(SUCCESS == test_status1 && 15 == result1);

	test_status2 = Calculate("10 + 2 * 3", &result2);
	printf("Test 2: ");
	TestBoolResult(SUCCESS == test_status2 && 16 == result2);

	test_status3 = Calculate("10 * 5 + -2", &result3);
	printf("Test 3: ");
	TestBoolResult(SUCCESS == test_status3 && 48 == result3);

	test_status4 = Calculate("10 * 6 + 5", &result4);
	printf("Test 4: ");
	TestBoolResult(SUCCESS == test_status4 && 65 == result4);
	
	test_status5 = Calculate("10 * 5 * 2 + 1", &result5);
	printf("Test 5: ");
	TestBoolResult(SUCCESS == test_status5 && 101 == result5);



}

static void TestCalculateDiv(void)
{
	status_t test_status1 = SUCCESS;
	status_t test_status2 = SUCCESS;
	status_t test_status3 = SUCCESS;
	status_t test_status4 = SUCCESS;
	status_t test_status5 = SUCCESS;
	status_t test_status6 = SUCCESS;
	double result1 = 0;
	double result2 = 0;
	double result3 = 0;
	double result4 = 0;
	double result5 = 0;
	double result6 = 0;
	
	printf("-------Division-------\n");
	
	test_status1 = Calculate("10 / 2", &result1);
	printf("Test 1: ");
	TestBoolResult(SUCCESS == test_status1 && 5 == result1);

	test_status2 = Calculate("10 + 10 / 2", &result2);
	printf("Test 2: ");
	TestBoolResult(SUCCESS == test_status2 && 15 == result2);
	
	test_status3 = Calculate("10 / 5 + -2", &result3);
	printf("Test 3: ");
	TestBoolResult(SUCCESS == test_status3 && 0 == result3);

	test_status4 = Calculate("10 * 6 / 2", &result4);
	printf("Test 4: ");
	TestBoolResult(SUCCESS == test_status4 && 30 == result4);
	
	test_status5 = Calculate("10 / 5 * 2", &result5);
	printf("Test 5: ");
	TestBoolResult(SUCCESS == test_status5 && 4 == result5);
	
	test_status6 = Calculate("1 + 10 / 0 * 2 + 9", &result6);
	printf("Test 6: ");
	TestBoolResult(MATH_FAULT == test_status6);

}


static void TestCalculateBrackets(void)
{
	status_t test_status1 = SUCCESS;
	status_t test_status2 = SUCCESS;
	status_t test_status3 = SUCCESS;
	status_t test_status4 = SUCCESS;
	status_t test_status5 = SUCCESS;
	status_t test_status6 = SUCCESS;
	double result1 = 0;
	double result2 = 0;
	double result3 = 0;
	double result4 = 0;
	double result5 = 0;
	double result6 = 0;
	
	printf("-------Brackets-------\n");
	
	test_status1 = Calculate("(10 / 2)", &result1);
	printf("Test 1: ");
	TestBoolResult(SUCCESS == test_status1 && 5 == result1);

	test_status2 = Calculate("(10 + 10) / 2", &result2);
	printf("Test 2: ");
	TestBoolResult(SUCCESS == test_status2 && 10 == result2);

	test_status3 = Calculate("10 / (5 + -2)", &result3);
	printf("Test 3: ");
	TestBoolResult(SUCCESS == test_status3 && ((double)(10)/3) == result3);
	
	test_status4 = Calculate("(10) *6 / 2", &result4);
	printf("Test 4: ");
	TestBoolResult(SUCCESS == test_status4 && 30 == result4);
	
	test_status5 = Calculate("(10 / (5 * 2)", &result5);
	printf("Test 5: ");
	TestBoolResult(SYNTAX_FAULT == test_status5);
	
	test_status6 = Calculate("(1 + (30 / 3)) * 2 +9", &result6);
	printf("Test 6: ");
	TestBoolResult(SUCCESS == test_status6 && 31 == result6);

}

/**************************test utility functions************************/
static void TestBoolResult(int result)
{
	if (result)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}
