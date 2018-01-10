#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <SFML/System.hpp>
#include <cassert>
#include <ctime>
#include <random>
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

struct PRNG
{
    unsigned seed = 0;
};

struct PRNGColor
{
    std::mt19937 engine;
};

void initColorGenerator(PRNGColor &generator)
{
    // Используем время с 1 января 1970 года в секундах как случайное зерно
    const unsigned seed = unsigned(std::time(nullptr));
    generator.engine.seed(seed);
}

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

void initGenerator(PRNG &generator)
{
    // Получаем случайное зерно последовательности
    generator.seed = unsigned(std::time(nullptr));
}

unsigned random(PRNG &generator, unsigned minValue, unsigned maxValue)
{
    // Проверяем корректность аргументов
    assert(minValue < maxValue);
    // Итеративно изменяем текущее число в генераторе
    generator.seed = (generator.seed * 73129 + 95121);

    // Приводим число к отрезку [minValue, maxValue]
    return (generator.seed % (maxValue + 1 - minValue)) + minValue;
}

size_t getRandomIndex(PRNGColor &generator, size_t size)
{
    // Создаём распределение
    std::uniform_int_distribution<size_t> distribution(0, size - 1);

    // Вычисляем псевдослучайное число: вызовем распределение как функцию,
    //  передав генератор произвольных целых чисел как аргумент.
    return distribution(generator.engine);
}

int main()
{
    PRNG generator;
    initGenerator(generator);

    PRNGColor colorGenerator;
    initColorGenerator(colorGenerator);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Arrow follows mouse", sf::Style::Default, settings);

    ball balls[5];
    sf::Color Collor[8] = {{125, 125, 125}, {255, 0, 255}, {255, 0, 0}, {0, 0, 255}, {0, 255, 0}, {255, 0, 153}, {102, 255, 102}, {153, 255, 51}};
    sf::Vector2f position[5] = {{20.f, 80.f}, {40.f, 200.f}, {50.f, 500.f}, {400.f, 400.f}, {300.f, 500.f}};
    for (size_t i = 0; i < std::size(balls); ++i)
    {
        float speedX = random(generator, 70, 300);
        float speedY = random(generator, 70, 300);

        int colorFirst = getRandomIndex(colorGenerator, std::size(Collor));
        int colorSecond = getRandomIndex(colorGenerator, std::size(Collor));

        sf::Color colorMix((Collor[colorFirst].r + Collor[colorSecond].r) / 2, (Collor[colorFirst].g + Collor[colorSecond].g) / 2, (Collor[colorFirst].b + Collor[colorSecond].b) / 2, (Collor[colorFirst].a + Collor[colorSecond].a) / 2);
        sf::Vector2f speed = {speedX, speedY};

        initBall(balls[i], colorMix, speed, position[i]);
    }
    window.display();

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
