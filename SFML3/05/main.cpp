#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
// Структура хранит фигуры, составляющие стрелку, а также
//  позицию и поворот стрелки.
// После изменения позиции или поворота надо вызвать
//  функцию updateArrowElements, чтобы стрелка оставалась
//  в согласованном состоянии.
struct Eye
{
    sf::ConvexShape pupil;
    sf::ConvexShape eyeball;
    sf::Vector2f position;
    float rotation = 0;
};

sf::Vector2f toEuclidean(float radiusX, float radiusY, float angle)
{
    return {
        radiusX * std::cos(angle),
        radiusY * std::sin(angle)};
}

float toDegrees(double radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void updateEyeElements(Eye &Eye)
{
    const sf::Vector2f headOffset = toEuclidean(10, 30, Eye.rotation);
    Eye.pupil.setPosition(Eye.position + headOffset);
    /* Eye.pupil.setRotation(toDegrees(Eye.rotation));*/
}
// Инициализирует фигуру-стрелку
void initEye(Eye &Eye, float posX, float posY)
{
    constexpr int pointCount = 200;

    Eye.position = {posX, posY};
    Eye.pupil.setPosition({posX, posY});
    Eye.pupil.setFillColor(sf::Color(0xFF, 0, 0));

    const sf::Vector2f PupilRadius = {10.f, 40.f};

    Eye.pupil.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            PupilRadius.x * std::sin(angle),
            PupilRadius.y * std::cos(angle)};
        Eye.pupil.setPoint(pointNo, point);
    }

    const sf::Vector2f ellipseRadius = {25.f, 100.f};

    Eye.eyeball.setPosition({posX, posY});
    Eye.eyeball.setFillColor(sf::Color(0xF, 0xFF, 0xFF));

    Eye.eyeball.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            ellipseRadius.x * std::sin(angle),
            ellipseRadius.y * std::cos(angle)};
        Eye.eyeball.setPoint(pointNo, point);
    }

    updateEyeElements(Eye);
}

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

// Обновляет фигуру, указывающую на мышь
void update(const sf::Vector2f &mousePosition, Eye &Eye)
{
    const sf::Vector2f delta = mousePosition - Eye.position;
    Eye.rotation = atan2(delta.y, delta.x);
    updateEyeElements(Eye);
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, Eye &EyeR, Eye &EyeL)
{
    window.clear();
    window.draw(EyeL.eyeball);
    window.draw(EyeL.pupil);
    window.draw(EyeR.eyeball);
    window.draw(EyeR.pupil);
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
    Eye eyeL;
    Eye eyeR;
    sf::Vector2f mousePosition;

    initEye(eyeL, 400, 300);
    initEye(eyeR, 500, 300);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, eyeL);
        update(mousePosition, eyeR);
        redrawFrame(window, eyeR, eyeL);
    }
}