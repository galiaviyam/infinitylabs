#include <cstddef>	// size_t
#include <iostream> // ostream 
#include <cstring>
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

    len = ::strlen(str) + 1;
    new_str = new char[len];
    ::memcpy(new_str, str, len);
    
    return new_str;
}


String foo(String s_)
{
	String s2(s_);
	return s2;
}

int main(void)
{
	String str1 = "123";
	String str2;
	str2 = foo(str1);
}
