#include "AutomataApplication.hpp"

#include <iostream>
#include <string>

using std::operator""s;

AutomataApplication::AutomataApplication()
    : m_View(), m_Rectangle(), /*m_WindowOutline(),*/ m_ViewSpeed(),
    m_PanningLast(), m_PanningCurrent(), m_Logger(Application::GetClientLogger())
{
    const sf::Vector2f& fWindowSize = static_cast<sf::Vector2f>(Application::GetWindow().getSize());

    m_View.setSize(fWindowSize);
    m_View.setCenter({ fWindowSize.x / 2.0f, fWindowSize.y / 2.0f });

    if (!m_Font.loadFromFile("resources/fonts/Dosis-Light.otf"s))
        Application::GetClientLogger().Error("Failed to load the font!"s);

    float ratio = m_View.getSize().x / m_View.getSize().y;
    m_ViewSpeed = { ratio * 100.0f, ratio * 100.0f };

    m_Rectangle.setSize({ 100.0f, 100.0f });
    m_Rectangle.setPosition({ 0.0f, 0.0f });
    m_Rectangle.setFillColor(sf::Color::Green);

    m_PlayerBox.SetFont(m_Font);
    m_PlayerBox.SetText("m_Player"s);
    m_PlayerBox.SetSize(m_Rectangle.getSize());
    m_PlayerBox.SetPosition(m_Rectangle.getPosition());
    m_PlayerBox.SetOutlineColor(sf::Color::Magenta);
    m_PlayerBox.SetOutlineThickness(1.0f);

    m_WindowBox.SetFont(m_Font);
    m_WindowBox.SetText("m_Window"s);
    m_WindowBox.SetSize(fWindowSize);
    m_WindowBox.SetPosition({0.0f, 0.0f});
    m_WindowBox.SetOutlineColor(sf::Color::Yellow);
    m_WindowBox.SetOutlineThickness(1.0f);

    m_MouseBox.SetFont(m_Font);
    m_MouseBox.SetText("m_Mouse"s);
    m_MouseBox.SetSize({ 30.0f, 30.0f });
    m_MouseBox.SetOrigin({ 15.0f, 15.0f });
    m_MouseBox.SetOutlineColor(sf::Color::Red);
    m_MouseBox.SetOutlineThickness(1.0f);

    /*m_WindowOutline.setSize(fWindowSize);
    m_WindowOutline.setPosition({ 0.0f, 0.0f });
    m_WindowOutline.setFillColor({ 0u, 0u, 0u, 0u});
    m_WindowOutline.setOutlineColor(sf::Color::Yellow);
    m_WindowOutline.setOutlineThickness(1.0f);

    m_Text.setPosition({ -m_WindowOutline.getOutlineThickness(),
        -m_Text.getGlobalBounds().height * 1.5f - m_WindowOutline.getOutlineThickness() });*/
}

void AutomataApplication::Update(float deltaTime)
{
    m_PlayerBox.SetPosition(m_Rectangle.getPosition());

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    m_View.move({ 0.0f, -100.0f * deltaTime });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  m_View.move({ 0.0f, +100.0f * deltaTime });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  m_View.move({ -100.0f * deltaTime, 0.0f });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) m_View.move({ +100.0f * deltaTime, 0.0f });

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) m_Rectangle.move({ 0.0f, -100.0f * deltaTime });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) m_Rectangle.move({ 0.0f, +100.0f * deltaTime });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) m_Rectangle.move({ -100.0f * deltaTime, 0.0f });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) m_Rectangle.move({ +100.0f * deltaTime, 0.0f });

    { // todo: fix for zoom
        auto fMousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(Application::GetWindow()));

        const auto& view = Application::GetWindow().getView();

        const auto& viewPosition = sf::Vector2f{
            view.getCenter().x - (view.getSize().x / 2.0f),
            view.getCenter().y - (view.getSize().y / 2.0f)
        };

        m_MouseBox.SetPosition(fMousePosition + viewPosition);
    }
}

void AutomataApplication::Render()
{
    Application::SetView(m_View);

    Application::ClearScreen(sf::Color::Black);

    Application::Draw(m_Rectangle);

    Application::Draw(m_PlayerBox);
    Application::Draw(m_WindowBox);
    Application::Draw(m_MouseBox);

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

    m_PanningButtonPressed = true;

    m_PanningLast    = sf::Mouse::getPosition(Application::GetWindow());
    m_PanningCurrent = sf::Mouse::getPosition(Application::GetWindow());
}

void AutomataApplication::EC_MouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButton)
{
    if (mouseButton.button != sf::Mouse::Left)
        return;

    m_PanningButtonPressed = false;
}

void AutomataApplication::EC_MouseMoved(const sf::Event::MouseMoveEvent& mouseMove)
{
    if (!m_PanningButtonPressed)
        return;

    m_PanningCurrent = { mouseMove.x, mouseMove.y };

    m_View.move({ -static_cast<float>(m_PanningCurrent.x - m_PanningLast.x),
        -static_cast<float>(m_PanningCurrent.y - m_PanningLast.y) });

    m_PanningLast = m_PanningCurrent;
}
