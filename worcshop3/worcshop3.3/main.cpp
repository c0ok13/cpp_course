#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

/*void init(, )
{
}*/

//обработка мышки
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition, sf::Vector2f &center, sf::Vector2f &pos2, sf::VertexArray &lines)
{
    mousePosition = {float(event.x), float(event.y)};

    pos2 = mousePosition;
    sf::Vector2f delta = center - pos2;
    std::cout << "Distnace:" << std::hypot(delta.x, delta.y) << std::endl;
    lines[1].position = mousePosition;
    lines[1].color = sf::Color::Green;
}

//opros
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition, sf::Vector2f &center, sf::Vector2f &pos2, sf::VertexArray &lines)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition, center, pos2, lines);
            break;
        default:
            break;
        }
    }
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, sf::VertexArray &lines)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(lines);
    window.display();
}

// Программа рисует в окне стрелку, которая поворачивается вслед за курсором мыши.
int main()
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Arrow follows mouse", sf::Style::Default, settings);

    sf::VertexArray lines(sf::LinesStrip, 2);

    sf::Vector2f pos2;

    sf::Vector2f center(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    lines[0].position = center;
    lines[0].color = sf::Color::Red;

    sf::Vector2f mousePosition;

    while (window.isOpen())
    {
        pollEvents(window, mousePosition, center, pos2, lines);
        redrawFrame(window, lines);
    }
}