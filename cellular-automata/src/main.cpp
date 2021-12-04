#include <iostream>
#include <vector>

#include "automata/SimulationSpace.hpp"

#include <SFML/Graphics.hpp>

int main(int argc, char** argv)
{
    sf::RenderWindow window(sf::VideoMode(800u, 600u), "SFML Window!");
    sf::Event eventHandle{};

    sf::RectangleShape rectangle{};
    rectangle.setSize({ 100.0f, 100.0f });
    rectangle.setPosition({ 100.0f, 100.0f });
    rectangle.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (window.pollEvent(eventHandle))
        {
            if (eventHandle.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(rectangle);
        window.display();
    }

    return EXIT_SUCCESS;
}
