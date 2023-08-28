/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Calculator              */
/*   Date:      23/01/23                */
/*   Reviewer:  Or                      */
/*                                      */
/****************************************/

#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__


/***************************** Description **********************************
		Calculator is a program that calculates mathematical expressions.
		It can perform basic operations such as addition, subtraction, 
		multiplication, and division.
		
		This calculator is based on a finite state machine (FSM) to process
		mathematical expressions passed as a string.
		
		The valid characters to use in the string are:
		- '0' - '9' - digits of the numbers in the expression, in decimal.
		- '+' - addition
		- '-' - subtraction
		- '*' - multiplication
		- '/' - division
		- '(' - open paranthesis
		- ')' - close paranthesis
		- ' ' (space)
		
****************************************************************************/

typedef enum status
{
    SYS_FAULT = -1,
    SUCCESS = 0,
    MATH_FAULT = 1,
    SYNTAX_FAULT = 2
}status_t;

/*-----------------------------------------------------------------------------
Description: 
	The Calculate function calculates a given math expression, with the 
	arithmetic operations: addition, substruction, multiplication, and division,
	as well as the use of brackets.
	
Parameters:
	string- The mathematic expression to calculate.
	result- A pointer to a variable for the calculator to store the result in.
	
Return Value:
	SUCCESS- If the calculation was succesful.
	SYS_FAULT- If the function failed due to a system fault.
	MATH_FAULT- If the expression contains invalid math operation (aka division 
				by 0).
	SYNTAX_FAULT- If the expression contains undefined characters.
	
Complexity: 
	time: O(1)  / space: O(1) 
-----------------------------------------------------------------------------*/
status_t Calculate(const char *string, double *result);

#endif /* __CALCULATOR_H__ */


