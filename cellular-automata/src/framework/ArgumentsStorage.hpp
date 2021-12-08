#pragma once

#include <string>
#include <vector>

namespace Framework
{
    class ArgumentsStorage
    {
    public:
        ArgumentsStorage(int argc, char** argv);

        size_t GetSize() const noexcept;

        const std::string& operator[](size_t index) const;

    public:
        inline auto begin() { return m_Data.begin(); }
        inline auto end()   { return m_Data.end(); }

        inline auto begin() const { return m_Data.begin(); }
        inline auto end() const   { return m_Data.end(); }

    private:
        std::vector<std::string> m_Data;
    };
}
