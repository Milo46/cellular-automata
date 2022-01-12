#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <memory>
#include <vector>

#define CHECK_IF_SFML_RESOURCE(_Name) \
    static_assert(std::is_same_v<_Name, sf::Font> || \
                  std::is_same_v<_Name, sf::Texture>);

namespace Framework
{
    template<typename _Ty>
    struct Resource
    {
        std::string Filepath;
        std::shared_ptr<_Ty> Data;
    };

    class ResourceManager
    {
    public:
        //                  name
        using ResourceKey = std::string;

        template<typename _Ty>
        using ResourceValue = Resource<_Ty>;

    public:
        ResourceManager() = default;

        template<typename _SfResource>
        bool CreateResource(const std::string& name, const std::string& filepath)
        {
            CHECK_IF_SFML_RESOURCE(_SfResource);

            auto pureResource = std::make_shared<_SfResource>();
            if (!pureResource.loadFromFile(filepath))
                return false;

            auto resource = new Resource<_SfResource>(filepath, pureResource);
            m_Data.insert(std::make_pair(name, resource));

            return true;
        }

        template<typename _SfResource>
        const Resource<_SfResource>& GetResource(const std::string& name) const
        {
            CHECK_IF_SFML_RESOURCE(_SfResource);

            if (m_Data.find(name) == m_Data.end())
                return nullptr;

            return reinterpret_cast<Resource<_SfResource>>(m_Data.at(name));
        }

        template<typename _SfResource>
        const Resource<_SfResource>& LoadResource(const std::string& filepath)
        {
            
        }

        bool CreateFont(const std::string& name, const std::string& filepath);
        bool CreateTexture(const std::string& name, const std::string& filepath);

        const Resource<sf::Font>& GetFont(const std::string& name) const;
        const Resource<sf::Texture>& GetTexture(const std::string& name) const;

        const Resource<sf::Font>& LoadFont(const std::string& filepath);
        const Resource<sf::Texture>& LoadTexture(const std::string& filepath);

    private:
        std::map<std::string, void*> m_Data;
    };
}
