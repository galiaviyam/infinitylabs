/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Priority Queue          */
/*   Date:      22/05/23                */
/*                                      */
/****************************************/

#ifndef ILRD_RD136_7_PRIORITY_QUEUE_HPP
#define ILRD_RD136_7_PRIORITY_QUEUE_HPP

#include <queue>
#include <vector>
#include <functional>

namespace ilrd
{

template <class T,
class Container = std::vector<T>,
class Compare = std::less<typename Container::value_type>>
class PriorityQueue : private std::priority_queue<T, Container, Compare>
{
    typedef typename std::priority_queue<T, Container, Compare> pq_t;
public: 
    typedef typename pq_t::value_type value_type;
    typedef typename pq_t::reference reference;

    using pq_t::push;
    using pq_t::pop;
    using pq_t::empty;
    const value_type& front() const;
    
};

template <class T, class Container, class Compare>
inline const typename PriorityQueue<T, Container, Compare>::value_type& 
PriorityQueue<T, Container, Compare>::front() const
{
    return this->top();
}

} // namespace ilrd

#endif //ILRD_RD136_7_PRIORITY_QUEUE_HPP
