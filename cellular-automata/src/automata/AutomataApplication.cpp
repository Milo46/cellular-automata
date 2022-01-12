#include "AutomataApplication.hpp"

#include <iostream>
#include <string>

using std::operator""s;

AutomataApplication::AutomataApplication()
    : m_View(), m_Rectangle(), m_WindowOutline(), m_ViewSpeed(),
    m_Logger(Application::GetClientLogger())
{
    const sf::Vector2f& fWindowSize = static_cast<sf::Vector2f>(Application::GetWindow().getSize());

    m_View.setSize(fWindowSize);
    m_View.setCenter({ fWindowSize.x / 2.0f, fWindowSize.y / 2.0f });

    if (!m_Font.loadFromFile("resources/fonts/Dosis-Light.otf"s))
        Application::GetClientLogger().Error("Failed to load the font!"s);

    m_Text.setFont(m_Font);
    m_Text.setString("m_Window");

    float ratio = m_View.getSize().x / m_View.getSize().y;
    m_ViewSpeed = { ratio * 100.0f, ratio * 100.0f };

    m_Rectangle.setSize({ 100.0f, 100.0f });
    m_Rectangle.setPosition({ 0.0f, 0.0f });
    m_Rectangle.setFillColor(sf::Color::Green);

    m_WindowOutline.setSize(fWindowSize);
    m_WindowOutline.setPosition({ 0.0f, 0.0f });
    m_WindowOutline.setFillColor({ 0u, 0u, 0u, 0u});
    m_WindowOutline.setOutlineColor(sf::Color::Yellow);
    m_WindowOutline.setOutlineThickness(1.0f);

    m_Text.setPosition({ -m_WindowOutline.getOutlineThickness(),
        -m_Text.getGlobalBounds().height * 1.5f - m_WindowOutline.getOutlineThickness() });
}

void AutomataApplication::Update(float deltaTime)
{
    //m_View.move({ -100.0f * deltaTime, -100.0f * deltaTime });

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    m_View.move({ 0.0f, -100.0f * deltaTime });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  m_View.move({ 0.0f, +100.0f * deltaTime });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  m_View.move({ -100.0f * deltaTime, 0.0f });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) m_View.move({ +100.0f * deltaTime, 0.0f });

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) m_Rectangle.move({ 0.0f, -100.0f * deltaTime });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) m_Rectangle.move({ 0.0f, +100.0f * deltaTime });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) m_Rectangle.move({ -100.0f * deltaTime, 0.0f });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) m_Rectangle.move({ +100.0f * deltaTime, 0.0f });
}

void AutomataApplication::Render()
{
    Application::SetView(m_View);

    Application::ClearScreen(sf::Color::Black);
    Application::Draw(m_Rectangle);
    Application::Draw(m_WindowOutline);
    Application::Draw(m_Text);
    Application::Display();
}

void AutomataApplication::EC_Closed()
{
    m_Logger.Trace("[Client]: Closing application..."s);
}

void AutomataApplication::EC_TextEntered(const sf::Event::TextEvent& text)
{
    m_Logger.Trace("[Client]: Text entered: "s + static_cast<char>(text.unicode));
}

void AutomataApplication::EC_MouseWheelScrolled(const sf::Event::MouseWheelEvent& mouseWheel)
{
    m_Logger.Trace("Mouse wheel has been scrolled!"s);

    if (mouseWheel.x < 0.0f) m_View.zoom(1.0f + m_ZoomFactor);
    if (mouseWheel.x > 0.0f) m_View.zoom(1.0f - m_ZoomFactor);
}

void AutomataApplication::EC_MouseButtonPressed(const sf::Event::MouseButtonEvent& mouseButton)
{
    if (mouseButton.button != sf::Mouse::Left)
        return;

    m_PaddingStart = sf::Mouse::getPosition(Application::GetWindow());
}

void AutomataApplication::EC_MouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButton)
{
    if (mouseButton.button != sf::Mouse::Left)
        return;

    m_PaddingEnd = sf::Mouse::getPosition(Application::GetWindow());
}
