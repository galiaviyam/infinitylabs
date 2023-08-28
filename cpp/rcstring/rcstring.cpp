/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   RCstring                */
/*   Date:      31/03/23                */
/*   Reviewer:  Itay                    */
/*                                      */
/****************************************/

#include <cstring>		// strlen
#include <iostream>		// ostream
#include <cstddef>		// offsetof
#include <cassert>		// assert

#include "rcstring.hpp"	// header file

//typedef struct RCString::SharedString::SharedString shared_string_t;

namespace ilrd
{
RCString::RCString(const char *str_): m_sharedStr(AllocSharedStr(str_)) {}

RCString::RCString(const RCString& src): m_sharedStr(src.m_sharedStr)
{
	++m_sharedStr->m_counter;
}

RCString& RCString::operator=(const RCString& other)
{
	ForSelfAssignment(other);
	DeleteCopy();
	m_sharedStr = other.m_sharedStr;
	
	return *this;
}

RCString::~RCString()
{
	DeleteCopy();
}

//RCString& RCString::operator=(const char *other)
//{
//	SharedString *alloc = AllocSharedStr(other);
//	
//	DeleteCopy();
//	
//	m_sharedStr = alloc;
//	
//	return *this;
//}

const char& RCString::operator[](std::size_t index) const
{
	return (m_sharedStr->m_str[index]);
}

char &RCString::operator[](std::size_t index)
{
	*this = m_sharedStr->m_str;
	
	return (m_sharedStr->m_str[index]);
}

std::size_t RCString::Length() const
{
	return (std::strlen(m_sharedStr->m_str));
}

const char *RCString::Cstr() const
{
	return (m_sharedStr->m_str);
}

RCString::SharedString::SharedString(const char *str_): m_counter(1)
{
	std::memcpy(m_str, str_, std::strlen(str_) + 1);
}

RCString::SharedString::SharedString(const SharedString& src)
{
	std::memcpy(m_str, src.m_str, std::strlen(src.m_str) + 1);
}

RCString::SharedString& RCString::SharedString::
			operator=(const SharedString& other)
{
	static_cast<void>(other);
	
	return *this;
}

RCString::SharedString::~SharedString() {} // empty on-purpose

bool operator==(const RCString& one, const RCString& other)
{
	return (!std::strcmp(one.Cstr(), other.Cstr()));
}

bool operator>(const RCString& one, const RCString& other)
{
	return (0 < std::strcmp(one.Cstr(), other.Cstr()));
}

bool operator<(const RCString& one, const RCString& other)
{
	return !((one > other) || (one == other));
}

std::ostream& operator<<(std::ostream& os, const RCString& other)
{
	return (os << other.Cstr());
}

RCString::SharedString *RCString::AllocSharedStr(const char *str)
{
	size_t offset = offsetof(SharedString, m_str);
	size_t struct_size = offset + std::strlen(str) + 1;
	void *mem = operator new (struct_size);
	
	SharedString *sharedStr = new(mem) SharedString(str);
	
	return sharedStr;
}

void RCString::DeleteCopy()
{
	if (1 == m_sharedStr->m_counter)
	{
		operator delete(m_sharedStr);
		m_sharedStr = 0;
	}
	else
	{
		--m_sharedStr->m_counter;
	}
}

void RCString::ForSelfAssignment(const RCString& other)
{
	++other.m_sharedStr->m_counter;
}

} // namespace ilrd
