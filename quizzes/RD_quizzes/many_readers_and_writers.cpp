#include <iostream>
#include <atomic>
#include <mutex>
#include <chrono>
#include <thread>

const int MAX_READERS = 5;

class SyncWritingReading {
public:
    SyncWritingReading();

    void StartRead();

    void EndRead();

    void StartWrite();

    void EndWrite();

private:
    std::atomic<int> m_count;
    std::mutex m_mutex;
    bool m_writer_active;
};

int main() {
    SyncWritingReading swr;

    std::thread readers[MAX_READERS];
    for (int i = 0; i < MAX_READERS; i++)
    {
        readers[i] = std::thread([&swr]()
        {
            swr.StartRead();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            swr.EndRead();
        });
    }

    std::thread writer([&swr]() {
        swr.StartWrite();
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        swr.EndWrite();
    });

    for (int i = 0; i < MAX_READERS; i++) {
        readers[i].join();
    }

    writer.join();

    return 0;
}

SyncWritingReading::SyncWritingReading(): m_count(0) {}

void SyncWritingReading::StartRead()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    ++m_count;
    std::cout << "Reader started. Readers count: " << m_count << std::endl;
}

void SyncWritingReading::EndRead()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    --m_count;
    std::cout << "Reader ended. Readers count: " << m_count << std::endl;
}

void SyncWritingReading::StartWrite()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    while (m_count > 0)
    {
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        lock.lock();
    }
    m_writer_active = true;
    std::cout << "Writer started." << std::endl;
}

void SyncWritingReading::EndWrite()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_writer_active = false;
    std::cout << "Writer ended." << std::endl;
}
