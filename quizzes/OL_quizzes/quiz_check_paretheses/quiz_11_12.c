#include <stdio.h> /*printf*/
#include <assert.h>/*assert*/
#include <string.h>/*strlen*/
#include "stack.h"/*stack*/

void CheckParenthesis(const char *str);

int main(void)
{
	
	CheckParenthesis("{}{}{}()");
	CheckParenthesis("{}{[]}{()}");
	CheckParenthesis("{}{}{([)]}");	
	CheckParenthesis("(a{a}cd)");
	
	return 0;
}

void CheckParenthesis(const char *str)
{
	char *runner = NULL;
	stack_t *stack = NULL;
	
	assert(NULL != str);
	
	runner = (char *)str;
	
	stack = StackCreate(strlen(str));
	
	while ('\0' != *runner)
	{
		switch (*runner)
		{
			case '{':
			case '(':
			case '[':
			{
				StackPush(stack, runner);
				++runner;
				break;
			}
			case ')':
            {
            	if ('(' == *(char *)StackPeek(stack))
            	{
            		StackPop(stack);
            	}
            	++runner;
            	break;
            }
            case '}':
            {
                if('{' == *(char *)StackPeek(stack))
                {
                    StackPop(stack);
                }
                ++runner;
                break;
            }
            case ']':
            {
                 if('[' == *(char *)StackPeek(stack))
                {
                    StackPop(stack);
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
    ((StackIsEmpty(stack))? (printf("balanced\n")) : (printf("unbalanced\n")));
}
