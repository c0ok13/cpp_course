#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({660, 250}), "MY NAME");
    window.clear();

    sf::RectangleShape m1;
    m1.setSize({20, 150});
    m1.setPosition({50, 50});
    m1.setFillColor(sf::Color(0x80, 0x80, 0x80));
    window.draw(m1);

    sf::RectangleShape m2;
    m2.setSize({20, 78});
    m2.setRotation(-45);
    m2.setPosition({55, 64});
    m2.setFillColor(sf::Color(0x80, 0x80, 0x80));
    window.draw(m2);

    sf::RectangleShape m3;
    m3.setSize({20, 150});
    m3.setPosition({150, 50});
    m3.setFillColor(sf::Color(0x80, 0x80, 0x80));
    window.draw(m3);

    sf::RectangleShape m4;
    m4.setSize({20, 77});
    m4.setRotation(45);
    m4.setPosition({150, 51});
    m4.setFillColor(sf::Color(0x80, 0x80, 0x80));
    window.draw(m4);

    sf::RectangleShape y1;
    y1.setSize({20, 100});
    y1.setRotation(-40);
    y1.setPosition({200, 63});
    y1.setFillColor(sf::Color(0x80, 0x80, 0x80));
    window.draw(y1);

    sf::RectangleShape y2;
    y2.setSize({20, 100});
    y2.setRotation(40);
    y2.setPosition({320, 50});
    y2.setFillColor(sf::Color(0x80, 0x80, 0x80));
    window.draw(y2);

    sf::RectangleShape y3;
    y3.setSize({23, 70});
    y3.setPosition({256, 130});
    y3.setFillColor(sf::Color(0x80, 0x80, 0x80));
    window.draw(y3);

    sf::RectangleShape a11;
    a11.setSize({20, 155});
    a11.setPosition({400, 51});
    a11.setRotation(20);
    a11.setFillColor(sf::Color(0x80, 0x80, 0x80));
    window.draw(a11);

    sf::RectangleShape a12;
    a12.setSize({20, 155});
    a12.setPosition({400, 56});
    a12.setRotation(-20);
    a12.setFillColor(sf::Color(0x80, 0x80, 0x80));
    window.draw(a12);

    sf::RectangleShape ap11;
    ap11.setSize({20, 20});
    ap11.setPosition({400, 50});
    ap11.setFillColor(sf::Color(0x80, 0x80, 0x80));
    window.draw(ap11);

    sf::RectangleShape ap12;
    ap12.setSize({20, 70});
    ap12.setPosition({370, 160});
    ap12.setRotation(-90);
    ap12.setFillColor(sf::Color(0x80, 0x80, 0x80));
    window.draw(ap12);

    sf::RectangleShape a21;
    a21.setSize({20, 155});
    a21.setPosition({550, 51});
    a21.setRotation(20);
    a21.setFillColor(sf::Color(0x80, 0x80, 0x80));
    window.draw(a21);

    sf::RectangleShape a22;
    a22.setSize({20, 155});
    a22.setPosition({550, 56});
    a22.setRotation(-20);
    a22.setFillColor(sf::Color(0x80, 0x80, 0x80));
    window.draw(a22);

    sf::RectangleShape ap21;
    ap21.setSize({20, 20});
    ap21.setPosition({550, 50});
    ap21.setFillColor(sf::Color(0x80, 0x80, 0x80));
    window.draw(ap21);

    sf::RectangleShape ap22;
    ap22.setSize({20, 70});
    ap22.setPosition({520, 160});
    ap22.setRotation(-90);
    ap22.setFillColor(sf::Color(0x80, 0x80, 0x80));
    window.draw(ap22);

    window.display();

    sf::sleep(sf::seconds(5));
}