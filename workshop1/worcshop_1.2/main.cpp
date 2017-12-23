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
void initArrow(sf::ConvexShape &arrow)
{
    arrow.setPosition({400, 300});
    arrow.setPointCount(7);
    arrow.setPoint(0, {35, 0});
    arrow.setPoint(1, {0, -40});
    arrow.setPoint(2, {0, -20});
    arrow.setPoint(3, {-25, -20});
    arrow.setPoint(4, {-25, 20});
    arrow.setPoint(5, {0, 20});
    arrow.setPoint(6, {0, 40});
    arrow.setFillColor(sf::Color(0xFF, 0xFC, 0));

    arrow.setOutlineThickness(2);
    arrow.setOutlineColor(sf::Color(0, 0, 0));
}

//  переводит радианы в градусы
float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

//обработка мышки
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << ",y=" << event.y << std::endl;

    mousePosition = {float(event.x), float(event.y)};
}

//opros
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
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
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

//obnova
void update(const sf::Vector2f &mousePosition, sf::ConvexShape &arrow, float dt)
{
    const sf::Vector2f delta = mousePosition - arrow.getPosition();
    const float distance = std::hypot(delta.x, delta.y);
    float angle = atan2(delta.y, delta.x);
    const float speed = 90;
    const float LinearSpeed = 20;
    float pt = arrow.getRotation();
    float maxspeed = speed * dt;
    if (distance != 0)
    {
        if (angle < 0)
        {
            angle += 2 * M_PI;
        }
        float ag = toDegrees(angle);
        float nextangle = std::min(std::abs(ag - maxspeed), maxspeed);
        if (ag < pt)
        {
            if ((ag + 180) < pt)
            {
                arrow.setRotation(pt + nextangle);
            }
            else
            {
                arrow.setRotation(pt - nextangle);
            }
        }
        else
        {
            if ((ag - 180) > pt)
            {
                arrow.setRotation(pt - nextangle);
            }
            else
            {
                arrow.setRotation(pt + nextangle);
            }
        }
        const sf::Vector2f NormVect = {delta.x / distance, delta.y / distance};
        float move = std::min(LinearSpeed * dt, distance);
        arrow.setPosition(arrow.getPosition() + NormVect * move);
    }
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &arrow)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(arrow);
    window.display();
}

// Программа рисует в окне стрелку, которая поворачивается вслед за курсором мыши.
int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::Clock clock;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Arrow follows mouse", sf::Style::Default, settings);

    sf::ConvexShape arrow;

    sf::Vector2f mousePosition;

    initArrow(arrow);
    while (window.isOpen())
    {
        const float dt = clock.restart().asSeconds();
        pollEvents(window, mousePosition);
        update(mousePosition, arrow, dt);
        redrawFrame(window, arrow);
    }
}