/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Simple String           */
/*   Date:      23/03/23                */
/*   Reviewer:  Ariel K.                */
/*                                      */
/****************************************/

#include <cstring>				// strcpy  
#include <cassert>				// assert

#include "simple_string.hpp"	// header file


using namespace ilrd;
using std::ostream;

char *DuplicateStr(const char *str);

String::String(const char *str_): m_str(DuplicateStr(str_)) {}

String::String(const String& src_): m_str(DuplicateStr(src_.Cstr())) {}

String::~String()
{
    delete[] m_str;
    m_str = 0;
}

String& String::operator=(const String& other_)
{
    char *str = DuplicateStr(other_.m_str);
    delete[] m_str;
    m_str = str;

    return *this;
}

namespace ilrd
{
ostream& operator<<(ostream& os_, const String& str_)
{
    return (os_ << str_.Cstr());
}

bool operator==(const String& one_, const String& other_) 
{
    return (!::strcmp(one_.Cstr(), other_.Cstr()));
}

bool operator>(const String& one_, const String& other_)
{
    return (0 < ::strcmp(one_.Cstr(), other_.Cstr()));
}

bool operator<(const String& one_, const String& other_)
{
    return !((one_ > other_) || (one_ == other_));
}
}

size_t String::Length() const
{
    return (::strlen(m_str));
}

const char *String::Cstr() const
{
    return (m_str);
}

char *DuplicateStr(const char *str)
{
    char *new_str = NULL;
    size_t len = 0;

    assert(NULL != str);

    len = ::strlen(str) + 1;
    new_str = new char[len];
    ::memcpy(new_str, str, len);
    
    return new_str;
}


