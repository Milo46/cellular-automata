#include <iostream>
#include <vector>

#include "StaticArray.hpp"

namespace CAConstants
{
    constexpr size_t c_ZeroDimensional  = 0u;
    constexpr size_t c_OneDimensional   = 1u;
    constexpr size_t c_TwoDimensional   = 2u;
    constexpr size_t c_ThreeDimensional = 3u;
    constexpr size_t c_FourDimensional  = 4u;
}

template<typename _Ty, size_t _Dimensions>
class CADataStatic
{
public:
    using Type = _Ty;
    
public:
    CADataStatic(size_t size)
        : m_Data(_Dimensions * size) {}

private:
    StaticArray<_Ty> m_Data;
};

int main(int argc, char** argv)
{
    

    return EXIT_SUCCESS;
}
