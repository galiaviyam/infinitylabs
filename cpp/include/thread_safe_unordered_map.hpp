#ifndef ILRD_RD136_7_THREAD_SAFE_UNORDERED_MAP_HPP
#define ILRD_RD136_7_THREAD_SAFE_UNORDERED_MAP_HPP

#include <unordered_map>
#include <mutex>
#include <functional>

namespace ilrd
{
template<typename Key, typename Value>
class ThreadSafeUnorderedMap
{
public:
    void insert(const Key& key, const Value& value)
    {
        std::lock_guard<std::mutex> lock(mutex);
        map[key] = value;
    }

    bool find(const Key& key, Value& value)
    {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = map.find(key);
        if (it != map.end())
        {
            value = it->second;
            return true;
        }
        return false;
    }

    bool erase(const Key& key)
    {
        std::lock_guard<std::mutex> lock(mutex);
        return map.erase(key) > 0;
    }

    void for_each(std::function<void(const Key&, const Value&)> callback)
    {
        std::unique_lock<std::mutex> lock(mutex);
        auto copy = map;

        lock.unlock();

        for (const auto& pair : copy)
        {
            callback(pair.first, pair.second);
        }
    }

private:
    std::unordered_map<Key, Value> map;
    std::mutex mutex;
};
} //namespace ilrd
#endif /* ILRD_RD136_7_THREAD_SAFE_UNORDERED_MAP_HPP */    
