#pragma once

#include "framework/Application.hpp"

#include "logger/Logger.hpp"

class AutomataApplication : public Framework::Application
{
public:
    AutomataApplication();

protected:
    virtual void Update(float deltaTime) override;
    virtual void Render() override;

protected:
    virtual void EC_Closed() override;
    virtual void EC_TextEntered(const sf::Event::TextEvent& text) override;
    virtual void EC_MouseWheelScrolled(const sf::Event::MouseWheelEvent& mouseWheel) override;

    // padding experimental
    virtual void EC_MouseButtonPressed(const sf::Event::MouseButtonEvent& mouseButton) override;
    virtual void EC_MouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButton) override;

private:
    sf::View m_View;
    sf::Font m_Font;
    sf::Text m_Text;

    sf::Vector2f m_ViewSpeed;

    float m_ZoomFactor = 0.1f;

private:
    sf::Vector2i m_PaddingStart;
    sf::Vector2i m_PaddingEnd;

private:
    sf::RectangleShape m_Rectangle;
    sf::RectangleShape m_WindowOutline;

private:
    Utility::Logger m_Logger;
};
