/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	State machine			*/
/*   Date:		22/01/23				*/
/*	 Reviewer:	Sveta					*/
/*										*/
/****************************************/

#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

/*------------------------------------------------------------------------------
Description:
	The FSMIsValidInput function using an FSM to determine if a binary string 
	is accepted or not.
	accepted string has at least two digits, and starts and ends with '0'.
	Passing a string containing characters other then '0' or '1' will cause an
	undefined behivior.

Parameters: 
	str - the string input for determine.

Return value: 
	On success the function return 0, otherwise it returns 1.

Complexity:
	time: O(n) / space: O(1).
------------------------------------------------------------------------------*/
int FSMIsValidInput(const char *str);


#endif /* __STATE_MACHINE_H__ */
