/****************************************/
/*                                      */
/*   Developer: Gali Aviyam             */
/*   Project:   Bit Array               */
/*   Date:      15/05/23                */
/*   Reviewer:  Matan                   */
/*                                      */
/****************************************/

#ifndef ILRD_RD136_7_BITARRAY_HPP
#define ILRD_RD136_7_BITARRAY_HPP

#include <cstddef>      //size_t
#include <string>       //tostring
#include <algorithm>    //transform
#include <stdexcept>    //out_of_range

namespace ilrd
{

const static int BITS_IN_BYTES = 8;
const static int WORDSIZE = (sizeof(size_t) * BITS_IN_BYTES); 
const static int BYTE_MAX_NUM = 256;

static size_t LutBitsInByte[BYTE_MAX_NUM] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2,
3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2,
3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5,
6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3,
4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 
5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 
4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 
5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 
3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 
6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 
6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8};

template <std::size_t SIZE>
class BitArray
{
class BitProxy;

public:
    explicit BitArray();

    bool operator[](std::size_t index) const;
    BitProxy operator[](std::size_t index);

    bool operator==(const BitArray& other) const;
    bool operator!=(const BitArray& other) const;
    BitArray& operator|=(const BitArray& other);
    BitArray& operator&=(const BitArray& other);
    BitArray& operator^=(const BitArray& other);
    BitArray& operator>>=(std::size_t n);
    BitArray& operator<<=(std::size_t n);

    std::size_t Count() const;
    std::string ToString() const;
    bool Get(std::size_t index) const;
    BitArray& Set();
    BitArray& Set(std::size_t index, bool val = true);
    BitArray& Flip();
    BitArray& Flip(std::size_t index);

private:
    class BitProxy
    {
    public:
        explicit BitProxy(std::size_t& bitarr, std::size_t index);

        operator bool() const; 
        BitProxy& operator=(const BitProxy& other); // b[i] = b[j]
        BitProxy& operator=(bool bit); // b[i] = true
        
    private:
        std::size_t& m_bitarr;
        std::size_t m_index;

    };
    static const std::size_t ARR_SIZE = 
                (((SIZE + (WORDSIZE - 1)) & ~(WORDSIZE - 1)) / WORDSIZE);
    size_t m_bitarr[ARR_SIZE];
    static bool GetVal(size_t bitarr, size_t index);
    static void Fill(size_t *bitarr, size_t mask);
    static size_t CleanLeftovers(size_t bitarr);
    static void ShiftExtra(std::size_t *bitarr, std::size_t n);
    static size_t GetIndex(size_t index);
    static size_t GetBitIndex(size_t index);

    class FunctFlip
    {
    public:
        size_t operator()(const size_t& num1);
    };

    class FunctOr
    {
    public:
        size_t operator()(const size_t& num1, const size_t& num2);
    };

    class FunctAnd
    {
    public:
        size_t operator()(const size_t& num1, const size_t& num2);
    };

    class FunctXor
    {
    public:
        size_t operator()(const std::size_t& num1, const std::size_t& num2);
    };

    class FunctCount
    {
    public:
        FunctCount();
        void operator()(const unsigned char &bitarr);
        size_t m_count;
    };

    class FunctShiftLeft
    {
    public:
        FunctShiftLeft(int position);

        void operator()(std::size_t& bitarr);

    private:
        int m_position;
        std::size_t m_leftovers;
    };

    class FunctShiftRight
    {
    public:
        FunctShiftRight(int position);

        void operator()(std::size_t& bitarr);

    private:
        int m_position;
        std::size_t m_leftovers;
    };    
};
/*-------------------------------- Bit Array --------------------------------*/
template<std::size_t SIZE>
BitArray<SIZE>::BitArray()
{
    Fill(m_bitarr, size_t(0));
}

template<std::size_t SIZE>
bool BitArray<SIZE>::operator[](size_t index) const
{
    if (index >= SIZE)
    {
        throw std::out_of_range("index is larger than size");
    }

    return (GetVal(m_bitarr[GetIndex(index)], GetBitIndex(index)));
}

template<std::size_t SIZE>
typename BitArray<SIZE>::BitProxy BitArray<SIZE>::operator[](size_t index)
{
    if (index >= SIZE)
    {
        throw std::out_of_range("index is larger than size");
    }

    return (BitProxy(m_bitarr[GetIndex(index)], GetBitIndex(index)));
}

template<std::size_t SIZE>
bool BitArray<SIZE>::operator==(const BitArray<SIZE> &other) const
{
    return (std::equal(m_bitarr, m_bitarr + ARR_SIZE, other.m_bitarr));
}

template<std::size_t SIZE>
bool BitArray<SIZE>::operator!=(const BitArray<SIZE> &other) const
{
    return !(*this == other);
}

/*----------------------------------------------------------------------------*/
template <size_t SIZE>
size_t BitArray<SIZE>::FunctOr::operator()(const size_t& num1, const size_t& num2)
{
    return (num1 | num2);
}

template <size_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::operator|=(const BitArray& other)
{
    std::transform(m_bitarr, m_bitarr + ARR_SIZE, other.m_bitarr, m_bitarr, FunctOr());

    return *this;
}

/*----------------------------------------------------------------------------*/
template <size_t SIZE>
size_t BitArray<SIZE>::FunctAnd::operator()(const size_t& num1, const size_t& num2)
{
    return (num1 & num2);
}

template <size_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::operator&=(const BitArray& other)
{
    std::transform(m_bitarr, m_bitarr + ARR_SIZE, other.m_bitarr, m_bitarr, FunctAnd());

    return *this;
}

/*----------------------------------------------------------------------------*/
template <size_t SIZE>
size_t BitArray<SIZE>::FunctXor::operator()(const size_t& num1, const size_t& num2)
{
    return (num1 ^ num2);
}

template <size_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::operator^=(const BitArray& other)
{
    std::transform(m_bitarr, m_bitarr + ARR_SIZE, other.m_bitarr, m_bitarr, FunctXor());

    return *this;
}

/*----------------------------------------------------------------------------*/
template <size_t SIZE>
void BitArray<SIZE>::FunctCount::operator()(const unsigned char &bitarr)
{
    m_count += LutBitsInByte[bitarr];
}

template<std::size_t SIZE>
BitArray<SIZE>::FunctCount::FunctCount() : m_count(0) {}

template<std::size_t SIZE>
std::size_t BitArray<SIZE>::Count() const
{
    const unsigned char *tmp = reinterpret_cast<const unsigned char *>(m_bitarr);

    return (std::for_each(tmp, tmp + (ARR_SIZE * sizeof(size_t)), FunctCount()).m_count);
}

/*----------------------------------------------------------------------------*/
template<std::size_t SIZE>
std::string BitArray<SIZE>::ToString() const
{
    std::string buffer;

    for (int i = static_cast<int>(SIZE) - 1; i >= 0; --i)
    {
        buffer += ('0' + (*this)[i]);
    }

    return buffer;
}

/*----------------------------------------------------------------------------*/
template<std::size_t SIZE>
bool BitArray<SIZE>::Get(std::size_t index) const
{
    if (index >= SIZE)
    {
        throw std::out_of_range("index is larger than size");
    }

    return (*this)[index];
}

/*----------------------------------------------------------------------------*/
template<std::size_t SIZE>
BitArray<SIZE> &BitArray<SIZE>::Set()
{
    Fill(m_bitarr, ~(size_t(0)));
    m_bitarr[ARR_SIZE - 1] = CleanLeftovers(m_bitarr[ARR_SIZE - 1]);

    return *this;
}

template<std::size_t SIZE>
BitArray<SIZE> &BitArray<SIZE>::Set(std::size_t index, bool val)
{
    if (index >= SIZE)
    {
        throw std::out_of_range("index is larger than size");
    }

    (*this)[index] = val;

    return *this;
}

/*----------------------------------------------------------------------------*/
template<std::size_t SIZE>
size_t BitArray<SIZE>::FunctFlip::operator()(const size_t& num)
{
    return (~num);
}

template<std::size_t SIZE>
BitArray<SIZE> &BitArray<SIZE>::Flip()
{
    std::transform(m_bitarr, m_bitarr + ARR_SIZE, m_bitarr, FunctFlip());
    m_bitarr[ARR_SIZE - 1] = CleanLeftovers(m_bitarr[ARR_SIZE - 1]);

    return *this;
}

template<std::size_t SIZE>
BitArray<SIZE> &BitArray<SIZE>::Flip(std::size_t index)
{
    if (index >= SIZE)
    {
        throw std::out_of_range("index is larger than size");
    }

    ((*this)[index]) = !((*this)[index]);

    return *this;
}

/*----------------------------------------------------------------------------*/
template<std::size_t SIZE>
BitArray<SIZE>::FunctShiftLeft::FunctShiftLeft(int position): m_position(position), m_leftovers(0) {}

template<std::size_t SIZE>
void BitArray<SIZE>::FunctShiftLeft::operator()(std::size_t &bitarr)
{
    std::size_t tmp = bitarr >> (WORDSIZE - m_position); 
    bitarr = ((bitarr << m_position) | m_leftovers);
    m_leftovers = tmp;
}

template<std::size_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::operator<<=(std::size_t n)
{
    if (n >= WORDSIZE)
    {
        ShiftExtra(m_bitarr, n);
    }

    std::for_each(m_bitarr, m_bitarr + ARR_SIZE, FunctShiftLeft(n & (WORDSIZE - 1)));

    m_bitarr[ARR_SIZE - 1] = CleanLeftovers(m_bitarr[ARR_SIZE - 1]);
    
    return (*this);
}

/*----------------------------------------------------------------------------*/
template<std::size_t SIZE> 
BitArray<SIZE>& BitArray<SIZE>::operator>>=(std::size_t n)
{
    std::reverse(m_bitarr, m_bitarr + ARR_SIZE);

    if (n >= WORDSIZE)
    {
        ShiftExtra(m_bitarr, n);
    }
    
    std::for_each(m_bitarr, m_bitarr + ARR_SIZE, FunctShiftRight(n & (WORDSIZE - 1)));
    std::reverse(m_bitarr, m_bitarr + ARR_SIZE);

    return (*this);
}

template<std::size_t SIZE>
BitArray<SIZE>::FunctShiftRight::FunctShiftRight(int position): m_position(position), m_leftovers(0) {}

template<std::size_t SIZE>
void BitArray<SIZE>::FunctShiftRight::operator()(std::size_t &bitarr)
{
    std::size_t tmp = bitarr << (WORDSIZE - m_position);
    bitarr = ((bitarr >> m_position) | m_leftovers);
    m_leftovers = tmp;
}


/*----------------------------- static functions -----------------------------*/

template<std::size_t SIZE>
bool BitArray<SIZE>::GetVal(size_t bitarr, size_t index)
{
    if (index >= SIZE)
    {
        throw std::out_of_range("index is larger than size");
    }

    return ((bitarr >> index) & size_t(1));
}

template<std::size_t SIZE>
size_t BitArray<SIZE>::CleanLeftovers(size_t bitarr)
{
    size_t leftovers = WORDSIZE - (SIZE & (WORDSIZE - 1));
    bitarr = (bitarr << leftovers) >> leftovers;
    
    return bitarr;
}

template<std::size_t SIZE>
void BitArray<SIZE>::Fill(size_t *bitarr, size_t mask)
{
    std::fill(bitarr, bitarr + ARR_SIZE, mask);
}

template<std::size_t SIZE>
void BitArray<SIZE>::ShiftExtra(std::size_t *bitarr, std::size_t n)
{
    std::move(bitarr, bitarr + ARR_SIZE - (n / WORDSIZE), bitarr + (n / WORDSIZE));
    std::fill(bitarr, bitarr + (n / WORDSIZE), size_t(0));
}

template<std::size_t SIZE>
size_t BitArray<SIZE>::GetIndex(size_t index)
{
    return (index / WORDSIZE);
}

template<std::size_t SIZE>
size_t BitArray<SIZE>::GetBitIndex(size_t index)
{
    return (index & (WORDSIZE - 1));
}

/*-------------------------------- Bit Proxy --------------------------------*/

template<std::size_t SIZE>
BitArray<SIZE>::BitProxy::BitProxy(size_t &bitarr, size_t index) : 
                             m_bitarr(bitarr), m_index(index) {}

template<std::size_t SIZE>
BitArray<SIZE>::BitProxy::operator bool() const
{
    return (GetVal(m_bitarr, m_index));
}

template<std::size_t SIZE>
typename BitArray<SIZE>::BitProxy& BitArray<SIZE>::BitProxy::operator=(const BitProxy &other)
{
    *this = (GetVal(other.m_bitarr, other.m_index));

    return *this;
}

template<std::size_t SIZE>
typename BitArray<SIZE>::BitProxy& BitArray<SIZE>::BitProxy::operator=(bool bit)
{
    m_bitarr = (m_bitarr & ~(1UL << m_index)) | (size_t(bit) << m_index);

    return *this;
}

}   // namespace ilrd

#endif // ILRD_RD136_7_BITARRAY_HPP




