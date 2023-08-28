/****************************************/
/*                                      */
/*   Developer: Gali Aviyam             */
/*   Project:   Scope Lock              */
/*   Date:      11/05/23                */
/*   Reviewer:  Yuval                   */
/*                                      */
/****************************************/

#include <iostream>  
#include <mutex>

#include "scope_lock.hpp"

using namespace ilrd;

int main(void)
{
	std::mutex mtx;

	Scope_Lock<std::mutex> lock(mtx);

	return 0;
}