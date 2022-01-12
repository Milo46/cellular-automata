#include "Application.hpp"

#include <iostream>

namespace Framework
{
    namespace Configuration
    {
        const sf::VideoMode c_Resolution = { 800u, 600u };
        const sf::String c_Title         = "SFML Window";
        const sf::Uint32 c_Style         = sf::Style::Default;

        const sf::ContextSettings c_Settings{};
    }

    Application::Application()
        : m_Window(), m_EventHandler(),
        m_CoreLogger(Utility::Logger::c_Core),
        m_ClientLogger(Utility::Logger::c_Client)
    {
        if constexpr (Configuration::c_Style == sf::Style::Fullscreen)
        {
            m_Window.create(sf::VideoMode::getDesktopMode(), Configuration::c_Title,
                Configuration::c_Style, Configuration::c_Settings);
        }
        else
        {
            m_Window.create(Configuration::c_Resolution, Configuration::c_Title,
                Configuration::c_Style, Configuration::c_Settings);
        }
    }

    void Application::UpdateSFMLEvents()
    {
        //m_UserEventDispatcher >> m_Window;
        //m_CoreEventDispatcher >> m_UserEventDispatcher;

        while (m_Window.pollEvent(m_EventHandler))
        {
            switch (m_EventHandler.type)
            {
            case sf::Event::Closed:              CoreEC_Closed             ();                           break;
            case sf::Event::Resized:             CoreEC_Resized            (m_EventHandler.size);        break;
            case sf::Event::LostFocus:           CoreEC_LostFocus          ();                           break;
            case sf::Event::GainedFocus:         CoreEC_GainedFocus        ();                           break;
            case sf::Event::TextEntered:         CoreEC_TextEntered        (m_EventHandler.text);        break;
            case sf::Event::KeyPressed:          CoreEC_KeyPressed         (m_EventHandler.key);         break;
            case sf::Event::KeyReleased:         CoreEC_KeyReleased        (m_EventHandler.key);         break;
            case sf::Event::MouseWheelMoved:                                                             break;
            case sf::Event::MouseWheelScrolled:  CoreEC_MouseWheelScrolled (m_EventHandler.mouseWheel);  break;
            case sf::Event::MouseButtonPressed:  CoreEC_MouseButtonPressed (m_EventHandler.mouseButton); break;
            case sf::Event::MouseButtonReleased: CoreEC_MouseButtonReleased(m_EventHandler.mouseButton); break;
            case sf::Event::MouseMoved:          CoreEC_MouseMoved         (m_EventHandler.mouseMove);   break;
            case sf::Event::MouseEntered:        CoreEC_MouseEntered       ();                           break;
            case sf::Event::MouseLeft:           CoreEC_MouseLeft          ();                           break;

            default:
                std::cout << "[Engine]: Unhandled event!\n";
                std::cout << m_EventHandler.type << '\n';
                break;
            }
        }
    }

    void Application::CoreEC_Closed()
    {
        //std::cout << "[Engine]: Closing application!...\n";
        EC_Closed();
        m_Window.close();
    }

    void Application::CoreEC_Resized(const sf::Event::SizeEvent& size)
    {
        //std::cout << "[Engine]: Resized event has been catched!\n";
        EC_Resized(size);
    }

    void Application::CoreEC_LostFocus()
    {
        //std::cout << "[Engine]: LostFocus event has been catched!\n";
        EC_LostFocus();
    }

    void Application::CoreEC_GainedFocus()
    {
        //std::cout << "[Engine]: GainedFocus event has been catched!\n";
        EC_GainedFocus();
    }

    void Application::CoreEC_TextEntered(const sf::Event::TextEvent& text)
    {
        //std::cout << "[Engine]: TextEntered event has been catched!\n";
        EC_TextEntered(text);
    }

    void Application::CoreEC_KeyPressed(const sf::Event::KeyEvent& key)
    {
        //std::cout << "[Engine]: KeyPressed event has been catched!\n";
        EC_KeyPressed(key);
    }

    void Application::CoreEC_KeyReleased(const sf::Event::KeyEvent& key)
    {
        //std::cout << "[Engine]: KeyReleased event has been catched!\n";
        EC_KeyReleased(key);
    }

    void Application::CoreEC_MouseWheelScrolled(const sf::Event::MouseWheelEvent& mouseWheel)
    {
        //std::cout << "[Engine]: MouseWheelScrolled event has been catched!\n";
        EC_MouseWheelScrolled(mouseWheel);
    }

    void Application::CoreEC_MouseButtonPressed(const sf::Event::MouseButtonEvent& mouseButton)
    {
        //std::cout << "[Engine]: MouseButtonPressed event has been catched!\n";
        EC_MouseButtonPressed(mouseButton);
    }

    void Application::CoreEC_MouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButton)
    {
        //std::cout << "[Engine]: MouseButtonReleased event has been catched!\n";
        EC_MouseButtonReleased(mouseButton);
    }

    void Application::CoreEC_MouseMoved(const sf::Event::MouseMoveEvent& mouseMove)
    {
        //std::cout << "[Engine]: MouseMoved event has been catched!\n";
        EC_MouseMoved(mouseMove);
    }

    void Application::CoreEC_MouseEntered()
    {
        //std::cout << "[Engine]: MouseEntered event has been catched!\n";
        EC_MouseEntered();
    }

    void Application::CoreEC_MouseLeft()
    {
        //std::cout << "[Engine]: MouseLeft event has been catched!\n";
        EC_MouseLeft();
    }

    void Application::Run()
    {
        while (m_Window.isOpen())
        {
            m_DeltaTime = m_Clock.restart().asSeconds();

            UpdateSFMLEvents();
            Update(m_DeltaTime);
            Render();
        }
    }

    void Application::Draw(const sf::Drawable& drawable, const sf::RenderStates& states)
    {
        m_Window.draw(drawable, states);
    }
}
