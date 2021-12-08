#pragma once

#include <iostream>

namespace Utility
{
    void IO_Optimalization() noexcept
    {
        std::ios_base::sync_with_stdio(false);
        std::cout.tie(nullptr);
        std::cin.tie(nullptr);
    }
}
