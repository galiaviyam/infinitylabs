/****************************************/
/*                                      */
/*   Developer: Gali Aviyam             */
/*   Project:   Bit Array               */
/*   Date:      14/05/23                */
/*   Reviewer:  Matan                   */
/*                                      */
/****************************************/

#include "bit_array_ph1.hpp"    //bitarr header

namespace ilrd
{

/*-------------------------------- Bit Array --------------------------------*/
BitArray::BitArray(size_t bitarrVal) : m_bitarr(bitarrVal) {}

bool BitArray::operator[](size_t index) const
{
    return (GetVal(m_bitarr, index));
}

BitArray::BitProxy BitArray::operator[](size_t index)
{
    return BitProxy(m_bitarr, index);
}

bool BitArray::GetVal(size_t bitarr, size_t index)
{
    return ((bitarr >> index) & 1);
}

/*-------------------------------- Bit Proxy --------------------------------*/

BitArray::BitProxy::BitProxy(size_t &bitarr, size_t index) : 
                             m_bitarray(bitarr), m_index(index) {}

BitArray::BitProxy& BitArray::BitProxy::operator=(const BitProxy &other)
{
    *this = (GetVal(other.m_bitarray, other.m_index));

    return *this;
}

BitArray::BitProxy& BitArray::BitProxy::operator=(bool bit)
{
    m_bitarray = (m_bitarray & ~(bit << m_index)) | (bit << m_index);

    return *this;
}

BitArray::BitProxy::operator bool() const
{
    return (GetVal(m_bitarray, m_index));
}



}   // namespace ilrd
