/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Simple String           */
/*   Date:      23/03/23                */
/*   Reviewer:  Ariel K.                */
/*                                      */
/****************************************/

#ifndef ILRD_RD136_7_SIMPLE_STRING_HPP
#define ILRD_RD136_7_SIMPLE_STRING_HPP

#include <cstddef>	// size_t
#include <iostream> // ostream 

namespace ilrd
{
class String 
{
public:
	String(const char *str_ = ""); //non-explicit on purpose
	String(const String& src_);
	~String();
	String& operator=(const String& other_);

	size_t Length() const;
	const char *Cstr() const;

private:
    char *m_str;
};

bool operator==(const String& one_, const String& other_);
bool operator>(const String& one_, const String& other_);
bool operator<(const String& one_, const String& other_);
std::ostream& operator<<(std::ostream& os_, const String& str_);

}

#endif	// ILRD_RD136_7_SIMPLE_STRING_HPP
