// // Creation:  

//  String s0; // Creates a string that  points to "ABC"

//  String s1("1234"); 

//  String s2(s1);  

// // operator[]: (reuse the implementation)  

// s1[0] = 'r'; 
// s2[0] = s1[1];  

// // assignment:  

//  s1 = "abc"; 
//  s2 = s1; 
//  s1 = 'A'; // Will change all the characters in s1 to 'A' (in this case to "AAA")  

// s0 = s1 = s2; // Not allowed!  

// // Implement a function that will always return the number of String objects alive: 

// Use example:

#include <cstddef>
#include <cstring>
#include <iostream>

class String
{
public:
    String(const char *str = "ABC");
    String(const String& str);
    ~String();
    
    const String& operator=(const String& str);
    const String& operator=(const char ch);

    char& operator[](std::size_t indx);
    
	const char *Cstr() const;

    static size_t GetInstances();

private:
    static char *DupStr(const char *str);
    static char *ChrStr(const char *str, const char ch);
    
    char *m_str;
    static size_t m_count;
};

size_t String::m_count = 0;

int main()
{  
    String s1("1234");  
    s1 = '@'; // will change s1 to "@@@@"   
    String *s2 = new String;            
    std::cout<< s2->GetInstances(); // will print 2     
    delete s2;  
    std::cout<< String::GetInstances(); // will print 1
// s0 = s1 = s2; // Not allowed!  
    return 0;
}

String::String(const char *str) : m_str(DupStr(str))
{
    ++m_count;
}

String::String(const String& str) : m_str(DupStr(str.Cstr()))
{
    ++m_count;
}

String::~String()
{
    --m_count;
    delete[] m_str;
    m_str = 0;
}

const String& String::operator=(const String& str)
{
    char *new_str = DupStr(str.m_str);
    delete[] m_str;
    m_str = new_str;

    return *this;
}

const String& String::operator=(const char ch)
{
    char *new_str = ChrStr(m_str, ch);
    delete[] m_str;
    m_str = new_str;

    return *this;
}

char& String::operator[](std::size_t index)
{
    *this = m_str;
    return m_str[index];
}

char *String::DupStr(const char *str)
{
    std::size_t len = std::strlen(str) + 1;
    char *new_str = new char[len];
    std::memcpy(new_str, str, len);
    
    return new_str;
}

char *String::ChrStr(const char *str, const char ch)
{
    std::size_t len = std::strlen(str) + 1;
    char *new_str = new char[len];

    for (size_t i = 0; i < len; ++i)
    {
        new_str[i] = ch;
    }    
    return new_str;
}

size_t String::GetInstances()
{
    return m_count;
}

const char *String::Cstr() const
{
    return (m_str);
}
