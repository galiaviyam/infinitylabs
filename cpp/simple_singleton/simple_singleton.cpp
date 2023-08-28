/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Simple Singleton        */
/*   Date:      04/06/23                */
/*   Reviewer:                      */
/*                                      */
/****************************************/

#include "simple_singleton.hpp"

namespace ilrd
{
SimpleSingleton *SimpleSingleton::m_instance = 0;

SimpleSingleton *SimpleSingleton::GetInstance()
{
    if (0 == m_instance)
    {
        m_instance = new SimpleSingleton;
    }

    return m_instance;
}





















// void AtExitSimple()
{}
} //namespace ilrd

#endif /* ILRD_RD136_7_SIMPLE_SINGLETON_HPP */ 
