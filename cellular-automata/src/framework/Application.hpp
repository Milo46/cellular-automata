#pragma once

#include <SFML/Graphics.hpp>

#include "framework/ResourceManager.hpp"
#include "logger/Logger.hpp"

namespace Framework
{
    class Application
    {
    public:
        //static const sf::Keyboard::Key c_FullscreenKey = sf::Keyboard::F11;

    public:
        Application();
        void Run();

    protected: // Protected tools for inside content
        void Draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);

        inline void SetView(const sf::View& view) { m_Window.setView(view); }

        inline void ClearScreen(const sf::Color& color) { m_Window.clear(color); }
        inline void Display() /*---------------------*/ { m_Window.display(); }

        inline /*-*/ sf::RenderWindow& GetWindow() /*-*/ { return m_Window; }
        inline const sf::RenderWindow& GetWindow() const { return m_Window; }

        inline void Close() { m_Window.close(); }

        inline const Utility::Logger& GetClientLogger() const { return m_ClientLogger; }

    protected:
        virtual void EC_Closed() {}
        virtual void EC_Resized(const sf::Event::SizeEvent& size) {}
        virtual void EC_LostFocus() {}
        virtual void EC_GainedFocus() {}
        virtual void EC_TextEntered(const sf::Event::TextEvent& text) {}
        virtual void EC_KeyPressed(const sf::Event::KeyEvent& key) {}
        virtual void EC_KeyReleased(const sf::Event::KeyEvent& key) {}
        //virtual void EC_MouseWheelMoved(Application& sender) {} // deprecated
        virtual void EC_MouseWheelScrolled(const sf::Event::MouseWheelEvent& mouseWheel) {}
        virtual void EC_MouseButtonPressed(const sf::Event::MouseButtonEvent& mouseButton) {}
        virtual void EC_MouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButton) {}
        virtual void EC_MouseMoved(const sf::Event::MouseMoveEvent& mouseMove) {}
        virtual void EC_MouseEntered() {}
        virtual void EC_MouseLeft() {}

        // Supports only desktop!
        //virtual void EC_JoystickButtonPressed(...) {}
        //virtual void EC_JoystickButtonReleased(...) {}
        //virtual void EC_JoystickMoved(...) {}
        //virtual void EC_JoystickConnected(...) {}
        //virtual void EC_JoystickDisconnected(...) {}
        //virtual void EC_TouchBegan(...) {}
        //virtual void EC_TouchMoved(...) {}
        //virtual void EC_TouchEnded(...) {}
        //virtual void EC_SensorChanged(...) {}

    protected: // Pure virtual methods to override in derived class
        virtual void Update(float deltaTime) = 0;
        virtual void Render() = 0;

    private: // Internal functionality methods
        void UpdateSFMLEvents();

        void CoreEC_Closed();
        void CoreEC_Resized(const sf::Event::SizeEvent& size);
        void CoreEC_LostFocus();
        void CoreEC_GainedFocus();
        void CoreEC_TextEntered(const sf::Event::TextEvent& text);
        void CoreEC_KeyPressed(const sf::Event::KeyEvent& key);
        void CoreEC_KeyReleased(const sf::Event::KeyEvent& key);
        //void CoreEC_MouseWheelMoved(Application& sender); // deprecated
        void CoreEC_MouseWheelScrolled(const sf::Event::MouseWheelEvent& mouseWheel);
        void CoreEC_MouseButtonPressed(const sf::Event::MouseButtonEvent& mouseButton);
        void CoreEC_MouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButton);
        void CoreEC_MouseMoved(const sf::Event::MouseMoveEvent& mouseMove);
        void CoreEC_MouseEntered();
        void CoreEC_MouseLeft();

    private:
        sf::RenderWindow m_Window;
        sf::Event m_EventHandler;

        sf::Clock m_Clock;
        float m_DeltaTime = 0.0;

    private:
        Utility::Logger m_CoreLogger;
        Utility::Logger m_ClientLogger;
    };
}
