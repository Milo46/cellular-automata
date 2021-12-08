#include "ArgumentsStorage.hpp"

namespace Framework
{
    ArgumentsStorage::ArgumentsStorage(int argc, char** argv)
        : m_Data(argc)
    {
        for (size_t i = 0u; i < m_Data.size(); ++i)
            m_Data[i] = argv[i];
    }
    
    size_t ArgumentsStorage::GetSize() const noexcept
    {
        return m_Data.size();
    }

    const std::string& ArgumentsStorage::operator[](size_t index) const
    {
        return m_Data[index];
    }
}
