/****************************************/
/*                                      */
/*   Developer: Gali Aviyam             */
/*   Project:   Scope Lock              */
/*   Date:      11/05/23                */
/*   Reviewer:  Yuval                   */
/*                                      */
/****************************************/

#ifndef ILRD_RD136_7_SCOPE_LOCK_HPP
#define ILRD_RD136_7_SCOPE_LOCK_HPP

#include <boost/noncopyable.hpp>
#include <iostream>

namespace ilrd
{
template <typename T> // T has to be lockable, has Lock() and Unlock() methods
class Scope_Lock : private boost::noncopyable
{
public:
	explicit Scope_Lock(T& lockable);
	~Scope_Lock();

private:
	T& m_lock;
};

/*--------------------------------- Methods ---------------------------------*/
template <typename T>
Scope_Lock<T>::Scope_Lock(T& lockable) : m_lock(lockable) 
{
    m_lock.lock();
    #ifndef NDEBUG
        std::cout << "Locking" << std::endl;
    #endif
}

template <typename T>
Scope_Lock<T>::~Scope_Lock()
{
    m_lock.unlock();
    #ifndef NDEBUG
        std::cout << "Unlocking" << std::endl;
    #endif
}
}//namespace ilrd

#endif //ILRD_RD136_7_SCOPE_LOCK_HPP
