#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class TextBox
{
public:
    TextBox() = default;

    

private:
    sf::Text m_Text;
    sf::RectangleShape m_Box;
};
