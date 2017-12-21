#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 800}), "HOME");
    window.clear();

    sf::RectangleShape bloc;
    bloc.setSize({460, 200});
    bloc.setPosition({190, 500});
    bloc.setFillColor(sf::Color(0x8B, 0x45, 0x13));
    window.draw(bloc);

    sf::RectangleShape door;
    door.setSize({-70, -150});
    door.setPosition({350, 700});
    door.setFillColor(sf::Color(0x80, 0x80, 0x80));
    window.draw(door);

    sf::ConvexShape trap;
    trap.setFillColor(sf::Color(0x80, 0x00, 0x00));
    trap.setPosition(415, 500);
    trap.setPointCount(4);
    trap.setPoint(0, {-300, 0});
    trap.setPoint(1, {+300, 0});
    trap.setPoint(2, {+100, -150});
    trap.setPoint(3, {-100, -150});
    window.draw(trap);

    sf::RectangleShape toobe;
    toobe.setSize({-20, -40});
    toobe.setPosition({480, 380});
    toobe.setFillColor(sf::Color(0xC0, 0xC0, 0xC0));
    window.draw(toobe);

    sf::RectangleShape youtoobe;
    youtoobe.setSize({60, -40});
    youtoobe.setPosition({440, 340});
    youtoobe.setFillColor(sf::Color(0xC0, 0xC0, 0xC0));
    window.draw(youtoobe);

    sf::CircleShape crcl(10);
    crcl.setPosition({465, 275});
    crcl.setFillColor(sf::Color(0xDC, 0xDC, 0xDC));
    window.draw(crcl);

    sf::CircleShape crcl1(15);
    crcl1.setPosition({470, 255});
    crcl1.setFillColor(sf::Color(0xDC, 0xDC, 0xDC));
    window.draw(crcl1);

    sf::CircleShape crcl2(20);
    crcl2.setPosition({485, 240});
    crcl2.setFillColor(sf::Color(0xDC, 0xDC, 0xDC));
    window.draw(crcl2);

    sf::CircleShape crcl3(25);
    crcl3.setPosition({495, 220});
    crcl3.setFillColor(sf::Color(0xDC, 0xDC, 0xDC));
    window.draw(crcl3);

    window.display();

    sf::sleep(sf::seconds(5));
}