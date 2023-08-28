/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Factory Singleton       */
/*   Date:      04/06/23                */
/*   Reviewer:  Ariel                   */
/*                                      */
/****************************************/

#ifndef ILRD_RD136_7_FACTORY_SINGLETON_HPP
#define ILRD_RD136_7_FACTORY_SINGLETON_HPP

#include <mutex>
#include <unordered_map>    
#include <functional>
#include <stdexcept>    
#include <memory>

#include "handleton.hpp"

namespace ilrd
{
template <typename BASE, typename KEY, typename... ARGS>
class FactorySingleton
{
public:
    FactorySingleton(const FactorySingleton&) = delete;
    FactorySingleton& operator=(const FactorySingleton&) = delete;
    void Add(KEY key, std::function<BASE *(ARGS...)> creator);
    BASE *Create(KEY key, ARGS... args);
    void Remove(KEY key);
    static FactorySingleton<BASE, KEY, ARGS...> *GetInstance();

private:
    FactorySingleton() = default;
    std::unordered_map<KEY, std::function<BASE *(ARGS...)>> m_map;

    friend Singleton<FactorySingleton<BASE, KEY, ARGS...>>;
    friend Handleton<FactorySingleton<BASE, KEY, ARGS...>>;

    static std::shared_ptr<FactorySingleton> m_instance;
};

template <typename BASE, typename KEY, typename... ARGS>
void FactorySingleton<BASE, KEY,ARGS...>::
                        Add(KEY key, std::function<BASE *(ARGS...)> creator)
{
    m_map.emplace(key, creator);
}

template <typename BASE, typename KEY, typename... ARGS>
BASE *FactorySingleton<BASE, KEY,ARGS...>::Create(KEY key, ARGS... args)
{
    try
    {
        return m_map.at(key)(args...);
    }
    catch(const std::out_of_range& e)
    {
        throw std::invalid_argument("Key is not in the map");
    }
}

template <typename BASE, typename KEY, typename... ARGS>
FactorySingleton<BASE, KEY, ARGS...> *FactorySingleton<BASE, KEY, ARGS...>::GetInstance()
{
    static std::shared_ptr<FactorySingleton<BASE, KEY, ARGS...>> m_instance(new FactorySingleton<BASE, KEY , ARGS...>);

    return m_instance.get();
}

template <typename BASE, typename KEY, typename... ARGS>
void FactorySingleton<BASE, KEY,ARGS...>::Remove(KEY key)
{
    m_map.erase(key);
}

} //namespace ilrd

#endif /* ILRD_RD136_7_FACTORY_SINGLETON_HPP */ 
