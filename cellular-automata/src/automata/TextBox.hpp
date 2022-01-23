#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <string>

class TextBox : public sf::Drawable
{
public:
    TextBox();

    void SetFont(const sf::Font& font);
    void SetText(const std::string& text);
    void SetSize(const sf::Vector2f& size);
    void SetOrigin(const sf::Vector2f& origin);
    void SetPosition(const sf::Vector2f& position);
    void SetOutlineColor(const sf::Color& color);
    void SetOutlineThickness(float thickness);

    const sf::Font& GetFont() const;
    const std::string& GetText() const;
    const sf::Vector2f& GetSize() const;
    const sf::Vector2f& GetOrigin() const;
    const sf::Vector2f& GetPosition() const;
    const sf::Color& GetOutlineColor() const;
    float GetOutlineThickness() const;

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    void UpdateTextPosition();

private:
    sf::Text m_Text;
    sf::RectangleShape m_Box;
    
    bool m_ContainsLowLetters = false;
};
