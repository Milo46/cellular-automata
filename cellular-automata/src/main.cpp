#include <iostream>
#include <vector>

#include "automata/SimulationSpace.hpp"

#include "framework/Application.hpp"
#include "framework/ArgumentsStorage.hpp"

#include "utility/Optimalizations.hpp"

#include <SFML/Graphics.hpp>

int main(int argc, char** argv)
{
    Utility::IO_Optimalization();

    auto arguments = Framework::ArgumentsStorage(argc, argv);

    for (size_t i = 0u; i < arguments.GetSize(); ++i)
        std::cout << i << ": " << arguments[i] << '\n';

    for (const auto& it : arguments)
    {
        static size_t i = 0u;
        std::cout << i++ << ": " << it << '\n';
    }

    /*sf::RenderWindow window({800u, 600u}, "SFML Window!");
    sf::Event eventHandle{};

    sf::RectangleShape rectangle{};
    rectangle.setSize({ 100.0f, 100.0f });
    rectangle.setPosition({ 100.0f, 100.0f });
    rectangle.setFillColor(sf::Color::Green);

    sf::Clock dtClock{};
    double deltaTime{};

    while (window.isOpen())
    {
        while (window.pollEvent(eventHandle))
        {
            if (eventHandle.type == sf::Event::Closed)
                window.close();
        }

        deltaTime = dtClock.restart().asSeconds();
        std::cout << (1.0 / deltaTime) << '\n';

        window.clear();
        window.draw(rectangle);
        window.display();
    }*/

    return EXIT_SUCCESS;
}
