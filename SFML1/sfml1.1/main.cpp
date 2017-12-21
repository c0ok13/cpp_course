#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({240, 480}), "SVETOFOR");
    window.clear();

    sf::RectangleShape shape;
    shape.setSize({240, 500});
    shape.setPosition({0, 0});
    shape.setFillColor(sf::Color(0x80, 0x80, 0x80));
    window.draw(shape);

    sf::CircleShape shape1(60);
    shape1.setPosition({60, 30});
    shape1.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape1);

    sf::CircleShape shape2(60);
    shape2.setPosition({60, 180});
    shape2.setFillColor(sf::Color(0xFF, 0xFF, 0x0));
    window.draw(shape2);

    sf::CircleShape shape3(60);
    shape3.setPosition({60, 330});
    shape3.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape3);

    window.display();

    sf::sleep(sf::seconds(5));
}