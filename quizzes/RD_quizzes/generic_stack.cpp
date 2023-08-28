#include <iostream>
#include <cstring>

namespace ilrd
{
template <typename T>
class Stack
{
public:
    Stack();
    ~Stack();

    T Peek() const;
    void Push(T data);
    T Pop();

private:
    T *m_sp;
    std::size_t m_size;
    std::size_t m_capacity;
};

template <typename T>
Stack<T>::Stack(): m_sp(new T[10]), m_size(0), m_capacity(10) {}

template <typename T>
Stack<T>::~Stack()
{
    delete[] m_sp;
}

template <typename T>
void Stack<T>::Push(T data) 
{
    if (m_size == m_capacity)
    {
        m_capacity *= 2;
        
        T *tmp = new T[m_capacity];
        std::memcpy(tmp, m_sp, m_size * sizeof(T));

        delete[] m_sp;
        m_sp = tmp;
    }

    *(m_sp + m_size) = data;
    ++m_size;
}

template <typename T>
T Stack<T>::Pop()
{
    --m_size;
    
    return *(m_sp + m_size);
}

template <typename T>
T Stack<T>::Peek() const
{
    return *(m_sp + m_size - 1);
}

}

int main()
{
    ilrd::Stack<int> stack1;
    
    for (int i = 0; 100 > i; ++i)
    {
        stack1.Push(i);
    }

    for (int i = 99; 0 <= i; --i)
    {
        if (i != stack1.Peek())
        {
            std::cout << "FAIL" << stack1.Peek() << std::endl;
        }

        stack1.Pop();
    }

    ilrd::Stack<float> stack2;
    
    for (float i = 0.5; 100 > i; ++i)
    {
        stack2.Push(i);
    }

    for (float i = 99.5; 0 <= i; --i)
    {
        if (i != stack2.Peek())
        {
            std::cout << "FAIL" << stack2.Peek() << std::endl;
        }

        stack2.Pop();
    }

    std::cout << "pass" << std::endl;

    return 0;
}
