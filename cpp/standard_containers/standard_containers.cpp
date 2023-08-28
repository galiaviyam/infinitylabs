/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Standard Containers     */
/*   Date:      08/04/23                */
/*   Reviewer:  Noy                     */
/*                                      */
/****************************************/


#include <iostream>     // cout
#include <list>         // push_back
#include <string>       // string data type
#include <algorithm>    // find

#include "standard_containers.hpp" // standard_containers header

namespace ilrd
{

class TextLine;

bool operator==(const TextLine& one, const TextLine& other);
std::ostream& operator<<(std::ostream& os, const TextLine& textLine);

//----------------------------------- Class ---------------------------------

class TextLine
{
public:
	TextLine(std::string data = "", size_t count = 1);
	
	TextLine& operator=(const TextLine& other);
    
	std::string Cstr() const;
	size_t GetCounter() const;
	void IncCounter();
	static void PrintText(std::list<TextLine> text);
private:
	std::string m_data;
	size_t m_count;
};

//------------------------- Methods and Constructors ------------------------

TextLine::TextLine(std::string data, size_t count): m_data(data), m_count(count) {}

std::string TextLine::Cstr() const
{
	return m_data;
}

TextLine& TextLine::operator=(const TextLine& other)
{
	m_data = other.Cstr();
	return *this;
}

size_t TextLine::GetCounter() const
{
	return m_count;
}

void TextLine::IncCounter()
{
	++m_count;
}

//--------------------------------- Operators -------------------------------

bool operator==(const TextLine& one, const TextLine& other)
{
	return (one.Cstr() == other.Cstr());
}

std::ostream& operator<<(std::ostream& os, const TextLine& textLine)
{
	size_t count = textLine.GetCounter();
	if (1 < count)
	{
		os << count << " x ";
	}
	
	return os << textLine.Cstr();
}

//----------------------------------- Histo ---------------------------------

void Histo(void)
{
	std::cout << "Please enter lines of text" << std::endl;
	std::cout << "(Enter \".\" to exit)" << std::endl;
	
	std::list<TextLine> text;
	const std::string exit_mark = ".";
	
	std::string input = "";
	std::getline(std::cin, input);
	std::list<TextLine>::iterator iter;
	
	while(exit_mark != input)
	{
		iter = std::find(text.begin(), text.end(), input);
		if(text.end() == iter)
		{
			text.push_back(input);
		}
		else
		{
			iter->IncCounter();
		}
		
		std::getline(std::cin, input);
	}
	
	std::cout << std::endl;
	TextLine::PrintText(text);
}
void TextLine::PrintText(std::list<TextLine> text)
{
	std::cout << "------- Output -------" << std::endl;
	while (!text.empty())
	{
		std::cout << text.front() << std::endl;
		text.pop_front();
	}
	std::cout << std::endl;
}
}	// namespace ilrd
