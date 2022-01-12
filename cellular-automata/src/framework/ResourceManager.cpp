#include "ResourceManager.hpp"

namespace Framework
{
    bool ResourceManager::CreateFont(const std::string& name, const std::string& filepath)
    {
        auto font = std::make_shared<sf::Font>();
        if (!font->loadFromFile(filepath))
            return false;

        

        return true;
    }
}
