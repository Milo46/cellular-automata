#include "TextBox.hpp"

TextBox::TextBox()
    : m_Text(), m_Box()
{
    m_Box.setFillColor(sf::Color::Transparent);
}

void TextBox::SetFont(const sf::Font& font)
{
	m_Text.setFont(font);
}

void TextBox::SetText(const std::string& text)
{
    for (const auto& it : text)
    {
        if (it == 'q' || it == 'y' || it == 'p' ||
            it == 'g' || it == 'j')
        {
            m_ContainsLowLetters = true;
        }
    }

	m_Text.setString(text);
}

void TextBox::SetSize(const sf::Vector2f& size)
{
	m_Box.setSize(size);
}

void TextBox::SetOrigin(const sf::Vector2f& origin)
{
    m_Box.setOrigin(origin);
}

void TextBox::SetPosition(const sf::Vector2f& position)
{
	m_Box.setPosition(position);
	TextBox::UpdateTextPosition();
}

void TextBox::SetOutlineColor(const sf::Color& color)
{
	m_Box.setOutlineColor(color);
}

void TextBox::SetOutlineThickness(float thickness)
{
	m_Box.setOutlineThickness(thickness);
	TextBox::UpdateTextPosition();
}

const sf::Font& TextBox::GetFont() const
{
	return *m_Text.getFont();
}

const std::string& TextBox::GetText() const
{
	return m_Text.getString();
}

const sf::Vector2f& TextBox::GetSize() const
{
	return m_Box.getSize();
}

const sf::Vector2f& TextBox::GetOrigin() const
{
    return m_Box.getOrigin();
}

const sf::Vector2f& TextBox::GetPosition() const
{
	return m_Box.getPosition();
}

const sf::Color& TextBox::GetOutlineColor() const
{
	return m_Box.getOutlineColor();
}

float TextBox::GetOutlineThickness() const
{
	return m_Box.getOutlineThickness();
}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Box, states);
	target.draw(m_Text, states);
}

void TextBox::UpdateTextPosition()
{
    float xPosition = m_Box.getPosition().x - m_Box.getOrigin().x - m_Box.getOutlineThickness();
    float yPosition = m_Box.getPosition().y - m_Box.getOrigin().y - m_Box.getOutlineThickness() - m_Text.getGlobalBounds().height * 1.5f;

    // fixing higher position when for letters like { q, y, p, g, j }
    // that particular code works only for text with default size (30)
    if (m_ContainsLowLetters)
        yPosition += 7u;

	m_Text.setPosition({ xPosition, yPosition });
}
