#include <cstddef>
#include <cstring>
#include <iostream>

class String
{
public:
    String(const char *str = "");
    String(const String& str);
    ~String();
    
    String& operator=(const String& str);
    char& operator[](std::size_t indx);
    
	const char *Cstr() const;

private:
    static char *AllocNewStr(const char *str);
    
    char *m_str;
};

std::ostream& operator<<(std::ostream& os_, const String& str_);

int main(void)
{
    String s1("one");
    String s2 = "two";
    String s3(s2);
    String s4;
    
    s4 = s2;
    s3[2] = 'k';
    s2 = s2;
    
    std::cout << "s1: " << s1 << '\n';
    std::cout << "s2: " << s2 << '\n';
    std::cout << "s3: " << s3 << '\n';
    std::cout << "s4: " << s4 << '\n';
    
    return 0;
}

String::String(const char *str) : m_str(AllocNewStr(str))
{
}

String::String(const String& str) : m_str(AllocNewStr(str.m_str))
{
}

String::~String()
{
    delete[] m_str;
    m_str = 0;
}

String& String::operator=(const String& str)
{
    char *new_str = AllocNewStr(str.m_str);
    delete[] m_str;
    m_str = new_str;

    return *this;
}

char& String::operator[](std::size_t index)
{
    *this = m_str;
    return m_str[index];
}

char *String::AllocNewStr(const char *str)
{
    std::size_t len = std::strlen(str) + 1;
    char *newStr = new char[len];
    std::memcpy(newStr, str, len);
    
    return newStr;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
    return (os << str.Cstr());
}

const char *String::Cstr() const
{
    return (m_str);
}
