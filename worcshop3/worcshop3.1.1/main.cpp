#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

struct ballWithName
{
    sf::Text text;
    sf::CircleShape circle;
};

void init(ballWithName &ballWithName, int radius, sf::Font &font)
{
    ballWithName.text.setFont(font);
    ballWithName.text.setString("MIYA");
    ballWithName.text.setCharacterSize(30);
    ballWithName.text.setFillColor(sf::Color::Green);

    ballWithName.circle.setRadius(radius);
    ballWithName.circle.setPosition(WINDOW_WIDTH / 2 - radius, WINDOW_HEIGHT / 2 - radius);
    ballWithName.circle.setOrigin(radius, radius);
    ballWithName.circle.setFillColor(sf::Color::Yellow);
    ballWithName.circle.setOutlineThickness(3);
    ballWithName.circle.setOutlineColor(sf::Color::Black);
    ballWithName.text.setPosition(ballWithName.circle.getPosition().x - 40, ballWithName.circle.getPosition().y - radius / 3);
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
void redrawFrame(sf::RenderWindow &window, ballWithName &ballWithName)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(ballWithName.circle);
    window.draw(ballWithName.text);
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

    ballWithName ball;

    sf::Font font;
    font.loadFromFile("Azeroth Cyrillic.ttf");

    init(ball, 70, font);

    while (window.isOpen())
    {
        pollEvents(window);
        redrawFrame(window, ball);
    }
}