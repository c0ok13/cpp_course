#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <SFML/System.hpp>
// Структура хранит фигуры, составляющие стрелку, а также
//  позицию и поворот стрелки.
// После изменения позиции или поворота надо вызвать
//  функцию updateArrowElements, чтобы стрелка оставалась
//  в согласованном состоянии.

// Инициализирует фигуру-стрелку
constexpr unsigned BALL_RADIUS = 30;
constexpr size_t ballsCount = 5;

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

struct ball
{
    sf::CircleShape circle;
    sf::Vector2f position;
    sf::Vector2f speed;
};

void checkBall(ball (&balls)[ballsCount])
{
    for (size_t fi = 0; fi < std::size(balls); ++fi)
    {
        for (size_t si = fi + 1; si < std::size(balls); ++si)
        {
            sf::Vector2f distVect = balls[fi].circle.getPosition() - balls[si].circle.getPosition();
            float distance = std::hypot(distVect.x, distVect.y);
            if (distance < BALL_RADIUS * 2)
            {
                sf::Vector2f postSpeedVect = balls[fi].speed - balls[si].speed;

                balls[fi].speed = balls[fi].speed - (postSpeedVect.x * distVect.x + postSpeedVect.y * distVect.y) / (distance * distance) * distVect;

                distVect = -distVect;
                postSpeedVect = -postSpeedVect;

                balls[si].speed = balls[si].speed - (postSpeedVect.x * distVect.x + postSpeedVect.y * distVect.y) / (distance * distance) * distVect;
            }
        }
    }
}

void initBall(ball &ball, sf::Color &color, sf::Vector2f &speed, sf::Vector2f &position)
{
    ball.circle.setFillColor(sf::Color(color));
    ball.circle.setPosition(position);
    ball.circle.setRadius(BALL_RADIUS);
    ball.circle.setOrigin(BALL_RADIUS, BALL_RADIUS);
    ball.speed = speed;
}

//obnova
void update(ball (&balls)[ballsCount], float dt)
{
    for (size_t i = 0; i < std::size(balls); ++i)
    {
        if ((balls[i].circle.getPosition().x + BALL_RADIUS >= WINDOW_WIDTH) && (balls[i].circle.getPosition().x - BALL_RADIUS > 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }

        if ((balls[i].circle.getPosition().x - BALL_RADIUS < 0) && (balls[i].speed.x < 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }

        if ((balls[i].circle.getPosition().y + BALL_RADIUS >= WINDOW_HEIGHT) && (balls[i].circle.getPosition().y - BALL_RADIUS > 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }

        if ((balls[i].circle.getPosition().y - BALL_RADIUS < WINDOW_WIDTH) && (balls[i].circle.getPosition().y - BALL_RADIUS < 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        balls[i].circle.setPosition(balls[i].circle.getPosition() + balls[i].speed * dt);
    }
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
void redrawFrame(sf::RenderWindow &window, ball (&balls)[ballsCount])
{
    window.clear(sf::Color(255, 255, 255));
    for (size_t i = 0; i < std::size(balls); ++i)
    {
        window.draw(balls[i].circle);
    }
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

    ball balls[5];
    sf::Color Collor[5] = {{125, 125, 125}, {255, 0, 255}, {255, 0, 0}, {0, 0, 255}, {0, 255, 0}};
    sf::Vector2f speed[5] = {{20.f, 80.f}, {10, 30.f}, {50.f, 5.f}, {30.f, 30.f}, {100.f, 1.f}};
    sf::Vector2f position[5] = {{20.f, 80.f}, {40.f, 200.f}, {50.f, 500.f}, {400.f, 400.f}, {300.f, 500.f}};
    initBall(balls[0], Collor[0], speed[0], position[0]);
    initBall(balls[1], Collor[1], speed[1], position[1]);
    initBall(balls[2], Collor[2], speed[2], position[2]);
    initBall(balls[3], Collor[3], speed[3], position[3]);
    initBall(balls[4], Collor[4], speed[4], position[4]);

    sf::Clock clock;

    sf::Vector2f mousePosition;

    while (window.isOpen())
    {
        const float dt = clock.restart().asSeconds();
        pollEvents(window);
        checkBall(balls);
        update(balls, dt);
        redrawFrame(window, balls);
    }
}
