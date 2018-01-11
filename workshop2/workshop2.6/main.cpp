#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <SFML/System.hpp>
#include <cassert>
#include <ctime>
#include <random>
#include <algorithm>
// Структура хранит фигуры, составляющие стрелку, а также
//  позицию и поворот стрелки.
// После изменения позиции или поворота надо вызвать
//  функцию updateArrowElements, чтобы стрелка оставалась
//  в согласованном состоянии.

// Инициализирует фигуру-стрелку
constexpr unsigned BALL_RADIUS = 30;

static const sf::Color Collor[8] = {{125, 125, 125}, {255, 0, 255}, {255, 0, 0}, {0, 0, 255}, {0, 255, 0}, {255, 0, 153}, {102, 255, 102}, {153, 255, 51}};

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

struct ball
{
    sf::CircleShape circle;
    sf::Vector2f position;
    sf::Vector2f speed;
    float clock;
};

void initBall(ball &balls, sf::Color &color, sf::Vector2f &speed, sf::Vector2f &position)
{
    balls.circle.setFillColor(sf::Color(color));
    balls.circle.setPosition(position);
    balls.circle.setRadius(BALL_RADIUS);
    balls.circle.setOrigin(BALL_RADIUS, BALL_RADIUS);
    balls.speed = speed;
}

struct PRNG
{
    unsigned seed = 0;
};

struct PRNGColor
{
    std::mt19937 engine;
};

size_t getRandomIndex(PRNGColor &generator, size_t size)
{
    // Создаём распределение
    std::uniform_int_distribution<size_t> distribution(0, size - 1);

    // Вычисляем псевдослучайное число: вызовем распределение как функцию,
    //  передав генератор произвольных целых чисел как аргумент.
    return distribution(generator.engine);
}

void initColorGenerator(PRNGColor &generator)
{
    // Используем время с 1 января 1970 года в секундах как случайное зерно
    const unsigned seed = unsigned(std::time(nullptr));
    generator.engine.seed(seed);
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

//задаем импульс правильный для шарика
void checkBall(std::vector<ball>(&balls))
{
    for (size_t fi = 0; fi < balls.size(); ++fi)
    {
        for (size_t si = fi + 1; si < balls.size(); ++si)
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

//obnova
void updateBallLifetimers(std::vector<ball>(&balls), float dt)
{
    for (size_t i = 0; i < balls.size(); ++i)
    {
        balls[i].clock += dt;
    }
}

bool isDeathTime(ball &ball)
{
    return (ball.clock >= 10);
}

void removeDeathBalls(std::vector<ball>(&balls))
{
    for (size_t i = 0; i < balls.size(); ++i)
    {
        auto newEnd = std::remove_if(balls.begin(), balls.end(), isDeathTime);
        balls.erase(newEnd, balls.end());
    }
}

void update(std::vector<ball>(&balls), float dt)
{
    updateBallLifetimers(balls, dt);
    removeDeathBalls(balls);
    for (size_t i = 0; i < balls.size(); ++i)
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
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition, bool &Click)
{
    Click = false;
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            mousePosition = {float(event.mouseButton.x), float(event.mouseButton.y)};
            Click = true;
            break;
        default:
            break;
        }
    }
}
//проверяет на столкновение со стенками и шариками для создания шарика
void createChecking(sf::Vector2f &mousePosition, const int WINDOW_HEIGHT, const int WINDOW_WIDTH, std::vector<ball>(&balls), PRNGColor &colorGenerator, PRNG &generator)
{
    bool Check = true;
    for (size_t i = 0; i < balls.size(); ++i)
    {
        sf::Vector2f distVect = mousePosition - balls[i].circle.getPosition();
        float distance = std::hypot(distVect.x, distVect.y);
        std::cout << distance << std::endl;

        if (not((mousePosition.y + BALL_RADIUS < WINDOW_HEIGHT) && (mousePosition.x + BALL_RADIUS < WINDOW_WIDTH) && (mousePosition.y > BALL_RADIUS) && (mousePosition.x > BALL_RADIUS) && (distance > BALL_RADIUS * 2)))
        {
            Check = false;
        }
    }
    std::cout << "     " << std::endl;
    if (Check == true)
    {
        ball newBall;
        int colorFirst = getRandomIndex(colorGenerator, std::size(Collor));
        int colorSecond = getRandomIndex(colorGenerator, std::size(Collor));

        float speedX = random(generator, 70, 300);
        float speedY = random(generator, 70, 300);
        sf::Vector2f speed = {speedX, speedY};

        sf::Color colorMix((Collor[colorFirst].r + Collor[colorSecond].r) / 2, (Collor[colorFirst].g + Collor[colorSecond].g) / 2, (Collor[colorFirst].b + Collor[colorSecond].b) / 2, (Collor[colorFirst].a + Collor[colorSecond].a) / 2);

        initBall(newBall, colorMix, speed, mousePosition);
        balls.push_back(newBall);
    }
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, std::vector<ball>(&balls))
{
    window.clear(sf::Color(255, 255, 255));
    for (size_t i = 0; i < balls.size(); ++i)
    {
        window.draw(balls[i].circle);
    }
    window.display();
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

    std::vector<ball> balls;
    sf::Vector2f position[5] = {{20.f, 80.f}, {40.f, 200.f}, {50.f, 500.f}, {400.f, 400.f}, {300.f, 500.f}};
    for (size_t i = 0; i < 5; ++i)
    {
        float speedX = random(generator, 70, 300);
        float speedY = random(generator, 70, 300);

        int colorFirst = getRandomIndex(colorGenerator, std::size(Collor));
        int colorSecond = getRandomIndex(colorGenerator, std::size(Collor));

        sf::Color colorMix((Collor[colorFirst].r + Collor[colorSecond].r) / 2, (Collor[colorFirst].g + Collor[colorSecond].g) / 2, (Collor[colorFirst].b + Collor[colorSecond].b) / 2, (Collor[colorFirst].a + Collor[colorSecond].a) / 2);
        sf::Vector2f speed = {speedX, speedY};

        ball newBall;
        initBall(newBall, colorMix, speed, position[i]);
        balls.push_back(newBall);
    }
    window.display();

    sf::Clock clock;

    bool Click = false;

    sf::Vector2f mousePosition;

    while (window.isOpen())
    {
        const float dt = clock.restart().asSeconds();
        pollEvents(window, mousePosition, Click);
        if (Click == true)
        {
            createChecking(mousePosition, WINDOW_HEIGHT, WINDOW_WIDTH, balls, colorGenerator, generator);
        }
        checkBall(balls);
        update(balls, dt);
        redrawFrame(window, balls);
    }
}
