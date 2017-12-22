#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
// Структура хранит фигуры, составляющие стрелку, а также
//  позицию и поворот стрелки.
// После изменения позиции или поворота надо вызвать
//  функцию updateArrowElements, чтобы стрелка оставалась
//  в согласованном состоянии.

// Инициализирует фигуру-стрелку
void initcat(sf::Sprite &cat, sf::Texture &texture)
{
    cat.setTexture(texture);
    cat.setTextureRect(sf::IntRect(0, 0, 38, 35));
    cat.setPosition(100, 25);
}

//opros
void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, sf::Sprite &cat)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(cat);
    window.display();
}

// Программа рисует в окне стрелку, которая поворачивается вслед за курсором мыши.
int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Arrow follows mouse", sf::Style::Default, settings);

    sf::Sprite cat;

    sf::Texture texture;
    texture.loadFromFile("png/cat.png");

    initcat(cat, texture);
    while (window.isOpen())
    {
        pollEvents(window);
        redrawFrame(window, cat);
    }
}