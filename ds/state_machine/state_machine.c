/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	State machine			*/
/*   Date:		22/01/23				*/
/*	 Reviewer:	Sveta					*/
/*										*/
/****************************************/

#include <assert.h>			/* assert */

#include "state_machine.h"	/* header file */

#define MAX_INPUTS 2

typedef enum state
{
	INITIAL = 0,
	REJECT,
	NOT_ACCEPTED,
	ACCEPTED
} state_t;

enum 
{
	VALID = 0,
	NOT_VALID
};

typedef struct transition
{
	const char in;
	const state_t out;
} transition_t;

typedef struct fsm
{
	const state_t state;
	state_t (*Action)(char);
	const transition_t table[MAX_INPUTS];
} fsm_t;

static state_t Initial(char c);
static state_t Reject(char c);
static state_t NotAccepted(char c);
static state_t Accepted(char c);

const fsm_t fsm[] = 
{
	{INITIAL,		&Initial,		{{'1', REJECT},		{'0', NOT_ACCEPTED}}},
	{REJECT,		&Reject, 		{{'1', REJECT},			{'0', REJECT}}},
	{NOT_ACCEPTED,	&NotAccepted, 	{{'1', NOT_ACCEPTED},	{'0', ACCEPTED}}},
	{ACCEPTED,		&Accepted,		{{'1', NOT_ACCEPTED},	{'0', ACCEPTED}}}
};


int FSMIsValidInput(const char *str)
{
	char *curr_input = NULL;
	state_t curr_state = INITIAL;
	
	assert(NULL != str);
	curr_input = (char *)str;
		
	while ('\0' != *curr_input)
	{
		assert(('0' == *curr_input) || ('1' == *curr_input));
		
		curr_state = fsm[curr_state].Action(*curr_input);
		++curr_input;
	}
	
	return ((ACCEPTED == curr_state) ? VALID : NOT_VALID);
}

static state_t Initial(char c)
{
	assert(('0' == c) || ('1' == c));
	
	return (('0' == c) ? NOT_ACCEPTED : REJECT);
}

static state_t NotAccepted(char c)
{
	assert(('0' == c) || ('1' == c));
	
	return (('0' == c) ? ACCEPTED : NOT_ACCEPTED);
}

static state_t Accepted(char c)
{
	assert(('0' == c) || ('1' == c));
	
	return (('0' == c) ? ACCEPTED : NOT_ACCEPTED);
}

static state_t Reject(char c)
{	
	(void)c;
	
	return REJECT;
}


