#include "TextBox.hpp"

void TextBox::SetFont(const sf::Font& font)
{
	m_Text.setFont(font);
}

void TextBox::SetText(const std::string& text)
{
	m_Text.setString(text);
}

void TextBox::SetSize(const sf::Vector2f& size)
{
	m_Box.setSize(size);
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
	m_Text.setPosition({ -m_Box.getOutlineThickness(),
		-m_Text.getGlobalBounds().height * 1.5f - m_Box.getOutlineThickness() });
}
