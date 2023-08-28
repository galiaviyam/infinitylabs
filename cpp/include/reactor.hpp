/****************************************/
/*                                      */
/*   Developer: Gali Aviyam             */
/*   Project:   Reactor                 */
/*   Date:      15/06/23                */
/*   Reviewer:  Gal                     */
/*                                      */
/****************************************/

#ifndef ILRD_RD136_7_REACTOR_HPP
#define ILRD_RD136_7_REACTOR_HPP

#include <vector>           // std::vector
#include <functional>       // std::function
#include <unordered_map>    // std::unordered_map

namespace ilrd
{

class Reactor
{
public:
    enum Mode : int
    {
        READ,
        WRITE,
        EXCEPT,
        NUM_OF_MODES
    };

    Reactor();
    ~Reactor();

    Reactor(const Reactor&) = delete;
    Reactor& operator=(const Reactor&) = delete;

    void Add(int fd, Mode mode, const std::function<void(void)>& callback);
    void Remove(int fd, Mode mode);

    void Run(); // blocking
    void Stop();

private:

    class FDListener
    {
    public:
        typedef std::pair<int, Mode> fd_mode_t;

        FDListener(int timeoutSec);
        ~FDListener() = default;
        FDListener(const FDListener&) = delete;
        FDListener& operator=(const FDListener&) = delete;
        
        std::vector<fd_mode_t> Wait(const std::vector<fd_mode_t>& fd);
    private:
        int m_timeoutSec;
    };

    struct Hash
    {
        std::size_t operator()(const std::pair<int, Mode>& key) const
        {
            return std::hash<int>{}(key.first);
        }
    };

    bool m_isRunning;
    std::vector<std::pair<int, Mode>> m_fds;
    std::unordered_map<std::pair<int, Mode>,
                       std::function<void(void)>, Hash> m_callbacks;
};

}   // namespace ilrd

#endif /* ILRD_RD136_7_REACTOR_HPP */   