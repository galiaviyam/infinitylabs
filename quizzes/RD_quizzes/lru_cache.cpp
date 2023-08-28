#include <iostream>			/* cout */
#include <list>				/* list */
#include <unordered_map>	/* unordered_map */
#include <iterator>			/* iterator, auto */

template <typename T>
class LRU
{
public:
	explicit LRU(std::size_t capacity): m_capacity(capacity){}
	void Put(int key, const T& value);
	const T& Get(int key) const;
	void Print() const;

private:
	typedef typename std::list<std::pair<int, T>>::iterator iter_t;
	std::list<std::pair<int, T>> m_queue;
	std::unordered_map<int, iter_t> m_cache; 
	std::size_t m_capacity;
};

template <typename T>
void LRU<T>::Put(int key, const T &value)
{
	if (m_cache.find(key) == m_cache.end())
	{
		if (m_queue.size() == m_capacity)
		{			
			m_cache.erase(m_queue.back().first);
			m_queue.pop_back();
		}
	}
	else
	{
		m_queue.erase(m_cache[key]);
	}

	m_queue.push_front(std::make_pair(key, value));
	m_cache[key] = m_queue.begin();
}

template <typename T>
const T &LRU<T>::Get(int key) const
{
	auto iter = m_cache.find(key);
	if (m_cache.end() == iter)
	{
		throw std::runtime_error("key not found");
	}
	return (iter->second->second);
}

template <typename T>
void LRU<T>::Print() const
{
	for (const auto& item : m_queue)
	{
		std::cout << "key: " << item.first << "\nvalue: " << item.second 
                    << std::endl;
	}
}

int main(void)
{
	LRU<int> cache(5);

	for (int i = 1; i <= 5; ++i)
	{
		cache.Put(i, i);
	}
	cache.Print();

	cache.Put(3, 5);
	cache.Put(6, 8);

	int getter = cache.Get(6);
	if (8 == getter)
	{
		std::cout << "Get() pass" << std::endl;
	}
	
	cache.Print();

	return 0;
}
