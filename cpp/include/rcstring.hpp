/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   RCstring                */
/*   Date:      31/03/23                */
/*   Reviewer:  Itay                    */
/*                                      */
/****************************************/

#ifndef ILRD_RD136_7_RCSTRING_HPP
#define ILRD_RD136_7_RCSTRING_HPP

#include <iostream> // ostream

namespace ilrd
{

class RCString
{
public:
    RCString(const char *str_ = "");
    RCString(const RCString& src);
    RCString& operator=(const RCString& other);
    ~RCString();
    
//    RCString& operator=(const char *other);
    const char& operator[](std::size_t index) const;
    char &operator[](std::size_t index);
    std::size_t Length() const;
    const char *Cstr() const;
    
private:
	struct SharedString
	{
		SharedString(const char *str_ = "");
		SharedString(const SharedString& src);
    	SharedString& operator=(const SharedString& other);
		~SharedString();
		
		std::size_t m_counter;
		char m_str[1];
	};
	
	static SharedString *AllocSharedStr(const char *str);
	static void ForSelfAssignment(const RCString& other);
	void DeleteCopy();

	struct SharedString *m_sharedStr;
};

bool operator==(const RCString& one, const RCString& other);
bool operator>(const RCString& one, const RCString& other);
bool operator<(const RCString& one, const RCString& other);
std::ostream& operator<<(std::ostream& os, const RCString& other);

} //namespace ilrd

#endif    // ILRD_RD136_7_RCSTRING_HPP


