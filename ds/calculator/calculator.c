/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Calculator              */
/*   Date:      23/01/23                */
/*   Reviewer:  Or                      */
/*                                      */
/****************************************/

#include <assert.h>		/* assert */
#include <stdlib.h>		/*strtod*/
#include <string.h>		/* strlen */

#include "stack.h"		/*all functions in use*/
#include "calculator.h"	/* header file */

#define STACK_CAPACITY (80)
#define INPUTS_TYPES (4)
#define NUM_OF_OPERS (8)
#define FIRST_OPER_ASCII (40)
#define ASCII_SIZE (256)

typedef struct calc
{
	stack_t *stack_num;
	stack_t *stack_op;
	char *expression;
} calc_t;

typedef enum state
{
	WAIT_FOR_NUM = 0,
	WAIT_FOR_OPER,
	RESULT,
	ERROR,
	NUM_OF_STATES
} state_t;

typedef enum input_type 
{ 
	NUM = 0, 
	OPERATION_PLUS,
	OPERATION_MINUS,
	OPERATION_MULTI,
	OPERATION_DIV,
	BRACKET_LEFT,
	BRACKET_RIGHT, 
	INVALID_INPUT, 
	END_STR,
	SPACE,
	NUM_OF_INPUT_TYPES
} input_type_t;

typedef enum precedence 
{ 
	NO_PRECEDENCE = -1,
	PLUS_MINUS = 0, 
	MULTI_DIV,
	BRACKET
} precedence_t;

typedef enum sign_index 
{ 
	BRAC_LEFT = 0,
	BRAC_RIGHT = 1,
	MULTI = 2,
	PLUS = 3, 
	MINUS = 5,
	DIV = 7 
} sign_index_t;

typedef struct transition
{
	const input_type_t input;
	status_t (*Action)(calc_t *calc, double *num);
	const state_t dest_state;
} transition_t;

typedef struct oper_and_precedence
{
	const precedence_t precedence;
	char operation;
	double (*oper_func)(const double num1, const double num2);
} oper_and_precedence_t;

/*----------------------transition functions-----------------------*/
static status_t SkipSpaces(calc_t *calc, double *num);
static status_t PushNum(calc_t *calc, double *num);
static status_t PlusFunc(calc_t *calc, double *num);
static status_t MinusFunc(calc_t *calc, double *num);
static status_t MultiFunc(calc_t *calc, double *num);
static status_t DivFunc(calc_t *calc, double *num);
static status_t ErrorFunc(calc_t *calc, double *num);
static status_t CalcResult(calc_t *calc, double *num);
static status_t OpenBracket(calc_t *calc, double *num);
static status_t CloseBracket(calc_t *calc,double *num);
/*----------------------simple calc functions-----------------------*/
static double SimplePlus(const double num1, const double num2);
static double SimpleMinus(const double num1, const double num2);
static double SimpleMulti(const double num1, const double num2);
static double SimpleDiv(const double num1, const double num2);
static double DoNothing(const double num1, const double num2);
/*---------------------initialization functions--------------------*/
static void InitInputTypeLut(void);
static status_t InitCalcStruct(calc_t *calc, const char *expression);
/*----------------------operations functions-----------------------*/
static void CalcOneOper(calc_t *calc);
static status_t PerformPrecOper(calc_t *calc, char *operation);
/*-------------------------get functions--------------------------*/
static input_type_t GetInputType(char *str);
static int GetPrecedence(char ch);
static status_t CheckMathFault(calc_t *calc, double *num);
static int CheckParenthesis(const char *str);

/*----------------transition table initialization-----------------*/
static const transition_t FSM[NUM_OF_INPUT_TYPES][NUM_OF_STATES] = 
{
	{{NUM, &PushNum ,WAIT_FOR_OPER}, 
	{NUM, &ErrorFunc ,ERROR}, 
	{NUM, &CalcResult, RESULT}, 
	{NUM, &ErrorFunc ,ERROR}},
	 
	{{OPERATION_PLUS, &PushNum, WAIT_FOR_OPER},
	{OPERATION_PLUS, &PlusFunc, WAIT_FOR_NUM}, 
	{OPERATION_PLUS, &CalcResult, RESULT}, 
	{OPERATION_PLUS, &ErrorFunc ,ERROR}},
	
	{{OPERATION_MINUS, &PushNum, WAIT_FOR_OPER}, 
	{OPERATION_MINUS, &MinusFunc, WAIT_FOR_NUM}, 
	{OPERATION_MINUS, &CalcResult, RESULT}, 
	{OPERATION_MINUS, &ErrorFunc ,ERROR}},
	
	{{OPERATION_MULTI,  &ErrorFunc ,ERROR}, 
	{OPERATION_MULTI, &MultiFunc, WAIT_FOR_NUM}, 
	{OPERATION_MULTI, &CalcResult, RESULT}, 
	{OPERATION_MULTI, &ErrorFunc ,ERROR}},
	
	{{OPERATION_DIV, &ErrorFunc ,ERROR}, 
	{OPERATION_DIV, &DivFunc, WAIT_FOR_NUM}, 
	{OPERATION_DIV, &CalcResult, RESULT}, 
	{OPERATION_DIV, &ErrorFunc ,ERROR}},
	
	{{BRACKET_LEFT, &OpenBracket, WAIT_FOR_NUM},
	{BRACKET_LEFT, &ErrorFunc ,ERROR}, 
	{BRACKET_LEFT, &CalcResult, RESULT}, 
	{BRACKET_LEFT, &ErrorFunc ,ERROR}},
	
	{{BRACKET_RIGHT, &ErrorFunc ,ERROR}, 
	{BRACKET_RIGHT, &CloseBracket, WAIT_FOR_OPER}, 
	{BRACKET_RIGHT, &CalcResult, RESULT}, 
	{BRACKET_RIGHT, &ErrorFunc ,ERROR}},
	
	{{INVALID_INPUT, &ErrorFunc ,ERROR}, 
	{INVALID_INPUT, &ErrorFunc ,ERROR}, 
	{INVALID_INPUT, &ErrorFunc ,ERROR}, 
	{INVALID_INPUT, &ErrorFunc ,ERROR}},
	
	{{END_STR, &ErrorFunc ,ERROR}, 
	{END_STR, &CalcResult ,RESULT}, 
	{END_STR, &CalcResult ,RESULT}, 
	{END_STR, &ErrorFunc ,ERROR}},
	
	{{SPACE, &SkipSpaces ,WAIT_FOR_NUM}, 
	{SPACE, &SkipSpaces ,WAIT_FOR_OPER}, 
	{SPACE, &CalcResult ,RESULT}, 
	{SPACE, &ErrorFunc ,ERROR}}
};

static const oper_and_precedence_t ASCII_oper[NUM_OF_OPERS] = 
{
	{NO_PRECEDENCE,	'(',	&DoNothing},
	{BRACKET,		')',	&DoNothing},
	{MULTI_DIV,		'*',	&SimpleMulti},
	{PLUS_MINUS,	'+',	&SimplePlus},
	{NO_PRECEDENCE,	'\0',	NULL},
	{PLUS_MINUS,	'-',	&SimpleMinus},
	{NO_PRECEDENCE,	'\0',	NULL},
	{MULTI_DIV,		'/',	&SimpleDiv}
};

static input_type_t type_lut[ASCII_SIZE] = {0};

/*---------------------------Function Definition-----------------------------*/
status_t Calculate(const char *string, double *result)
{
	status_t ret_status = SUCCESS;
	input_type_t input_index = INVALID_INPUT;
	calc_t calc = {0};
	state_t state = WAIT_FOR_NUM;
	
	assert(string);
	assert(result);
	
	ret_status = CheckParenthesis(string);
	if (SUCCESS != ret_status)
	{
		return ret_status;
	}
	
	ret_status = InitCalcStruct(&calc, string);
	
	InitInputTypeLut();
	
	while ((RESULT != state) && SUCCESS == ret_status)
	{
		input_index = GetInputType(calc.expression);
		ret_status = FSM[input_index][state].Action(&calc, result);
		state = FSM[input_index][state].dest_state;
	}
	
	StackDestroy(calc.stack_op);
	StackDestroy(calc.stack_num);
	
	return ret_status;
}

/*-----------------------------Service Functions-----------------------------*/
static status_t InitCalcStruct(calc_t *calc, const char *expression)
{
	calc->stack_op = StackCreate(STACK_CAPACITY);
	if (NULL == calc->stack_op)
	{
		return SYS_FAULT;
	}
	
	calc->stack_num = StackCreate(STACK_CAPACITY);
	if (NULL == calc->stack_num)
	{
		StackDestroy(calc->stack_op);
		return SYS_FAULT;
	}
	
	calc->expression = (char *)expression;
	
	return SUCCESS;
}

static input_type_t GetInputType(char *str)
{
	assert(NULL != str);
	
	return (type_lut[(int)*str]);	
}

static status_t SkipSpaces(calc_t *calc, double *num)
{
	assert(NULL != calc);
	
	++calc->expression;
	(void)num;
	
	return SUCCESS;
}

static void InitInputTypeLut(void)										
{
	int i = 0;
	
	assert(NULL != type_lut);
	
	for (i = 0; ASCII_SIZE > i; ++i)
	{
		type_lut[i] = INVALID_INPUT;
	}
	
	for (i = '0';'9' >= i; ++i)
	{
		type_lut[i] = NUM;
	}
	
	type_lut['+'] = OPERATION_PLUS;
	type_lut['-'] = OPERATION_MINUS;
	
	type_lut['*'] = OPERATION_MULTI;
	type_lut['/'] = OPERATION_DIV;
	
	type_lut['('] = BRACKET_LEFT;
	type_lut[')'] = BRACKET_RIGHT;
	
	type_lut[' '] = SPACE;
	type_lut['\0'] = END_STR;
}

static status_t PushNum(calc_t *calc, double *num)
{
	status_t ret_status = SUCCESS;
	void *num_to_push = NULL;
	double res = 0;
	
	assert(NULL != calc);
	assert(NULL != calc->stack_num);
	
	(void)num;
	
	res = strtod(calc->expression, &calc->expression);
	
	ret_status = CheckMathFault(calc, &res);
	if (MATH_FAULT != ret_status)
	{
		memcpy((double **)&num_to_push, &res, sizeof(double));
		StackPush(calc->stack_num, num_to_push);
	}
	
	return ret_status;
}

static status_t PerformPrecOper(calc_t *calc, char *operation)
{
	status_t ret_status = SUCCESS;

	assert(NULL != calc->stack_op);
	assert(NULL != calc->stack_num);
	assert(NULL != operation);
	
	while (!StackIsEmpty(calc->stack_op) && (GetPrecedence(*operation) 
				<= GetPrecedence(*(char *)StackPeek(calc->stack_op))))
	{
		CalcOneOper(calc);
	}
	
	StackPush(calc->stack_op, operation);
	
	return ret_status;
}

static int GetPrecedence(char ch) 
{
	return (ASCII_oper[ch - FIRST_OPER_ASCII].precedence);  
}

static status_t PlusFunc(calc_t *calc, double *num)
{
	status_t ret_status = SUCCESS;
	
	assert(NULL != calc->stack_op);
	assert(NULL != calc->stack_num);
	
	(void)num;
	
	ret_status = PerformPrecOper(calc, &ASCII_oper[PLUS].operation);
	++calc->expression;
	
	return ret_status;
}

static status_t MinusFunc(calc_t *calc, double *num)
{
	status_t ret_status = SUCCESS;
	
	assert(NULL != calc->stack_op);
	assert(NULL != calc->stack_num);
	
	(void)num;
	
	ret_status = PerformPrecOper(calc, &ASCII_oper[MINUS].operation);
	
	++calc->expression;
	
	return ret_status;
}

static status_t MultiFunc(calc_t *calc, double *num)
{
	status_t ret_status = SUCCESS;
	
	assert(NULL != calc->stack_op);
	assert(NULL != calc->stack_num);
	
	(void)num;
	
	ret_status = PerformPrecOper(calc, &ASCII_oper[MULTI].operation);

	++calc->expression;
	
	return ret_status;
}

static status_t DivFunc(calc_t *calc, double *num)
{
	status_t ret_status = SUCCESS;
	
	assert(NULL != calc->stack_op);
	assert(NULL != calc->stack_num);
	
	(void)num;
	
	ret_status = PerformPrecOper(calc, &ASCII_oper[DIV].operation);

	++calc->expression;
	
	return ret_status;
}

static double SimplePlus(const double num1, const double num2)
{
	return (num1 + num2);
}

static double SimpleMinus(const double num1, const double num2)
{
	return (num1 - num2);
}

static double SimpleMulti(const double num1, const double num2)
{
	return (num1 * num2);
}

static double SimpleDiv(const double num1, const double num2)
{
	assert(0 != num2);
	
	return (num1 / num2);
}

static double DoNothing(const double num1, const double num2)
{
	(void)num1;
	(void)num2;
	
	return (0);
}

static status_t ErrorFunc(calc_t *calc, double *num)
{
	(void)calc;
	(void)num;

	++calc->expression;
	
	return SYNTAX_FAULT;
}

static status_t CalcResult(calc_t *calc, double *num)
{
	status_t ret_status = SYNTAX_FAULT;
	void *ptr_cast = NULL;
	
	assert(NULL != calc->stack_op);
	assert(NULL != calc->stack_num);
	assert(NULL != num);

	while (!StackIsEmpty(calc->stack_op))
	{
		CalcOneOper(calc);
	}
	
	if (!StackIsEmpty(calc->stack_num))
	{	
		ptr_cast = StackPop(calc->stack_num);

		memcpy(num, (double **)&ptr_cast, sizeof(double));
		ret_status = SUCCESS;
	}
	
	return ret_status;
}

static status_t OpenBracket(calc_t *calc, double *num)
{
	StackPush(calc->stack_op, &ASCII_oper[BRAC_LEFT].operation);
	
	(void)num;
	++calc->expression;
	
	return 0;
}

static status_t CloseBracket(calc_t *calc, double *num)
{
	status_t ret_status = SUCCESS;
	
	assert(NULL != calc->stack_op);
	assert(NULL != calc->stack_num);	
	(void)num;
	
	while ('(' != *(char *)StackPeek(calc->stack_op))
	{
		CalcOneOper(calc);
	}
	
	StackPop(calc->stack_op);

	++calc->expression;
	return ret_status;
}

static void CalcOneOper(calc_t *calc)
{
	char *top_oper = NULL;
	double top_num1 = 0.0;
	void *ptr_num1 = NULL;
	double top_num2 = 0.0;
	void *ptr_num2 = NULL;
	double res = 0.0;
	void *ptr_res = NULL;
	
	assert(NULL != calc->stack_op);
	assert(NULL != calc->stack_num);
	
	top_oper = (char *)StackPop(calc->stack_op);
	
	ptr_num2 = StackPop(calc->stack_num);
	memcpy(&top_num2, (double **)&ptr_num2, sizeof(double));
	
	ptr_num1 = StackPop(calc->stack_num);
	memcpy(&top_num1, (double **)&ptr_num1, sizeof(double));
	
	res = ASCII_oper[*top_oper - FIRST_OPER_ASCII].oper_func(top_num1, top_num2);
	
	memcpy((double **)&ptr_res, &res, sizeof(double));
	StackPush(calc->stack_num, ptr_res);
}

static status_t CheckMathFault(calc_t *calc, double *num)
{
	status_t status = SUCCESS;
	
	assert(NULL != calc->stack_op);
	assert(NULL != calc->stack_num);
	assert(NULL != num);
	
	if ((0.0 == *num) && (!StackIsEmpty(calc->stack_op)) && 
		('/' == *(char *)StackPeek(calc->stack_op)))
	{
		status = MATH_FAULT;
	}
	
	return status;
}

static int CheckParenthesis(const char *str)
{
    stack_t *stack = NULL;
	int status = SYNTAX_FAULT;
    char *runner = NULL;
    
    assert(NULL != str);
    runner = (char *)str;
    
    stack = StackCreate(strlen(str));
    if (NULL == stack)
    {
    	return SYS_FAULT;
    }
    
    while ('\0' != *(runner))
    {
        switch (*runner)
        {
            case '(':
            {
            	StackPush(stack, runner);
            	++runner;
                break;
            }
            case ')':
            {
              if (!StackIsEmpty(stack) && '(' == *(char *)StackPeek(stack))
              {
                  StackPop(stack);
              }
              else
              {
              	StackPush(stack, runner);
              }
                  ++runner;
                  break;
            }
            default:
            {
            	++runner;
            	break;
            }	
        }
    }
   
	if (StackIsEmpty(stack))
	{
		status = SUCCESS;
	}
	
    StackDestroy(stack);
    
    return (status);
}

