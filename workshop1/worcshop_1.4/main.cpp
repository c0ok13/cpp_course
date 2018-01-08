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
void initsprite(sf::Sprite &cat, sf::Texture &texture, float width, float hight, float centerX, float centerY)
{
    cat.setTexture(texture);
    cat.setTextureRect(sf::IntRect(0, 0, width, hight));
    cat.setPosition(100, 25);
    cat.setOrigin(centerX, centerY);
}

//обработка мышки
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << ",y=" << event.y << std::endl;

    mousePosition = {float(event.x), float(event.y)};
}

//obnova
void update(sf::Sprite &cat, sf::Sprite &point, float dt)
{
    const sf::Vector2f delta = cat.getPosition() - point.getPosition();
    const float distance = std::hypot(delta.x, delta.y);
    const float speed = 90;
    float rotate = 0;
    float maxspeed = speed * dt;
    if (cat.getPosition().x < point.getPosition().x)
    {
        cat.setScale(1, 1);
    }
    if (cat.getPosition().x > point.getPosition().x)
    {
        cat.setScale(-1, 1);
    }
    if (distance != 0)
    {
        const sf::Vector2f NormVect = {delta.x / distance, delta.y / distance};
        float move = std::min(speed * dt, distance);

        cat.setPosition(cat.getPosition() - NormVect * move);
    }
}

//opros
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition, sf::Sprite &point)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            point.setPosition(event.mouseButton.x, event.mouseButton.y);
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, sf::Sprite &cat, sf::Sprite &point)
{
    window.clear(sf::Color(255, 255, 255));
    if (cat.getPosition() != point.getPosition())
    {
        window.draw(point);
    }
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

    sf::Clock clock;

    sf::Texture texture;
    texture.loadFromFile("png/cat.png");

    sf::Texture point_text;
    point_text.loadFromFile("png/red_pointer.png");

    sf::Vector2f mousePosition;

    sf::Sprite point;
    initsprite(point, point_text, 32, 32, 16, 16);
    initsprite(cat, texture, 38, 35, 19, 17.5);
    while (window.isOpen())
    {
        const float dt = clock.restart().asSeconds();
        pollEvents(window, mousePosition, point);
        update(cat, point, dt);
        redrawFrame(window, cat, point);
    }
}
