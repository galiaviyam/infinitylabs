/****************************************/
/*                                      */
/*   Developer: Gali Aviyam             */
/*   Project:   Bit Array               */
/*   Date:      14/05/23                */
/*   Reviewer:  Matan                   */
/*                                      */
/****************************************/

#include <cstddef>      // size_t


namespace ilrd
{
class BitArray
{
class BitProxy;

public:
    explicit BitArray(size_t bitarrVal = 0);

    bool operator[](size_t index) const;
    BitProxy operator[](size_t index);

private:
    class BitProxy
    {
    public:
        explicit BitProxy(size_t &bitarr, size_t index);

        BitProxy& operator=(const BitProxy& other); // b[i] = b[j]
        BitProxy& operator=(bool bit); // b[i] = TRUE
        operator bool() const;

    private:
        size_t& m_bitarray;
        size_t m_index;
    };
    size_t m_bitarr;
    static bool GetVal(size_t bitarr, size_t index);
};

} // ilrd