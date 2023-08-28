/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Simple Singleton        */
/*   Date:      04/06/23                */
/*   Reviewer:                      */
/*                                      */
/****************************************/
#ifndef ILRD_RD136_7_SIMPLE_SINGLETON_HPP
#define ILRD_RD136_7_SIMPLE_SINGLETON_HPP

#include <atomic>    
#include <mutex>

namespace ilrd
{
/*--------------------------- Singleton - Phase I ---------------------------*/
class SimpleSingleton
{
public:
    SimpleSingleton(const SimpleSingleton&) = delete;
    SimpleSingleton& operator=(const SimpleSingleton&) = delete;

    static SimpleSingleton *GetInstance();

private:
    SimpleSingleton() = default;
    static SimpleSingleton *m_instance;
};

} //namespace ilrd

#endif /* ILRD_RD136_7_SIMPLE_SINGLETON_HPP */ 
