/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Factory                 */
/*   Date:      01/06/23                */
/*   Reviewer:  Itay                    */
/*                                      */
/****************************************/

#ifndef ILRD_RD136_7_FACTORY_HPP
#define ILRD_RD136_7_FACTORY_HPP

#include <unordered_map>
#include <functional>
#include <iostream>			//invalid_argument
#include <memory>			//unique_ptr

namespace ilrd
{

template <typename BASE, typename KEY, typename... ARGS>
class Factory
{
public:
    void Add(KEY key, std::function<BASE *(ARGS...)> creator);
    BASE *Create(KEY key, ARGS... args);

private:
    std::unordered_map<KEY, std::function<BASE *(ARGS...)>> m_map;
    
};

template <typename BASE, typename KEY, typename... ARGS>
void Factory<BASE, KEY,ARGS...>::
                        Add(KEY key, std::function<BASE *(ARGS...)> creator)
{
    m_map.emplace(key, creator);
}

template <typename BASE, typename KEY, typename... ARGS>
BASE *Factory<BASE, KEY,ARGS...>::Create(KEY key, ARGS... args)
{
    try
    {
        return m_map.at(key)(args...);
    }
    catch(const std::exception& e)
    {
        throw std::invalid_argument("Key is not in the map");
    }
}

} //namespace ilrd

#endif /* ILRD_RD136_7_FACTORY_HPP */ 
